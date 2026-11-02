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
#include "itkLabelImageToLabelMapFilter.h"
#include "itkGTest.h"

namespace
{
void
zeroSizeCase()
{
  // test filter with zero sized image
  constexpr unsigned int ImageDimension{ 3 };
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, ImageDimension>;
  auto p_filter = itk::LabelImageToLabelMapFilter<ImageType>::New();
  auto p_image = ImageType::New();

  // The image region is empty by default: do not set any region to it and allocate memory
  p_image->AllocateInitialized();

  p_filter->SetInput(p_image);
  p_filter->Update();
}
} // namespace

TEST(LabelImageToLabelMapFilter, ConvertedLegacyTest)
{
  constexpr int Dimension{ 2 };

  using LabelObjectType = itk::LabelObject<unsigned long, Dimension>;
  using IndexType = LabelObjectType::IndexType;
  using LabelMapType = itk::LabelMap<LabelObjectType>;
  using SizeType = LabelMapType::SizeType;
  using ImageType = itk::Image<unsigned char, Dimension>;

  using LabelImageToLabelMapFilterType = itk::LabelImageToLabelMapFilter<ImageType, LabelMapType>;

  auto image = ImageType::New();

  SizeType sizeIn;
  sizeIn[0] = 11;
  sizeIn[1] = 11;
  image->SetRegions(sizeIn);
  image->Allocate();
  image->FillBuffer(255);

  IndexType idxHorizontal;
  idxHorizontal[1] = 5;

  IndexType idxVertical;
  idxVertical[0] = 5;
  for (int ctr = 0; ctr < 11; ++ctr)
  {
    idxHorizontal[0] = ctr;
    idxVertical[1] = ctr;
    image->SetPixel(idxHorizontal, 1);
    image->SetPixel(idxVertical, 1);
  }

  idxHorizontal[1] = 7;
  idxVertical[0] = 7;

  for (int ctr = 0; ctr < 11; ++ctr)
  {
    idxHorizontal[0] = ctr;
    idxVertical[1] = ctr;
    image->SetPixel(idxHorizontal, 5);
    image->SetPixel(idxVertical, 2);
  }

  idxHorizontal[0] = 7;
  image->SetPixel(idxHorizontal, 3);

  auto conversion = LabelImageToLabelMapFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(conversion, LabelImageToLabelMapFilter, ImageToImageFilter);


  conversion->SetInput(image);
  conversion->SetBackgroundValue(255);
  conversion->Update();

  EXPECT_EQ(conversion->GetBackgroundValue(), 255u) << "Error conversion background value.";

  LabelMapType::Pointer map;
  map = conversion->GetOutput();

  EXPECT_EQ(map->GetBackgroundValue(), 255u) << "Error in Label Image (background).";

  map->Print(std::cout);

  std::cout << "Printing out map." << std::endl;
  for (int ctrI = 0; ctrI < 11; ++ctrI)
  {
    for (int ctrJ = 0; ctrJ < 11; ++ctrJ)
    {
      IndexType index;
      index[0] = ctrI;
      index[1] = ctrJ;
      const unsigned long val = map->GetPixel(index);
      std::cout << "Pixel[" << ctrI << ',' << ctrJ << "]: " << val << std::endl;
      if (((ctrI == 5) || (ctrJ == 5)) && (ctrI != 7) && (ctrJ != 7))
      {
        EXPECT_EQ(val, 1u) << "Error in Label Image (foreground).";
      }
      else
      {
        if ((ctrI == 7) && (ctrJ == 7))
        {
          EXPECT_EQ(val, 3u) << "Error in Label Image (foreground).";
          continue;
        }
        if (ctrJ == 7)
        {
          EXPECT_EQ(val, 5u) << "Error in Label Image (foreground).";
        }
        else if (ctrI == 7)
        {
          EXPECT_EQ(val, 2u) << "Error in Label Image (foreground).";
        }
        else
        {
          EXPECT_EQ(val, 255u) << "Error in Label Image (background).";
        }
      }
    }
  }

  zeroSizeCase();
}
