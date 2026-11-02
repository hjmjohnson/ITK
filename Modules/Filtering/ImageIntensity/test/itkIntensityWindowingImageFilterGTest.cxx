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

#include "itkIntensityWindowingImageFilter.h"
#include "itkMath.h"
#include "itkNumericTraits.h"
#include "itkRandomImageSource.h"
#include "itkGTest.h"

TEST(IntensityWindowingImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 3 };
  using PixelType = float;

  using TestInputImage = itk::Image<PixelType, Dimension>;
  using TestOutputImage = itk::Image<PixelType, Dimension>;

  auto                       size = TestInputImage::SizeType::Filled(64);
  TestInputImage::RegionType region{ size };


  using FilterType = itk::IntensityWindowingImageFilter<TestInputImage, TestOutputImage>;
  auto filter = FilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, IntensityWindowingImageFilter, UnaryFunctorImageFilter);

  // Generate a real image
  using SourceType = itk::RandomImageSource<TestInputImage>;
  auto                          source = SourceType::New();
  TestInputImage::SizeValueType randomSize[3] = { 17, 8, 20 };

  // Set up source
  source->SetSize(randomSize);

  constexpr double minValue{ -128.0 };
  constexpr double maxValue{ 127.0 };

  source->SetMin(static_cast<TestInputImage::PixelType>(minValue));
  source->SetMax(static_cast<TestInputImage::PixelType>(maxValue));

  filter->SetInput(source->GetOutput());

  constexpr double desiredMinimum{ -1.0 };
  constexpr double desiredMaximum{ 1.0 };

  constexpr float windowMinimum{ -50.0f };
  constexpr float windowMaximum{ 50.0f };

  filter->SetOutputMinimum(desiredMinimum);
  EXPECT_EQ(desiredMinimum, filter->GetOutputMinimum());

  filter->SetOutputMaximum(desiredMaximum);
  EXPECT_EQ(desiredMaximum, filter->GetOutputMaximum());

  filter->SetWindowMinimum(windowMinimum);
  EXPECT_EQ(windowMinimum, filter->GetWindowMinimum());

  filter->SetWindowMaximum(windowMaximum);
  EXPECT_EQ(windowMaximum, filter->GetWindowMaximum());

  std::cout << "Window minimum:maximum = " << windowMinimum << ':' << windowMaximum << ", equivalent window:level = "
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetWindow()) << ':'
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetLevel()) << std::endl;

  std::cout << "Gray level linear transformation scale = "
            << static_cast<itk::NumericTraits<FilterType::RealType>::PrintType>(filter->GetScale())
            << ", shift = " << static_cast<itk::NumericTraits<FilterType::RealType>::PrintType>(filter->GetShift())
            << std::endl;

  ASSERT_NO_THROW(filter->UpdateLargestPossibleRegion());

  ASSERT_NO_THROW(filter->SetFunctor(filter->GetFunctor()));

  using CalculatorType = itk::MinimumMaximumImageCalculator<TestOutputImage>;
  auto calculator = CalculatorType::New();

  calculator->SetImage(filter->GetOutput());

  calculator->Compute();

  constexpr double tolerance{ 1e-7 };

  const double obtainedMinimum = calculator->GetMinimum();
  const double obtainedMaximum = calculator->GetMaximum();

  EXPECT_NEAR(obtainedMinimum, desiredMinimum, tolerance) << "Error in minimum";

  EXPECT_NEAR(obtainedMaximum, desiredMaximum, tolerance) << "Error in maximum";

  constexpr float window{ 50.0f };
  constexpr float level{ 50.0f };

  filter->SetWindowLevel(window, level);

  std::cout << "Window:level = "
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetWindow()) << ':'
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetLevel())
            << ", equivalent window minimum:maximum = "
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetWindowMinimum()) << ':'
            << static_cast<itk::NumericTraits<FilterType::InputPixelType>::PrintType>(filter->GetWindowMaximum())
            << std::endl;

  ASSERT_NO_THROW(filter->UpdateLargestPossibleRegion());

  calculator->Compute();

  const double obtainedMinimum2 = calculator->GetMinimum();
  const double obtainedMaximum2 = calculator->GetMaximum();

  EXPECT_NEAR(obtainedMinimum2, desiredMinimum, tolerance) << "Error in minimum";

  EXPECT_NEAR(obtainedMaximum2, desiredMaximum, tolerance) << "Error in maximum";
}
