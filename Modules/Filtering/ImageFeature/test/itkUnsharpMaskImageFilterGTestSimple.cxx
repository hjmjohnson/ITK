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

#include "itkUnsharpMaskImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkSimpleFilterWatcher.h"
#include "itkGTest.h"

TEST(UnsharpMaskImageFilter, ConvertedLegacyTestSimple)
{
  // Define the dimension of the images
  constexpr unsigned int Dimension{ 2 };

  // Define the pixel types of the images
  using PixelType = float;

  // Declare the types of the images
  using InputImageType = itk::Image<PixelType, Dimension>;

  // Declare the type of the index to access images
  using IndexType = itk::Index<Dimension>;

  // Declare the type of the size
  using SizeType = itk::Size<Dimension>;

  // Declare the type of the Region
  using RegionType = itk::ImageRegion<Dimension>;

  // Create the input image
  auto inputImage = InputImageType::New();

  // Define its size, and start index
  constexpr SizeType size{ 20, 4 };
  IndexType          start{};
  RegionType         region{ start, size };

  // Initialize the input image
  inputImage->SetRegions(region);
  inputImage->Allocate();

  // Declare an Iterator type for the input image
  using InputImageIteratorType = itk::ImageRegionIteratorWithIndex<InputImageType>;

  // Create one iterator for the input Image (this is a light object)
  InputImageIteratorType it(inputImage, inputImage->GetRequestedRegion());

  // Initialize the contents of the input image
  while (!it.IsAtEnd())
  {
    if (it.GetIndex()[0] > static_cast<itk::IndexValueType>(size[0] / 2))
    {
      it.Set(1.0);
    }
    else
    {
      it.Set(0.0);
    }

    ++it;
  }

  // Declare the type for the itk::UnsharpMaskImageFilter
  using UnsharpMaskImageFilterFilterType = itk::UnsharpMaskImageFilter<InputImageType>;

  using GradientImageType = UnsharpMaskImageFilterFilterType::OutputImageType;

  // Create the filter
  auto filter = UnsharpMaskImageFilterFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, UnsharpMaskImageFilter, ImageToImageFilter);

  const itk::SimpleFilterWatcher watchit(filter);

  // Connect the input images
  filter->SetInput(inputImage);


  UnsharpMaskImageFilterFilterType::InternalPrecisionType threshold = -0.1;
  filter->SetThreshold(threshold);

  EXPECT_THROW(filter->Update(), itk::ExceptionObject);


  // Set the filter properties
  constexpr UnsharpMaskImageFilterFilterType::SigmaArrayType::ValueType sigma{ 2.5 };
  filter->SetSigma(sigma);

  UnsharpMaskImageFilterFilterType::SigmaArrayType sigmas = filter->GetSigmas();

  constexpr double tolerance{ 10e-6 };
  for (unsigned int i = 0; i < sigmas.Size(); ++i)
  {
    const UnsharpMaskImageFilterFilterType::SigmaArrayType::ValueType sigma2 = sigmas[i];
    EXPECT_NEAR(sigma, sigma2, tolerance) << "Error in the Sigma values along the [" << i << "]-th dimension.";
  }

  constexpr UnsharpMaskImageFilterFilterType::InternalPrecisionType amount{ 0.8 };
  filter->SetAmount(amount);
  EXPECT_EQ(amount, filter->GetAmount());

  threshold = 0.01;
  filter->SetThreshold(threshold);
  EXPECT_EQ(threshold, filter->GetThreshold());

  constexpr bool clamp{ std::is_integral_v<UnsharpMaskImageFilterFilterType::OutputPixelType> };
  filter->SetClamp(clamp);
  EXPECT_EQ(clamp, filter->GetClamp());

  if (clamp)
  {
    filter->ClampOn();
    EXPECT_EQ(true, filter->GetClamp());
  }
  else
  {
    filter->ClampOff();
    EXPECT_EQ(false, filter->GetClamp());
  }

  // Execute the filter
  ASSERT_NO_THROW(filter->Update());

  // Get the Smart Pointer to the Filter Output
  // It is important to do it AFTER the filter is Updated
  // Because the object connected to the output may be changed
  // by another during GenerateData() call
  const GradientImageType::Pointer outputImage = filter->GetOutput();

  // check that output is correct near the step
  start[0] = 9;
  constexpr float mins[4]{ -0.21f, -0.33f, 1.32f, 1.20f };
  constexpr float maxs[4]{ -0.20f, -0.32f, 1.33f, 1.21f };
  for (unsigned int i = 0; i < 4; ++i)
  {
    EXPECT_GE(outputImage->GetPixel(start), mins[i]);
    EXPECT_LE(outputImage->GetPixel(start), maxs[i]);
    ++start[0];
  }

  // All objects should be automatically destroyed at this point
}
