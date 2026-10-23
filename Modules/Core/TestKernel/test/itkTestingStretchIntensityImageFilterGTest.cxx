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

#include "itkGTest.h"
#include "itkTestingStretchIntensityImageFilter.h"
#include "itkStatisticsImageFilter.h"
#include "itkImageRegionIterator.h"

TEST(TestingStretchIntensityImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };
  using PixelType = short;
  using ImageType = itk::Image<PixelType, Dimension>;
  using StretchFilterType = itk::Testing::StretchIntensityImageFilter<ImageType>;
  using StatsFilterType = itk::StatisticsImageFilter<ImageType>;

  constexpr ImageType::SizeType imageSize{ 32, 32 };
  auto                          image = ImageType::New();
  image->SetRegions(imageSize);
  image->Allocate();
  PixelType i = -511;
  for (itk::ImageRegionIterator<ImageType> it(image, image->GetLargestPossibleRegion()); !it.IsAtEnd(); ++it, ++i)
  {
    it.Set(i);
  }

  auto stretchFilter = StretchFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(stretchFilter, StretchIntensityImageFilter, ImageSource);

  stretchFilter->SetInput(image);

  int       outputMinimumPixelValue = 16384;
  int       outputMaximumPixelValue = -5000;
  PixelType outputMinPix(outputMinimumPixelValue);
  PixelType outputMaxPix(outputMaximumPixelValue);
  stretchFilter->SetOutputMinimum(outputMinPix);
  stretchFilter->SetOutputMaximum(outputMaxPix);

  EXPECT_THROW(stretchFilter->Update(), itk::ExceptionObject);

  outputMinimumPixelValue = -5000;
  outputMaximumPixelValue = 16384;
  outputMinPix = outputMinimumPixelValue;
  outputMaxPix = outputMaximumPixelValue;
  stretchFilter->SetOutputMinimum(outputMinPix);
  stretchFilter->SetOutputMaximum(outputMaxPix);

  EXPECT_EQ(outputMinimumPixelValue, stretchFilter->GetOutputMinimum());
  EXPECT_EQ(outputMaximumPixelValue, stretchFilter->GetOutputMaximum());


  EXPECT_NO_THROW(stretchFilter->Update());

  std::cout << "Scale: " << stretchFilter->GetScale() << std::endl;
  std::cout << "Shift: " << stretchFilter->GetShift() << std::endl;

  EXPECT_EQ(stretchFilter->GetInputMinimum(), -511);
  EXPECT_EQ(stretchFilter->GetInputMaximum(), 512);

  auto statsFilter = StatsFilterType::New();
  statsFilter->SetInput(stretchFilter->GetOutput());

  EXPECT_NO_THROW(statsFilter->Update());

  EXPECT_EQ(outputMinimumPixelValue, statsFilter->GetMinimum());
  EXPECT_EQ(outputMaximumPixelValue, statsFilter->GetMaximum());

  std::cout << "Output Minimum: " << statsFilter->GetMinimum() << std::endl
            << "Output Maximum: " << statsFilter->GetMaximum() << std::endl
            << "Output Mean: " << statsFilter->GetMean() << std::endl
            << "Output Variance: " << statsFilter->GetVariance() << std::endl
            << "Output Sigma: " << statsFilter->GetSigma() << std::endl;
}
