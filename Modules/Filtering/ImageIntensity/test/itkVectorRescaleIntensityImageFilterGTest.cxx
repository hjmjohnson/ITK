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

#include "itkMath.h"
#include "itkNumericTraits.h"
#include "itkVectorRescaleIntensityImageFilter.h"
#include "itkGTest.h"

#include <iostream>

TEST(VectorRescaleIntensityImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int VectorDimension{ 3 };

  using InputPixelType = itk::Vector<int, VectorDimension>;
  using OutputPixelType = itk::Vector<float, VectorDimension>;

  constexpr unsigned int ImageDimension{ 3 };

  using InputImageType = itk::Image<InputPixelType, ImageDimension>;
  using OutputImageType = itk::Image<OutputPixelType, ImageDimension>;

  auto                               inputImage = InputImageType::New();
  constexpr InputImageType::SizeType size{ 20, 20, 20 };
  InputImageType::RegionType         region{ size };

  InputPixelType pixelValue{ { 10, 20, 30 } };

  inputImage->SetRegions(region);
  inputImage->Allocate();
  inputImage->FillBuffer(pixelValue);

  using FilterType = itk::VectorRescaleIntensityImageFilter<InputImageType, OutputImageType>;

  auto filter = FilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, VectorRescaleIntensityImageFilter, UnaryFunctorImageFilter);

  filter->SetInput(inputImage);

  // Test exceptions
  double desiredMaximum = -1.0;
  filter->SetOutputMaximumMagnitude(desiredMaximum);
  EXPECT_THROW(filter->Update(), itk::ExceptionObject);

  desiredMaximum = 2.0;
  filter->SetOutputMaximumMagnitude(desiredMaximum);
  EXPECT_EQ(desiredMaximum, filter->GetOutputMaximumMagnitude());

  filter->SetFunctor(filter->GetFunctor());

  ASSERT_NO_THROW(filter->Update());

  const FilterType::InputRealType scale = filter->GetScale();
  std::cout << "Input scale value: " << static_cast<itk::NumericTraits<FilterType::InputRealType>::PrintType>(scale)
            << std::endl;

  const FilterType::InputRealType shift = filter->GetShift();
  std::cout << "Input scale value: " << static_cast<itk::NumericTraits<FilterType::InputRealType>::PrintType>(shift)
            << std::endl;

  const FilterType::InputRealType inputMaximumMagnitude = filter->GetInputMaximumMagnitude();
  std::cout << "Input maximum magnitude: "
            << static_cast<itk::NumericTraits<FilterType::InputRealType>::PrintType>(inputMaximumMagnitude)
            << std::endl;

  const OutputImageType::ConstPointer outputImage = filter->GetOutput();

  using IteratorType = itk::ImageRegionConstIterator<OutputImageType>;

  IteratorType ot(outputImage, outputImage->GetBufferedRegion());

  ot.GoToBegin();

  constexpr double tolerance{ 1e-3 };

  const double factor = desiredMaximum / static_cast<double>(pixelValue.GetNorm());

  while (!ot.IsAtEnd())
  {
    const OutputPixelType outputValue = ot.Get();
    for (unsigned int k = 0; k < VectorDimension; ++k)
    {
      if (itk::Math::NotAlmostEquals(outputValue[k], itk::NumericTraits<OutputPixelType>::ValueType{}))
      {
        EXPECT_NEAR(static_cast<double>(outputValue[k]), static_cast<double>(pixelValue[k] * factor), tolerance)
          << "Input  Pixel Value = " << pixelValue << ", Output Pixel Value = " << outputValue;
      }
    }
    ++ot;
  }
}
