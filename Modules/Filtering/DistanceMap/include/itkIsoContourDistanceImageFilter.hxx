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
#ifndef itkIsoContourDistanceImageFilter_hxx
#define itkIsoContourDistanceImageFilter_hxx

#include "itkImageRegionIterator.h"
#include "itkIndex.h"
#include <mutex>

namespace itk
{

template <typename TInputImage, typename TOutputImage>
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::IsoContourDistanceImageFilter()
  : m_LevelSetValue(InputPixelType{})
  , m_FarValue(10 * NumericTraits<PixelType>::OneValue())
  , m_NarrowBand(nullptr)
{}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::SetNarrowBand(NarrowBandType * ptr)
{
  if (m_NarrowBand != ptr)
  {
    m_NarrowBand = ptr;
    this->Modified();
  }
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "LevelSetValue: " << static_cast<typename NumericTraits<PixelRealType>::PrintType>(m_LevelSetValue)
     << std::endl;
  os << indent << "FarValue: " << static_cast<typename NumericTraits<PixelType>::PrintType>(m_FarValue) << std::endl;
  os << indent << "Spacing: " << static_cast<typename NumericTraits<InputSpacingType>::PrintType>(m_Spacing)
     << std::endl;
  itkPrintSelfBooleanMacro(NarrowBanding);

  itkPrintSelfObjectMacro(NarrowBand);

  // ToDo
  // os << indent << "NarrowBandRegion: " << m_NarrowBandRegion << std::endl;
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::GenerateInputRequestedRegion()
{
  // use the default implementation.
  this->Superclass::GenerateInputRequestedRegion();
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::EnlargeOutputRequestedRegion(DataObject * output)
{
  // this filter requires the all of the output image to be in
  // the buffer
  auto * imgData = dynamic_cast<TOutputImage *>(output);
  if (imgData)
  {
    imgData->SetRequestedRegionToLargestPossibleRegion();
  }
  else
  {
    // pointer could not be cast to TLevelSet *
    itkWarningMacro("itk::IsoContourDistanceImageFilter::EnlargeOutputRequestedRegion cannot cast "
                    << typeid(output).name() << " to " << typeid(TOutputImage *).name());
  }
}


template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::GenerateData()
{
  this->UpdateProgress(0.0f);
  this->AllocateOutputs();
  this->BeforeThreadedGenerateData();
  this->UpdateProgress(0.01f);

  this->ClassicMultiThread(this->ThreaderCallback); // parallelizes ThreadedGenerateData
  this->UpdateProgress(0.3f);

  // parallelizes ThreadedGenerateDataFull or ThreadedGenerateDataBand
  this->ClassicMultiThread(this->ThreaderFullCallback);
  this->UpdateProgress(0.99f);

  this->AfterThreadedGenerateData();
  this->UpdateProgress(1.0f);
}


template <typename TInputImage, typename TOutputImage>
ITK_THREAD_RETURN_FUNCTION_CALL_CONVENTION
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::ThreaderFullCallback(void * arg)
{
  using WorkUnitInfo = MultiThreaderBase::WorkUnitInfo;
  auto *             workUnitInfo = static_cast<WorkUnitInfo *>(arg);
  const ThreadIdType workUnitID = workUnitInfo->WorkUnitID;
  const ThreadIdType workUnitCount = workUnitInfo->NumberOfWorkUnits;
  using FilterStruct = typename ImageSource<TOutputImage>::ThreadStruct;
  auto * str = (FilterStruct *)(workUnitInfo->UserData);
  auto * filter = static_cast<Self *>(str->Filter.GetPointer());

  // execute the actual method with appropriate output region
  // first find out how many pieces extent can be split into.
  typename TOutputImage::RegionType splitRegion;
  const ThreadIdType                total = filter->SplitRequestedRegion(workUnitID, workUnitCount, splitRegion);

  if (workUnitID < total)
  {
    // Iterate over split region or split band as convenient.
    if (!filter->m_NarrowBanding)
    {
      filter->ThreadedGenerateDataFull(splitRegion, workUnitID);
    }
    else
    {
      filter->ThreadedGenerateDataBand(splitRegion, workUnitID);
    }
  }
  // else don't use this thread. Threads were not split conveniently.
  return ITK_THREAD_RETURN_DEFAULT_VALUE;
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::BeforeThreadedGenerateData()
{
  // Instead of using GetNumberOfWorkUnits, we need to split the image into the
  // number of regions that will actually be returned by
  // itkImageSource::SplitRequestedRegion. Sometimes this number is less than
  // the number of threads requested.
  OutputImageRegionType dummy;
  const unsigned int    actualThreads = this->SplitRequestedRegion(0, this->GetNumberOfWorkUnits(), dummy);

  m_Spacing = this->GetInput()->GetSpacing();

  if (m_NarrowBanding)
  {
    // Split the narrow band into sections, one section for each thread
    this->m_NarrowBandRegion = this->m_NarrowBand->SplitBand(actualThreads);
  }
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::ThreadedGenerateData(
  const OutputImageRegionType & outputRegionForThread,
  ThreadIdType                  itkNotUsed(threadId))
{
  using ImageConstPointer = typename InputImageType::ConstPointer;
  using OutputPointer = typename OutputImageType::Pointer;

  const ImageConstPointer inputPtr = this->GetInput();
  const OutputPointer     outputPtr = this->GetOutput();

  using ConstIteratorType = ImageRegionConstIterator<InputImageType>;
  using IteratorType = ImageRegionIterator<OutputImageType>;
  ConstIteratorType inIt(inputPtr, outputRegionForThread);
  IteratorType      outIt(outputPtr, outputRegionForThread);

  const PixelType negFarValue = -m_FarValue;

  // Initialize output image. This needs to be done regardless of the
  // NarrowBanding or Full implementation
  while (!inIt.IsAtEnd())
  {
    if (inIt.Get() > m_LevelSetValue)
    {
      outIt.Set(m_FarValue);
    }
    else if (inIt.Get() < m_LevelSetValue)
    {
      outIt.Set(negFarValue);
    }
    else
    {
      outIt.Set(PixelType{});
    }
    ++inIt;
    ++outIt;
  }
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::ThreadedGenerateDataFull(
  const OutputImageRegionType & outputRegionForThread,
  ThreadIdType                  itkNotUsed(threadId))
{
  using ImageConstPointer = typename InputImageType::ConstPointer;
  using OutputPointer = typename OutputImageType::Pointer;

  const ImageConstPointer inputPtr = this->GetInput();
  const OutputPointer     outputPtr = this->GetOutput();

  InputSizeType radiusIn;
  SizeType      radiusOut;

  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    radiusIn[n] = 2;
    radiusOut[n] = 1;
  }

  // Define Neighborhood iterator
  ConstNeighborhoodIterator<InputImageType> inNeigIt(radiusIn, inputPtr, outputRegionForThread);
  NeighborhoodIterator<OutputImageType>     outNeigIt(radiusOut, outputPtr, outputRegionForThread);
  // Get Stride information to move across dimension
  std::vector<OffsetValueType> stride(ImageDimension, 0);

  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    stride[n] = inNeigIt.GetStride(n);
  }

  const unsigned int center = inNeigIt.Size() / 2;

  for (inNeigIt.GoToBegin(); !inNeigIt.IsAtEnd(); ++inNeigIt, ++outNeigIt)
  {
    ComputeValue(inNeigIt, outNeigIt, center, stride);
  }
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::ThreadedGenerateDataBand(
  const OutputImageRegionType & itkNotUsed(outputRegionForThread),
  ThreadIdType                  threadId)
{
  const typename InputImageType::ConstPointer inputPtr = this->GetInput();
  const typename OutputImageType::Pointer     outputPtr = this->GetOutput();

  // Tasks:
  // 1. Initialize whole output image (done in ThreadedGenerateData)
  // 2. Wait for threads (done in ThreadedGenerateData)
  // 3. Computation over the narrowband
  auto       bandIt = m_NarrowBandRegion[threadId].Begin;
  const auto bandEnd = m_NarrowBandRegion[threadId].End;

  InputSizeType radiusIn;
  SizeType      radiusOut;
  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    radiusIn[n] = 2;
    radiusOut[n] = 1;
  }

  // Create neighborhood iterator
  InputNeighbordIteratorType     inNeigIt(radiusIn, inputPtr, inputPtr->GetRequestedRegion());
  OutputNeighborhoodIteratorType outNeigIt(radiusOut, outputPtr, outputPtr->GetRequestedRegion());

  // Get Stride information to move across dimension
  std::vector<OffsetValueType> stride(ImageDimension, 0);

  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    stride[n] = inNeigIt.GetStride(n);
  }
  const unsigned int center = inNeigIt.Size() / 2;

  while (bandIt != bandEnd)
  {
    inNeigIt.SetLocation(bandIt->m_Index);
    outNeigIt.SetLocation(bandIt->m_Index);

    ComputeValue(inNeigIt, outNeigIt, center, stride);

    ++bandIt;
  } // Band iterator
}

template <typename TInputImage, typename TOutputImage>
void
IsoContourDistanceImageFilter<TInputImage, TOutputImage>::ComputeValue(const InputNeighbordIteratorType &   inNeigIt,
                                                                       OutputNeighborhoodIteratorType &     outNeigIt,
                                                                       unsigned int                         center,
                                                                       const std::vector<OffsetValueType> & stride)
{
  const PixelRealType val0 = static_cast<PixelRealType>(inNeigIt.GetPixel(center)) - m_LevelSetValue;
  const bool          sign = (val0 > 0);

  PixelRealType grad0[ImageDimension];

  // Compute gradient at val0
  for (unsigned int ng = 0; ng < ImageDimension; ++ng)
  {
    grad0[ng] =
      static_cast<PixelRealType>(inNeigIt.GetNext(ng, 1)) - static_cast<PixelRealType>(inNeigIt.GetPrevious(ng, 1));
  }

  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    const PixelRealType val1 = static_cast<PixelRealType>(inNeigIt.GetPixel(center + stride[n])) - m_LevelSetValue;

    const bool neighSign = (val1 > 0);

    if (sign != neighSign)
    {
      PixelRealType grad1[ImageDimension];

      for (unsigned int ng = 0; ng < ImageDimension; ++ng)
      {
        grad1[ng] = static_cast<PixelType>(inNeigIt.GetPixel(center + stride[n] + stride[ng])) -
                    static_cast<PixelType>(inNeigIt.GetPixel(center + stride[n] - stride[ng]));
      }
      PixelRealType diff;
      if (sign)
      {
        diff = val0 - val1;
      }
      else
      {
        diff = val1 - val0;
      }
      if (diff < NumericTraits<PixelRealType>::min())
      {
        itkGenericExceptionMacro("diff " << diff << " < NumericTraits< PixelRealType >::min()");
        continue;
      }

      // Interpolate values
      PixelRealType grad[ImageDimension];

      constexpr PixelRealType alpha0 = 0.5; // Interpolation factor
      constexpr PixelRealType alpha1 = 0.5; // Interpolation factor

      PixelRealType norm = 0.;

      for (unsigned int ng = 0; ng < ImageDimension; ++ng)
      {
        grad[ng] = (grad0[ng] * alpha0 + grad1[ng] * alpha1) / (2. * static_cast<PixelRealType>(m_Spacing[ng]));
        norm += grad[ng] * grad[ng];
      }
      norm = std::sqrt(norm);

      if (norm > NumericTraits<PixelRealType>::min())
      {
        const PixelRealType val = itk::Math::abs(grad[n]) * m_Spacing[n] / norm / diff;

        const PixelRealType               valNew0 = val0 * val;
        const PixelRealType               valNew1 = val1 * val;
        const std::lock_guard<std::mutex> lockGuard(m_Mutex);
        if (itk::Math::abs(static_cast<double>(valNew0)) < itk::Math::abs(static_cast<double>(outNeigIt.GetNext(n, 0))))
        {
          outNeigIt.SetNext(n, 0, static_cast<PixelType>(valNew0));
        }
        if (itk::Math::abs(static_cast<double>(valNew1)) < itk::Math::abs(static_cast<double>(outNeigIt.GetNext(n, 1))))
        {
          outNeigIt.SetNext(n, 1, static_cast<PixelType>(valNew1));
        }
      }
      else
      {
        itkExceptionMacro("Gradient norm is lower than pixel precision");
      }
    } // end if (sign != signNeigh)
  } // end for n
}

} // namespace itk

#endif
