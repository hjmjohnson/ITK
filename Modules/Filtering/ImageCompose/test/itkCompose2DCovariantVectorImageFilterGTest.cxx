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

#include <iostream>
#include "itkComposeImageFilter.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(Compose2DCovariantVectorImageFilter, ConvertedLegacyTest)
{
  using PixelType = unsigned char;
  using InputImageType = itk::Image<PixelType, 3>;

  using OutputPixelType = itk::CovariantVector<float, 2>;
  using OutputImageType = itk::Image<OutputPixelType, 3>;

  using FilterType = itk::ComposeImageFilter<InputImageType, OutputImageType>;

  using RegionType = InputImageType::RegionType;
  using SizeType = InputImageType::SizeType;

  auto filter = FilterType::New();

  auto zeroImage = InputImageType::New();
  auto oneImage = InputImageType::New();

  constexpr SizeType size{ 2, 2, 2 };
  RegionType         region{ size };

  zeroImage->SetRegions(region);
  oneImage->SetRegions(region);

  zeroImage->Allocate();
  oneImage->Allocate();

  zeroImage->FillBuffer(29);
  oneImage->FillBuffer(51);

  filter->SetInput1(zeroImage);
  filter->SetInput2(oneImage);

  ASSERT_NO_THROW(filter->Update());

  using OutputImageType = FilterType::OutputImageType;

  const OutputImageType::Pointer twoVectorImage = filter->GetOutput();

  using OutputIterator = itk::ImageRegionIterator<OutputImageType>;
  using InputIterator = itk::ImageRegionIterator<InputImageType>;

  InputIterator i0(zeroImage, region);
  InputIterator i1(oneImage, region);

  OutputIterator ot(twoVectorImage, region);

  i0.GoToBegin();
  i1.GoToBegin();

  ot.GoToBegin();

  using OutputPixelType = OutputImageType::PixelType;

  while (!ot.IsAtEnd())
  {
    OutputPixelType outp = ot.Get();
    EXPECT_EQ(i0.Get(), outp[0]) << "Error in zeroth component";
    EXPECT_EQ(i1.Get(), outp[1]) << "Error in first component";
    ++ot;
    ++i0;
    ++i1;
  }
}
