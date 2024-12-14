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
#ifndef itkBinaryStatisticsKeepNObjectsImageFilter_hxx
#define itkBinaryStatisticsKeepNObjectsImageFilter_hxx

#include "itkProgressAccumulator.h"

namespace itk
{
template <typename TInputImage, typename TFeatureImage>
BinaryStatisticsKeepNObjectsImageFilter<TInputImage, TFeatureImage>::BinaryStatisticsKeepNObjectsImageFilter()
  : m_BackgroundValue(NumericTraits<OutputImagePixelType>::NonpositiveMin())
  , m_ForegroundValue(NumericTraits<OutputImagePixelType>::max())
  , m_Attribute(LabelObjectType::MEAN)
{
  this->SetNumberOfRequiredInputs(2);
}

template <typename TInputImage, typename TFeatureImage>
void
BinaryStatisticsKeepNObjectsImageFilter<TInputImage, TFeatureImage>::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // We need all the input.
  const InputImagePointer input = const_cast<InputImageType *>(this->GetInput());
  if (input)
  {
    input->SetRequestedRegion(input->GetLargestPossibleRegion());
  }
}

template <typename TInputImage, typename TFeatureImage>
void
BinaryStatisticsKeepNObjectsImageFilter<TInputImage, TFeatureImage>::EnlargeOutputRequestedRegion(DataObject *)
{
  this->GetOutput()->SetRequestedRegion(this->GetOutput()->GetLargestPossibleRegion());
}

template <typename TInputImage, typename TFeatureImage>
void
BinaryStatisticsKeepNObjectsImageFilter<TInputImage, TFeatureImage>::GenerateData()
{
  // Create a process accumulator for tracking the progress of this minipipeline
  auto progress = ProgressAccumulator::New();

  progress->SetMiniPipelineFilter(this);

  // Allocate the output
  this->AllocateOutputs();

  auto labelizer = LabelizerType::New();
  labelizer->SetInput(this->GetInput());
  labelizer->SetInputForegroundValue(m_ForegroundValue);
  labelizer->SetOutputBackgroundValue(m_BackgroundValue);
  labelizer->SetFullyConnected(m_FullyConnected);
  labelizer->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(labelizer, .3f);

  auto valuator = LabelObjectValuatorType::New();
  valuator->SetInput(labelizer->GetOutput());
  valuator->SetFeatureImage(this->GetFeatureImage());
  valuator->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  valuator->SetComputeHistogram(false);
  if (m_Attribute != LabelObjectType::PERIMETER && m_Attribute != LabelObjectType::ROUNDNESS)
  {
    valuator->SetComputePerimeter(false);
  }
  if (m_Attribute == LabelObjectType::FERET_DIAMETER)
  {
    valuator->SetComputeFeretDiameter(true);
  }
  progress->RegisterInternalFilter(valuator, .3f);

  auto opening = KeepNObjectsType::New();
  opening->SetInput(valuator->GetOutput());
  opening->SetNumberOfObjects(m_NumberOfObjects);
  opening->SetReverseOrdering(m_ReverseOrdering);
  opening->SetAttribute(m_Attribute);
  opening->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(opening, .2f);

  auto binarizer = BinarizerType::New();
  binarizer->SetInput(opening->GetOutput());
  binarizer->SetForegroundValue(m_ForegroundValue);
  binarizer->SetBackgroundValue(m_BackgroundValue);
  binarizer->SetBackgroundImage(this->GetInput());
  binarizer->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(binarizer, .2f);

  binarizer->GraftOutput(this->GetOutput());
  binarizer->Update();
  this->GraftOutput(binarizer->GetOutput());
}

template <typename TInputImage, typename TFeatureImage>
void
BinaryStatisticsKeepNObjectsImageFilter<TInputImage, TFeatureImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  itkPrintSelfBooleanMacro(FullyConnected);
  os << indent
     << "BackgroundValue: " << static_cast<typename NumericTraits<OutputImagePixelType>::PrintType>(m_BackgroundValue)
     << '\n';
  os << indent
     << "ForegroundValue: " << static_cast<typename NumericTraits<OutputImagePixelType>::PrintType>(m_ForegroundValue)
     << '\n';
  os << indent << "NumberOfObjects: " << m_NumberOfObjects << '\n';
  os << indent << "ReverseOrdering: " << m_ReverseOrdering << '\n';
  os << indent << "Attribute: " << LabelObjectType::GetNameFromAttribute(m_Attribute) << " (" << m_Attribute << ')'
     << '\n';
}
} // end namespace itk
#endif
