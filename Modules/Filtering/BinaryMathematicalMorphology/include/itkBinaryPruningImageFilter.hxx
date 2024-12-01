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
#ifndef itkBinaryPruningImageFilter_hxx
#define itkBinaryPruningImageFilter_hxx

#include <iostream>

#include "itkImageRegionIterator.h"

namespace itk
{
/**
 *    Constructor
 */
template <typename TInputImage, typename TOutputImage>
BinaryPruningImageFilter<TInputImage, TOutputImage>::BinaryPruningImageFilter()
{
  this->SetNumberOfRequiredOutputs(1);

  OutputImagePointer const pruneImage = OutputImageType::New();
  this->SetNthOutput(0, pruneImage.GetPointer());

  m_Iteration = 3;
}

/**
 *  Return the pruning Image pointer
 */
template <typename TInputImage, typename TOutputImage>
auto
BinaryPruningImageFilter<TInputImage, TOutputImage>::GetPruning() -> OutputImageType *
{
  return dynamic_cast<OutputImageType *>(this->ProcessObject::GetOutput(0));
}

/**
 *  Prepare data for computation
 */
template <typename TInputImage, typename TOutputImage>
void
BinaryPruningImageFilter<TInputImage, TOutputImage>::PrepareData()
{
  itkDebugMacro("PrepareData Start");
  OutputImagePointer const pruneImage = GetPruning();

  InputImagePointer const inputImage = dynamic_cast<const TInputImage *>(ProcessObject::GetInput(0));

  pruneImage->SetBufferedRegion(pruneImage->GetRequestedRegion());
  pruneImage->Allocate();

  typename OutputImageType::RegionType const region = pruneImage->GetRequestedRegion();

  ImageRegionConstIterator<TInputImage> it(inputImage, region);
  ImageRegionIterator<TOutputImage>     ot(pruneImage, region);

  itkDebugMacro("PrepareData: Copy input to output");

  while (!ot.IsAtEnd())
  {
    ot.Set(static_cast<typename OutputImageType::PixelType>(it.Get()));
    ++it;
    ++ot;
  }
  itkDebugMacro("PrepareData End");
}

/**
 *  Post processing for computing thinning
 */
template <typename TInputImage, typename TOutputImage>
void
BinaryPruningImageFilter<TInputImage, TOutputImage>::ComputePruneImage()
{
  itkDebugMacro("ComputeThinImage Start");
  OutputImagePointer const pruneImage = GetPruning();

  typename OutputImageType::RegionType const region = pruneImage->GetRequestedRegion();

  auto                     radius = MakeFilled<typename NeighborhoodIteratorType::RadiusType>(1);
  NeighborhoodIteratorType ot(radius, pruneImage, region);

  typename NeighborhoodIteratorType::OffsetType const offset1 = { { -1, -1 } };
  typename NeighborhoodIteratorType::OffsetType const offset2 = { { -1, 0 } };
  typename NeighborhoodIteratorType::OffsetType const offset3 = { { -1, 1 } };
  typename NeighborhoodIteratorType::OffsetType const offset4 = { { 0, 1 } };
  typename NeighborhoodIteratorType::OffsetType const offset5 = { { 1, 1 } };
  typename NeighborhoodIteratorType::OffsetType const offset6 = { { 1, 0 } };
  typename NeighborhoodIteratorType::OffsetType const offset7 = { { 1, -1 } };
  typename NeighborhoodIteratorType::OffsetType const offset8 = { { 0, -1 } };

  unsigned int count = 0;
  while (count < m_Iteration)
  {
    ot.GoToBegin();
    while (!ot.IsAtEnd())
    {
      if (ot.GetCenterPixel())
      {
        PixelType genus = ot.GetPixel(offset1) + ot.GetPixel(offset2);
        genus += ot.GetPixel(offset3) + ot.GetPixel(offset4);
        genus += ot.GetPixel(offset5) + ot.GetPixel(offset6);
        genus += ot.GetPixel(offset7) + ot.GetPixel(offset8);
        if (genus < 2)
        {
          genus = 0;
          ot.SetCenterPixel(genus);
        }
      }

      ++ot;
    }
    ++count;
  }
  itkDebugMacro("ComputeThinImage End");
}

/**
 *  Generate PruneImage
 */
template <typename TInputImage, typename TOutputImage>
void
BinaryPruningImageFilter<TInputImage, TOutputImage>::GenerateData()
{
  this->PrepareData();

  itkDebugMacro("GenerateData: Computing Thinning Image");
  this->ComputePruneImage();
} // end GenerateData()

/**
 *  Print Self
 */
template <typename TInputImage, typename TOutputImage>
void
BinaryPruningImageFilter<TInputImage, TOutputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Pruning image: " << std::endl;
  os << indent << "Iteration: " << m_Iteration << std::endl;
}
} // end namespace itk

#endif
