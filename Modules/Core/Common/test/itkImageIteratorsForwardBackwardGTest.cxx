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

#include "itkImageRegionIteratorWithIndex.h"
#include "itkGTest.h"

TEST(ImageIteratorsForwardBackward, ConvertedLegacyTest)
{

  std::cout << "Creating an image" << std::endl;
  using ImageType = itk::Image<unsigned short, 3>;

  auto myImage = ImageType::New();

  auto size = ImageType::SizeType::Filled(4);

  const ImageType::RegionType region{ size };

  myImage->SetRegions(region);
  myImage->Allocate();

  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  using ConstIteratorType = itk::ImageRegionConstIteratorWithIndex<ImageType>;

  IteratorType it(myImage, region);

  auto value = ImageType::PixelType{};

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

  value = ImageType::PixelType{};

  while (!ot.IsAtEnd())
  {
    value++;

    ASSERT_EQ(ot.Get(), value) << "Error in forward pass. Test failed at index " << ot.GetIndex();
    ++ot;
  }

  std::cout << "      PASSED !" << std::endl;

  // Verification
  std::cout << "Verifying the data backwards... ";

  ot.GoToReverseBegin();
  --ot;
  --value;
  while (!ot.IsAtReverseEnd())
  {

    ASSERT_EQ(ot.Get(), value) << "Error in backwards pass. Test failed at index " << ot.GetIndex();
    value--;
    --ot;
  }

  std::cout << "      PASSED !" << std::endl;

  // Verification
  ConstIteratorType cot(myImage, region);
  std::cout << "Const Iterator: Verifying the data forwards... ";

  value = ImageType::PixelType{};

  while (!cot.IsAtEnd())
  {
    value++;

    ASSERT_EQ(cot.Get(), value) << "Error in forward pass. Test failed at index " << cot.GetIndex();
    ++cot;
  }

  std::cout << "      PASSED !" << std::endl;

  // Verification
  std::cout << "Const Iterator : Verifying the data backwards... ";

  cot.GoToReverseBegin();
  --cot;
  --value;
  while (!cot.IsAtReverseEnd())
  {

    ASSERT_EQ(cot.Get(), value) << "Error in backwards pass. Test failed at index " << cot.GetIndex();
    value--;
    --cot;
  }

  std::cout << "      PASSED !" << std::endl;

  std::cout << std::endl << "Test passed" << std::endl;
}
