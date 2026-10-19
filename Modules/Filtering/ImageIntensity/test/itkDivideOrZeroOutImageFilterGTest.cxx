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

#include "itkDivideOrZeroOutImageFilter.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkNumericTraits.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(DivideOrZeroOutImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 3 };
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;
  using DivideFilterType = itk::DivideOrZeroOutImageFilter<ImageType>;

  constexpr ImageType::SizeType size{ 10, 12, 14 };

  auto numeratorImage = ImageType::New();
  numeratorImage->SetRegions(size);
  numeratorImage->Allocate();
  numeratorImage->FillBuffer(1.0f);

  auto denominatorImage = ImageType::New();
  denominatorImage->SetRegions(size);
  denominatorImage->Allocate();

  // Set input test values
  denominatorImage->FillBuffer(1.0f);
  constexpr ImageType::IndexType zeroIndex{ 4, 5, 6 };
  denominatorImage->SetPixel(zeroIndex, 0.0f);

  // Instantiate and run the filter
  auto divider = DivideFilterType::New();
  divider->SetInput1(numeratorImage);
  divider->SetInput2(denominatorImage);
  divider->InPlaceOn();
  divider->UpdateLargestPossibleRegion();

  const ImageType::RegionType                       region = divider->GetOutput()->GetLargestPossibleRegion();
  itk::ImageRegionConstIteratorWithIndex<ImageType> iter(divider->GetOutput(), region);
  for (; !iter.IsAtEnd(); ++iter)
  {
    const ImageType::IndexType index = iter.GetIndex();
    if (index != zeroIndex)
    {
      EXPECT_EQ(iter.Get(), 1.0f) << "Incorrect value.";
    }
    else
    {
      EXPECT_EQ(iter.Get(), 0.0f) << "Incorrect value when denominator is below threshold.";
    }
  }

  divider->Print(std::cout);

  divider->SetThreshold(2.0f);
  EXPECT_EQ(divider->GetThreshold(), 2.0f) << "Threshold not set correctly.";

  divider->SetConstant(-2.3f);
  EXPECT_EQ(divider->GetConstant(), -2.3f) << "Constant not set correctly.";
}
