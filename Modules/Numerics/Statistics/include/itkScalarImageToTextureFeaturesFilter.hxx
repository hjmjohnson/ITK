/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkScalarImageToTextureFeaturesFilter_hxx
#define itkScalarImageToTextureFeaturesFilter_hxx

#include "itkNeighborhood.h"
#include "itkMath.h"

namespace itk::Statistics
{
template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::
  ScalarImageToTextureFeaturesFilter()
{
  this->SetNumberOfRequiredInputs(1);
  this->SetNumberOfRequiredOutputs(1);

  for (int i = 0; i < 2; ++i)
  {
    this->ProcessObject::SetNthOutput(i, this->MakeOutput(i));
  }

  this->m_GLCMGenerator = CooccurrenceMatrixFilterType::New();
  this->m_GLCMCalculator = TextureFeaturesFilterType::New();
  this->m_GLCMCalculator->SetInput(this->m_GLCMGenerator->GetOutput());
  this->m_FeatureMeans = FeatureValueVector::New();
  this->m_FeatureStandardDeviations = FeatureValueVector::New();

  // Set the requested features to the default value:
  // {Energy, Entropy, InverseDifferenceMoment, Inertia, ClusterShade,
  // ClusterProminence}
  const FeatureNameVectorPointer requestedFeatures = FeatureNameVector::New();
  // can't directly set m_RequestedFeatures since it is const!
  requestedFeatures->push_back(
    static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Energy));
  requestedFeatures->push_back(
    static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Entropy));
  requestedFeatures->push_back(static_cast<uint8_t>(
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::InverseDifferenceMoment));
  requestedFeatures->push_back(
    static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Inertia));
  requestedFeatures->push_back(
    static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterShade));
  requestedFeatures->push_back(
    static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterProminence));
  this->SetRequestedFeatures(requestedFeatures);

  // Set the offset directions to their defaults: half of all the possible
  // directions 1 pixel ILLRMUI
  // away. (The other half is included by symmetry.)
  // We use a neighborhood iterator to calculate the appropriate offsets.
  using NeighborhoodType = Neighborhood<typename ImageType::PixelType, ImageType::ImageDimension>;
  NeighborhoodType hood;
  hood.SetRadius(1);

  // select all "previous" neighbors that are face+edge+vertex
  // connected to the current pixel. do not include the center pixel.
  const unsigned int        centerIndex = hood.GetCenterNeighborhoodIndex();
  OffsetType                offset;
  const OffsetVectorPointer offsets = OffsetVector::New();
  for (unsigned int d = 0; d < centerIndex; ++d)
  {
    offset = hood.GetOffset(d);
    offsets->push_back(offset);
  }
  this->SetOffsets(offsets);
  m_FastCalculations = false;
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
auto
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::MakeOutput(
  DataObjectPointerArraySizeType itkNotUsed(idx)) -> DataObjectPointer
{
  return FeatureValueVectorDataObjectType::New().GetPointer();
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::GenerateData()
{
  if (m_FastCalculations)
  {
    this->FastCompute();
  }
  else
  {
    this->FullCompute();
  }
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::FullCompute()
{
  const size_t numOffsets = m_Offsets->size();
  const size_t numFeatures = m_RequestedFeatures->size();
  auto **      features = new double *[numOffsets];
  for (size_t i = 0; i < numOffsets; ++i)
  {
    features[i] = new double[numFeatures];
  }

  // For each offset, calculate each feature
  using InternalTextureFeatureName = itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature;

  size_t offsetNum = 0;
  for (typename OffsetVector::ConstIterator offsetIt = m_Offsets->Begin(); offsetIt != m_Offsets->End();
       ++offsetIt, offsetNum++)
  {
    this->m_GLCMGenerator->SetOffset(offsetIt.Value());
    this->m_GLCMCalculator->Update();


    size_t featureNum = 0;
    for (typename FeatureNameVector::ConstIterator fnameIt = m_RequestedFeatures->Begin();
         fnameIt != m_RequestedFeatures->End();
         ++fnameIt, featureNum++)
    {
      features[offsetNum][featureNum] =
        this->m_GLCMCalculator->GetFeature(static_cast<InternalTextureFeatureName>(fnameIt.Value()));
    }
  }

  // Now get the mean and deviation of each feature across the offsets.
  m_FeatureMeans->clear();
  m_FeatureStandardDeviations->clear();
  auto * tempFeatureMeans = new double[numFeatures];
  auto * tempFeatureDevs = new double[numFeatures];

  /*Compute incremental mean and SD, a la Knuth, "The  Art of Computer
    Programming, Volume 2: Seminumerical Algorithms",  section 4.2.2.
    Compute mean and standard deviation using the recurrence relation:
    M(1) = x(1), M(k) = M(k-1) + (x(k) - M(k-1) ) / k
    S(1) = 0, S(k) = S(k-1) + (x(k) - M(k-1)) * (x(k) - M(k))
    for 2 <= k <= n, then
    sigma = std::sqrt(S(n) / n) (or divide by n-1 for sample SD instead of
    population SD).
  */

  // Set up the initial conditions (k = 1)
  for (size_t featureNum = 0; featureNum < numFeatures; ++featureNum)
  {
    tempFeatureMeans[featureNum] = features[0][featureNum];
    tempFeatureDevs[featureNum] = 0;
  }
  // Run through the recurrence (k = 2 ... N)
  for (offsetNum = 1; offsetNum < numOffsets; ++offsetNum)
  {
    const size_t k = offsetNum + 1;
    for (size_t featureNum = 0; featureNum < numFeatures; ++featureNum)
    {
      const double M_k_minus_1 = tempFeatureMeans[featureNum];
      const double S_k_minus_1 = tempFeatureDevs[featureNum];
      const double x_k = features[offsetNum][featureNum];

      const double M_k = M_k_minus_1 + (x_k - M_k_minus_1) / k;
      const double S_k = S_k_minus_1 + (x_k - M_k_minus_1) * (x_k - M_k);

      tempFeatureMeans[featureNum] = M_k;
      tempFeatureDevs[featureNum] = S_k;
    }
  }
  for (size_t featureNum = 0; featureNum < numFeatures; ++featureNum)
  {
    tempFeatureDevs[featureNum] = std::sqrt(tempFeatureDevs[featureNum] / numOffsets);

    m_FeatureMeans->push_back(tempFeatureMeans[featureNum]);
    m_FeatureStandardDeviations->push_back(tempFeatureDevs[featureNum]);
  }

  auto * meanOutputObject =
    itkDynamicCastInDebugMode<FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(0));
  meanOutputObject->Set(m_FeatureMeans);

  auto * standardDeviationOutputObject =
    itkDynamicCastInDebugMode<FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(1));
  standardDeviationOutputObject->Set(m_FeatureStandardDeviations);

  delete[] tempFeatureMeans;
  delete[] tempFeatureDevs;
  for (size_t i = 0; i < numOffsets; ++i)
  {
    delete[] features[i];
  }
  delete[] features;
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::FastCompute()
{
  // Compute the feature for the first offset
  const typename OffsetVector::ConstIterator offsetIt = m_Offsets->Begin();
  this->m_GLCMGenerator->SetOffset(offsetIt.Value());
  this->m_GLCMCalculator->Update();

  using InternalTextureFeatureName = itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature;
  m_FeatureMeans->clear();
  m_FeatureStandardDeviations->clear();
  typename FeatureNameVector::ConstIterator fnameIt;
  for (fnameIt = m_RequestedFeatures->Begin(); fnameIt != m_RequestedFeatures->End(); ++fnameIt)
  {
    m_FeatureMeans->push_back(
      this->m_GLCMCalculator->GetFeature(static_cast<InternalTextureFeatureName>(fnameIt.Value())));
    m_FeatureStandardDeviations->push_back(0.0);
  }

  auto * meanOutputObject =
    itkDynamicCastInDebugMode<FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(0));
  meanOutputObject->Set(m_FeatureMeans);

  auto * standardDeviationOutputObject =
    itkDynamicCastInDebugMode<FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(1));
  standardDeviationOutputObject->Set(m_FeatureStandardDeviations);
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::SetInput(
  const ImageType * image)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput(0, const_cast<ImageType *>(image));

  m_GLCMGenerator->SetInput(image);
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::SetNumberOfBinsPerAxis(
  unsigned int numberOfBins)
{
  itkDebugMacro("setting NumberOfBinsPerAxis to " << numberOfBins);
  m_GLCMGenerator->SetNumberOfBinsPerAxis(numberOfBins);
  this->Modified();
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::SetPixelValueMinMax(
  PixelType min,
  PixelType max)
{
  itkDebugMacro("setting Min to " << min << "and Max to " << max);
  m_GLCMGenerator->SetPixelValueMinMax(min, max);
  this->Modified();
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::SetMaskImage(
  const MaskImageType * image)
{
  // Process object is not const-correct so the const_cast is required here
  this->ProcessObject::SetNthInput(1, const_cast<MaskImageType *>(image));

  m_GLCMGenerator->SetMaskImage(image);
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
const TImageType *
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::GetInput() const
{
  return itkDynamicCastInDebugMode<const ImageType *>(this->GetPrimaryInput());
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
const typename ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::
  FeatureValueVectorDataObjectType *
  ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::GetFeatureMeansOutput()
    const
{
  return itkDynamicCastInDebugMode<const FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(0));
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
const typename ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::
  FeatureValueVectorDataObjectType *
  ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::
    GetFeatureStandardDeviationsOutput() const
{
  return itkDynamicCastInDebugMode<const FeatureValueVectorDataObjectType *>(this->ProcessObject::GetOutput(1));
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
const TMaskImageType *
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::GetMaskImage() const
{
  return static_cast<const MaskImageType *>(this->ProcessObject::GetInput(1));
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::SetInsidePixelValue(
  MaskPixelType insidePixelValue)
{
  itkDebugMacro("setting InsidePixelValue to " << insidePixelValue);
  m_GLCMGenerator->SetInsidePixelValue(insidePixelValue);
  this->Modified();
}

template <typename TImageType, typename THistogramFrequencyContainer, typename TMaskImageType>
void
ScalarImageToTextureFeaturesFilter<TImageType, THistogramFrequencyContainer, TMaskImageType>::PrintSelf(
  std::ostream & os,
  Indent         indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "RequestedFeatures: " << this->GetRequestedFeatures() << std::endl;
  os << indent << "FeatureStandardDeviations: " << this->GetFeatureStandardDeviations() << std::endl;
  os << indent << "FastCalculations: " << this->GetFastCalculations() << std::endl;
  os << indent << "Offsets: " << this->GetOffsets() << std::endl;
  os << indent << "FeatureMeans: " << this->GetFeatureMeans() << std::endl;
}
} // namespace itk::Statistics

#endif
