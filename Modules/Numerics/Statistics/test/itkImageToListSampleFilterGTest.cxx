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
// The example tests the class itk::Statistics::ImageToListSampleFilter.
// The class is capable of generating an itk::ListSample from an image
// confined to a mask (if specified). This test exercises that.


#include "itkImageToListSampleFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkGTest.h"

namespace
{
using ImageType = itk::Image<unsigned int, 2>;
using MaskImageType = itk::Image<unsigned char, 2>;

//------------------------------------------------------------------------
// Creates a 10 x 10 image of unsigned chars with pixel at location
// (x,y) being yx. ie Pixel at (6,4) = 46.
//
ImageType::Pointer
CreateImage()
{
  auto image = ImageType::New();

  ImageType::IndexType start{};
  ImageType::SizeType  size;


  size[0] = 10;
  size[1] = 10;

  const ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;
  IteratorType it(image, region);
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    it.Set(it.GetIndex()[1] * 10 + it.GetIndex()[0]);
    ++it;
  }
  return image;
}

//------------------------------------------------------------------------
// Creates a 10 x 10 image of unsigned chars with pixel from (2,3) - (8,5) as
// 255 and rest as 0
MaskImageType::Pointer
CreateMaskImage()
{
  MaskImageType::IndexType start{};
  auto                     size = itk::MakeFilled<MaskImageType::SizeType>(10);


  const MaskImageType::RegionType region(start, size);
  auto                            image = MaskImageType::CreateInitialized(region);

  MaskImageType::IndexType startMask;
  MaskImageType::SizeType  sizeMask;

  startMask[0] = 2;
  startMask[1] = 3;

  sizeMask[0] = 7;
  sizeMask[1] = 3;

  const MaskImageType::RegionType regionMask(startMask, sizeMask);
  using IteratorType = itk::ImageRegionIteratorWithIndex<MaskImageType>;
  IteratorType it(image, regionMask);
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    it.Set(static_cast<unsigned char>(255));
    ++it;
  }
  return image;
}

//------------------------------------------------------------------------
// Creates a 13 x 17 image for testing verification of LargestPossibleRegion
MaskImageType::Pointer
CreateLargerMaskImage()
{
  MaskImageType::IndexType start;
  MaskImageType::SizeType  size;

  start[0] = 0;
  start[1] = 0;

  size[0] = 13;
  size[1] = 17;

  const MaskImageType::RegionType region(start, size);
  return MaskImageType::CreateInitialized(region);
}
} // namespace


TEST(ImageToListSampleFilter, ConvertedLegacyTest)
{
  const ImageType::Pointer     image = CreateImage();
  const MaskImageType::Pointer maskImage = CreateMaskImage();

  // Generate a list sample from "image" confined to the mask, "maskImage".
  using ImageToListSampleFilterType = itk::Statistics::ImageToListSampleFilter<ImageType, MaskImageType>;
  auto filter = ImageToListSampleFilterType::New();

  // Invoke update before adding an input. An exception should be
  // thrown.
  EXPECT_THROW(filter->Update(), itk::ExceptionObject)
    << "[FAILED] Exception should have been thrown since Update() is invoked without setting an input";
  // Restore the pipeline after the exception
  filter->ResetPipeline();

  EXPECT_EQ(filter->GetInput(), nullptr) << "[FAILED] GetInput() should return nullptr if the input has not been set";

  EXPECT_EQ(filter->GetMaskImage(), nullptr)
    << "[FAILED] GetMaskImage() should return nullptr if mask image has not been set";


  // generate list sample without a mask image
  filter->SetInput(image);
  filter->Update();


  // use a mask image
  filter->SetMaskImage(maskImage);
  filter->SetMaskValue(255);
  filter->Update();

  std::cout << filter->GetNameOfClass() << std::endl;
  filter->Print(std::cout);


  const ImageToListSampleFilterType::MaskPixelType pixelType = filter->GetMaskValue();

  EXPECT_EQ(pixelType, 255) << "Problem in SetMaskValue() GetMaskValue()";

  using ListSampleType = ImageToListSampleFilterType::ListSampleType;
  const ListSampleType * list = filter->GetOutput();

  // Check the sum of the pixels in the list sample. This should
  // be 945
  ListSampleType::ConstIterator lit = list->Begin();
  unsigned int                  sum = 0;
  while (lit != list->End())
  {
    sum += lit.GetMeasurementVector()[0];
    ++lit;
  }

  EXPECT_EQ(sum, 945u) << "[FAILED] Computed sum of pixels in the list sample (masked)";


  // Set on purpose a mask of inconsistent LargestPossibleRegion
  filter->SetMaskImage(CreateLargerMaskImage());

  EXPECT_THROW(filter->Update(), itk::ExceptionObject)
    << "Exception should have been thrown since the mask has a different LargestPossibleRegion.";
}
