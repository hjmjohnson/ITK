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
#include "itkBilateralImageFilter.h"
#include "itkNullImageToImageFilterDriver.hxx"
#include "itkGTest.h"

TEST(BilateralImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };

  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;

  using FilterType = itk::BilateralImageFilter<ImageType, ImageType>;

  // Set up filter
  auto filter = FilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, BilateralImageFilter, ImageToImageFilter);


  double                domainSigmaVal = 2.0;
  FilterType::ArrayType domainSigma = FilterType::ArrayType::Filled(domainSigmaVal);
  filter->SetDomainSigma(domainSigmaVal);
  EXPECT_EQ(domainSigma, filter->GetDomainSigma());

  domainSigmaVal = 2.5;
  domainSigma.Fill(domainSigmaVal);
  filter->SetDomainSigma(domainSigma);
  EXPECT_EQ(domainSigma, filter->GetDomainSigma());

  constexpr double domainMu{ 2.5 };
  filter->SetDomainMu(domainMu);
  EXPECT_EQ(domainMu, filter->GetDomainMu());

  constexpr double rangeSigma{ 35.0f };
  filter->SetRangeSigma(rangeSigma);
  EXPECT_EQ(rangeSigma, filter->GetRangeSigma());

  filter->SetFilterDimensionality(Dimension);
  EXPECT_EQ(Dimension, filter->GetFilterDimensionality());

  constexpr bool automaticKernelSize{ true };
  ITK_GTEST_SET_GET_BOOLEAN(filter, AutomaticKernelSize, automaticKernelSize);

  constexpr FilterType::SizeType::SizeValueType radiusVal = 2;
  constexpr FilterType::SizeType                radius = FilterType::SizeType::Filled(radiusVal);
  filter->SetRadius(radius);
  EXPECT_EQ(radius, filter->GetRadius());

  constexpr unsigned long numberOfRangeGaussianSamples{ 150 };
  filter->SetNumberOfRangeGaussianSamples(numberOfRangeGaussianSamples);
  EXPECT_EQ(numberOfRangeGaussianSamples, filter->GetNumberOfRangeGaussianSamples());

  // Run test
  itk::Size<Dimension> sz;
  sz[0] = 250;
  sz[1] = 250;
  itk::NullImageToImageFilterDriver<ImageType, ImageType> test1;
  test1.SetImageSize(sz);
  test1.SetFilter(filter);

  EXPECT_NO_THROW(test1.Execute());
}
