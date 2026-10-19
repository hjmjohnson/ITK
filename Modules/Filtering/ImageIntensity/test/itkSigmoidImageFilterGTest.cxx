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

#include "itkImageRegionIteratorWithIndex.h"
#include "itkMath.h"
#include "itkSigmoidImageFilter.h"
#include "itkGTest.h"


TEST(SigmoidImageFilter, ConvertedLegacyTest)
{

  // Define the dimension of the images
  constexpr unsigned int ImageDimension{ 3 };

  // Declare the types of the images
  using InputPixelType = float;
  using OutputPixelType = float;

  using InputImageType = itk::Image<InputPixelType, ImageDimension>;
  using OutputImageType = itk::Image<OutputPixelType, ImageDimension>;

  // Declare appropriate Iterator types for each image
  using InputIteratorType = itk::ImageRegionIteratorWithIndex<InputImageType>;
  using OutputIteratorType = itk::ImageRegionIteratorWithIndex<OutputImageType>;

  // Declare the type of the size
  using SizeType = itk::Size<ImageDimension>;

  // Declare the type of the Region
  using RegionType = itk::ImageRegion<ImageDimension>;

  // Create the input images
  auto inputImage = InputImageType::New();

  // Define their size and region
  constexpr SizeType size{ 2, 2, 2 };
  RegionType         region{ size };

  // Initialize the input image
  inputImage->SetRegions(region);
  inputImage->Allocate();

  // Create one iterator for the input image (this is a light object)
  InputIteratorType it(inputImage, inputImage->GetBufferedRegion());

  // Initialize the content of the input image
  constexpr double value{ 30 };
  inputImage->FillBuffer(value);

  // Declare the type for the Sigmoid filter
  using FilterType = itk::SigmoidImageFilter<InputImageType, OutputImageType>;

  // Create the filter
  auto filter = FilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, SigmoidImageFilter, UnaryFunctorImageFilter);

  // Set the input image
  filter->SetInput(inputImage);

  // Set the filter parameters
  constexpr double alpha{ 2.0 };
  constexpr double beta{ 3.0 };

  filter->SetAlpha(alpha);
  EXPECT_EQ(alpha, filter->GetAlpha());

  filter->SetBeta(beta);
  EXPECT_EQ(beta, filter->GetBeta());

  constexpr OutputPixelType maximum{ 1.0 };
  constexpr OutputPixelType minimum{ -1.0 };

  filter->SetOutputMinimum(minimum);
  EXPECT_EQ(minimum, filter->GetOutputMinimum());

  filter->SetOutputMaximum(maximum);
  EXPECT_EQ(maximum, filter->GetOutputMaximum());

  filter->SetFunctor(filter->GetFunctor());

  // Execute the filter
  filter->Update();

  // Get the filter output
  const OutputImageType::Pointer outputImage = filter->GetOutput();

  // Create an iterator for going through the image output
  OutputIteratorType ot(outputImage, outputImage->GetRequestedRegion());

  // Check the content of the result image
  constexpr OutputImageType::PixelType epsilon{ 1e-6 };
  ot.GoToBegin();
  it.GoToBegin();
  while (!ot.IsAtEnd())
  {
    const InputImageType::PixelType  input = it.Get();
    const OutputImageType::PixelType output = ot.Get();
    const double                     x1 = (input - beta) / alpha;
    const double                     x2 = (maximum - minimum) * (1.0 / (1.0 + std::exp(-x1))) + minimum;
    const auto                       sigmoid = static_cast<OutputImageType::PixelType>(x2);
    EXPECT_NEAR(sigmoid, output, epsilon) << " sigmoid( " << input << ")";
    ++ot;
    ++it;
  }
}
