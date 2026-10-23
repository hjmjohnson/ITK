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

#include "itkAffineTransform.h"
#include "itkResampleImageFilter.h"
#include "itkImageFileWriter.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(ResampleImageFilter, ConvertedLegacyTest)
{

  constexpr unsigned int VDimension{ 2 };

  using PixelType = float;
  using ImageType = itk::Image<PixelType, VDimension>;
  using ImageIndexType = ImageType::IndexType;
  using ImagePointerType = ImageType::Pointer;
  using ImageRegionType = ImageType::RegionType;
  using ImageSizeType = ImageType::SizeType;
  using CoordinateType = double;

  using AffineTransformType = itk::AffineTransform<CoordinateType, VDimension>;
  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, CoordinateType>;


  // Create and configure an image
  const ImagePointerType  image = ImageType::New();
  ImageIndexType          index = { { 0, 0 } };
  constexpr ImageSizeType size{ 18, 12 };
  const ImageRegionType   region{ index, size };
  image->SetLargestPossibleRegion(region);
  image->SetBufferedRegion(region);
  image->Allocate();

  // Fill image with a ramp
  for (itk::ImageRegionIteratorWithIndex<ImageType> iter(image, region); !iter.IsAtEnd(); ++iter)
  {
    index = iter.GetIndex();
    PixelType value = index[0] + index[1];
    iter.Set(value);
  }

  // Create an affine transformation
  auto aff = AffineTransformType::New();
  aff->Scale(0.5);

  // Create a linear interpolation image function
  auto interp = InterpolatorType::New();
  interp->SetInputImage(image);

  // Create and configure a resampling filter
  const itk::ResampleImageFilter<ImageType, ImageType>::Pointer resample =
    itk::ResampleImageFilter<ImageType, ImageType>::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(resample, ResampleImageFilter, ImageToImageFilter);

  resample->SetInput(image);
  EXPECT_EQ(image, resample->GetInput());

  resample->SetSize(size);
  EXPECT_EQ(size, resample->GetSize());

  resample->SetTransform(aff);
  EXPECT_EQ(aff, resample->GetTransform());

  resample->SetInterpolator(interp);
  EXPECT_EQ(interp, resample->GetInterpolator());

  index.Fill(0);
  resample->SetOutputStartIndex(index);
  EXPECT_EQ(index, resample->GetOutputStartIndex());

  // Run the resampling filter
  resample->Update();

  // Check if desired results were obtained
  bool                        passed = true;
  const ImageType::RegionType region2 = resample->GetOutput()->GetRequestedRegion();
  constexpr double            tolerance{ 1e-30 };
  for (itk::ImageRegionIteratorWithIndex<ImageType> iter2(resample->GetOutput(), region2); !iter2.IsAtEnd(); ++iter2)
  {
    index = iter2.GetIndex();
    PixelType       value = iter2.Get();
    const PixelType pixval = value;
    auto            expectedValue = static_cast<PixelType>((index[0] + index[1]) / 2.0);
    if (!itk::Math::FloatAlmostEqual(expectedValue, pixval, 10, tolerance))
    {
      std::cout << "Error in resampled image: Pixel " << index << "value    = " << value << "  "
                << "pixval   = " << pixval << "  "
                << "expected = " << expectedValue << std::endl;
      passed = false;
    }
  }

  // Test non-default values
  constexpr auto origin = itk::MakeFilled<ImageType::PointType>(1234.0);
  resample->SetOutputOrigin(origin);
  EXPECT_EQ(origin, resample->GetOutputOrigin());

  auto spacing = itk::MakeFilled<ImageType::SpacingType>(9876.0);
  resample->SetOutputSpacing(spacing);
  EXPECT_EQ(spacing, resample->GetOutputSpacing());

  // Report success or failure
  EXPECT_TRUE(passed) << "Resampling test failed";

  // Exercise error handling

  try
  {
    std::cout << "Setting interpolator to nullptr" << std::endl;
    passed = false;
    resample->SetInterpolator(nullptr);
    resample->Update();
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cout << err << std::endl;
    passed = true;
    resample->ResetPipeline();
    resample->SetInterpolator(interp);
  }

  EXPECT_TRUE(passed) << "Resampling test failed";
}
