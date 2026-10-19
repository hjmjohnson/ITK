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

#include "itkRLEImage.h"
#include "itkGTest.h"

TEST(RLEImageIteratorsForwardBackward, ConvertedLegacyTest)
{
  std::cout << "Creating an image" << std::endl;
  using ImageType = itk::RLEImage<unsigned short>;

  ImageType::Pointer myImage = ImageType::New();

  ImageType::SizeType size;

  size[0] = 4;
  size[1] = 4;
  size[2] = 4;

  ImageType::IndexType start;
  start.Fill(0);

  ImageType::RegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  myImage->SetLargestPossibleRegion(region);
  myImage->SetBufferedRegion(region);
  myImage->SetRequestedRegion(region);
  myImage->Allocate();

  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  using ConstIteratorType = itk::ImageRegionConstIteratorWithIndex<ImageType>;

  IteratorType it(myImage, region);

  ImageType::PixelType value;

  value = itk::NumericTraits<ImageType::PixelType>::ZeroValue();

  // Store information on the Image
  std::cout << "Storing data on the image ... " << std::endl;

  while (!it.IsAtEnd())
  {
    value++;
    it.Set(value);
    ++it;
  }


  // Verification
  IteratorType ot(myImage, region);
  std::cout << "Verifying the data forwards... ";

  value = itk::NumericTraits<ImageType::PixelType>::ZeroValue();

  while (!ot.IsAtEnd())
  {
    value++;

    EXPECT_EQ(ot.Get(), value) << "Error in forward pass" << std::endl
                               << "Values don't correspond to what was stored " << std::endl
                               << "Test failed at index " << ot.GetIndex();
    ++ot;
  }

  // Verification
  std::cout << "Verifying the data backwards... ";

  ot.GoToEnd();
  do
  {
    --ot;
    EXPECT_EQ(ot.Get(), value) << "Error in backwards pass" << std::endl
                               << "Values don't correspond to what was stored " << std::endl
                               << "Test failed at index " << ot.GetIndex();
    value--;
  } while (!ot.IsAtBegin());

  // Verification
  ConstIteratorType cot(myImage, region);
  std::cout << "Const Iterator: Verifying the data forwards... ";

  value = itk::NumericTraits<ImageType::PixelType>::ZeroValue();

  while (!cot.IsAtEnd())
  {
    value++;

    EXPECT_EQ(cot.Get(), value) << "Error in forward pass" << std::endl
                                << "Values don't correspond to what was stored " << std::endl
                                << "Test failed at index " << cot.GetIndex();
    ++cot;
  }

  // Verification
  std::cout << "Const Iterator : Verifying the data backwards... ";

  cot.GoToEnd();
  do
  {
    --cot;
    EXPECT_EQ(cot.Get(), value) << "Error in backwards pass" << std::endl
                                << "Values don't correspond to what was stored " << std::endl
                                << "Test failed at index " << cot.GetIndex();
    value--;
  } while (!cot.IsAtBegin());
}
