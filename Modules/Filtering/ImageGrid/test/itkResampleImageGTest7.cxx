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
#include "itkCastImageFilter.h"
#include "itkPipelineMonitorImageFilter.h"
#include "itkResampleImageFilter.h"
#include "itkStreamingImageFilter.h"
#include "itkGTest.h"
#include "itkMath.h"

/* itkResampleImageFilter output compared to streamed output
 */

TEST(ResampleImageFilter, ConvertedLegacyTest7)
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
  constexpr ImageSizeType size{ 64, 64 };
  const ImageRegionType   region{ index, size };
  image->SetRegions(region);
  image->Allocate();

  // Fill image with a ramp
  itk::ImageRegionIteratorWithIndex<ImageType> iter(image, region);
  for (iter.GoToBegin(); !iter.IsAtEnd(); ++iter)
  {
    index = iter.GetIndex();
    const PixelType value = index[0] + index[1];
    iter.Set(value);
  }

  // Create an affine transformation
  auto aff = AffineTransformType::New();
  aff->Scale(0.9);

  // Create a linear interpolation image function
  auto interp = InterpolatorType::New();
  interp->SetInputImage(image);

  // Create and configure a resampling filter
  const itk::ResampleImageFilter<ImageType, ImageType>::Pointer resample =
    itk::ResampleImageFilter<ImageType, ImageType>::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(resample, ResampleImageFilter, ImageToImageFilter);
  resample->SetInterpolator(interp);

  const auto upstream = itk::CastImageFilter<ImageType, ImageType>::New();
  upstream->SetInput(image);
  using MonitorType = itk::PipelineMonitorImageFilter<ImageType>;
  const auto monitor = MonitorType::New();
  monitor->SetInput(upstream->GetOutput());
  resample->SetInput(monitor->GetOutput());
  EXPECT_EQ(monitor->GetOutput(), resample->GetInput());

  resample->SetSize(size);
  EXPECT_EQ(size, resample->GetSize());

  resample->SetTransform(aff);
  EXPECT_EQ(aff, resample->GetTransform());

  resample->SetInterpolator(interp);
  EXPECT_EQ(interp, resample->GetInterpolator());

  index.Fill(0);
  resample->SetOutputStartIndex(index);
  EXPECT_EQ(index, resample->GetOutputStartIndex());

  using StreamerType = itk::StreamingImageFilter<ImageType, ImageType>;
  auto streamer = StreamerType::New();

  std::cout << "Test with normal AffineTransform." << std::endl;
  streamer->SetInput(resample->GetOutput());

  // Run the resampling filter without streaming, i.e. 1 StreamDivisions
  unsigned char numStreamDiv = 1; // do not split, i.e. do not stream
  streamer->SetNumberOfStreamDivisions(numStreamDiv);
  ASSERT_NO_THROW(streamer->UpdateLargestPossibleRegion());

  const ImagePointerType outputNoSDI = streamer->GetOutput(); // save output for later comparison
  outputNoSDI->DisconnectPipeline();                          // disconnect to create new output

  monitor->ClearPipelineSavedInformation();

  image->Modified();
  numStreamDiv = 8;
  streamer->SetNumberOfStreamDivisions(numStreamDiv);
  ASSERT_NO_THROW(streamer->UpdateLargestPossibleRegion());

  EXPECT_TRUE(monitor->VerifyInputFilterExecutedStreaming(static_cast<int>(numStreamDiv)))
    << "Streaming did not chunk the input as expected." << monitor;

  // Verify that we only requested a smaller chunk when streaming
  const ImageRegionType finalRequestedRegion(image->GetRequestedRegion());
  EXPECT_EQ(0, finalRequestedRegion.GetIndex(0));
  EXPECT_EQ(48, finalRequestedRegion.GetIndex(1));
  EXPECT_EQ(60u, finalRequestedRegion.GetSize(0));
  EXPECT_EQ(12u, finalRequestedRegion.GetSize(1));

  const ImagePointerType outputSDI = streamer->GetOutput();
  outputSDI->DisconnectPipeline();

  itk::ImageRegionIterator<ImageType> itNoSDI(outputNoSDI, outputNoSDI->GetLargestPossibleRegion());
  itk::ImageRegionIterator<ImageType> itSDI(outputSDI, outputSDI->GetLargestPossibleRegion());
  for (itNoSDI.GoToBegin(), itSDI.GoToBegin(); !itNoSDI.IsAtEnd() && !itSDI.IsAtEnd(); ++itNoSDI, ++itSDI)
  {
    EXPECT_FLOAT_EQ(itNoSDI.Value(), itSDI.Value())
      << "Error in pixel value at index [" << itNoSDI.ComputeIndex() << ']';
  }
  EXPECT_EQ(itNoSDI.IsAtEnd(), itSDI.IsAtEnd())
    << "Iterators don't agree on end of image at index [" << itNoSDI.ComputeIndex() << ']';

  // Test non default values
  constexpr auto origin = itk::MakeFilled<ImageType::PointType>(1234.0);
  resample->SetOutputOrigin(origin);
  EXPECT_EQ(origin, resample->GetOutputOrigin());

  auto spacing = itk::MakeFilled<ImageType::SpacingType>(9876.0);
  resample->SetOutputSpacing(spacing);
  EXPECT_EQ(spacing, resample->GetOutputSpacing());
}
