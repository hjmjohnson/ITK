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

#include "itkImageRandomIteratorWithIndex.h"
#include <iostream>

#include "itkImageRegionIteratorWithIndex.h"
#include "itkGTest.h"
#include "vnl/vnl_sample.h"

TEST(ImageRandomIterator, ConvertedLegacyTest)
{
  // The legacy test driver reseeds vnl_sample before every test.
  vnl_sample_reseed(8775070);
  std::cout << "Creating an image of indices" << std::endl;

  constexpr unsigned int ImageDimension{ 3 };

  using PixelType = itk::Index<ImageDimension>;

  using ImageType = itk::Image<PixelType, ImageDimension>;

  auto                          myImage = ImageType::New();
  const ImageType::ConstPointer myConstImage = myImage;

  ImageType::SizeType size0;

  size0[0] = 100;
  size0[1] = 100;
  size0[2] = 100;

  constexpr unsigned long numberOfSamples{ 10 };

  const ImageType::RegionType region0{ size0 };

  myImage->SetRegions(region0);
  myImage->Allocate();

  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  using RandomIteratorType = itk::ImageRandomIteratorWithIndex<ImageType>;

  using RandomConstIteratorType = itk::ImageRandomConstIteratorWithIndex<ImageType>;

  IteratorType it(myImage, region0);

  it.GoToBegin();
  ImageType::IndexType index0;

  // Fill an image with indices
  while (!it.IsAtEnd())
  {
    index0 = it.GetIndex();
    it.Set(index0);
    ++it;
  }


  // Sample the image
  RandomIteratorType ot(myImage, region0);
  ot.SetNumberOfSamples(numberOfSamples);
  ot.GoToBegin();


  std::cout << "Verifying non-const iterator... ";
  std::cout << "Random walk of the Iterator over the image " << std::endl;
  while (!ot.IsAtEnd())
  {
    index0 = ot.GetIndex();
    ASSERT_EQ(ot.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
    std::cout << index0 << std::endl;
    ++ot;
  }
  std::cout << "   Done ! " << std::endl;


  // Verification
  RandomConstIteratorType cot(myConstImage, region0);
  cot.SetNumberOfSamples(numberOfSamples);
  cot.GoToBegin();


  std::cout << "Verifying const iterator... ";
  std::cout << "Random walk of the Iterator over the image " << std::endl;

  while (!cot.IsAtEnd())
  {
    index0 = cot.GetIndex();
    ASSERT_EQ(cot.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
    std::cout << index0 << std::endl;
    ++cot;
  }
  std::cout << "   Done ! " << std::endl;

  // Verification
  std::cout << "Verifying iterator in reverse direction... " << std::endl;
  std::cout << "Should be a random walk too (a different one)" << std::endl;

  RandomIteratorType ior(myImage, region0);
  ior.SetNumberOfSamples(numberOfSamples);
  ior.GoToEnd();

  --ior;


  while (!ior.IsAtBegin())
  {
    index0 = ior.GetIndex();
    ASSERT_EQ(ior.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
    std::cout << index0 << std::endl;
    --ior;
  }
  std::cout << index0 << std::endl; // print the value at the beginning index
  std::cout << "   Done ! " << std::endl;

  // Verification
  std::cout << "Verifying const iterator in reverse direction... ";

  RandomConstIteratorType cor(myImage, region0);
  cor.SetNumberOfSamples(numberOfSamples); // 0=x, 1=y, 2=z
  cor.GoToEnd();

  --cor; // start at the end position

  while (!cor.IsAtBegin())
  {
    index0 = cor.GetIndex();
    ASSERT_EQ(cor.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
    std::cout << index0 << std::endl;
    --cor;
  }
  std::cout << index0 << std::endl; // print the value at the beginning index
  std::cout << "   Done ! " << std::endl;

  // Verification
  std::cout << "Verifying const iterator in both directions... ";

  RandomConstIteratorType dor(myImage, region0);
  dor.SetNumberOfSamples(numberOfSamples); // 0=x, 1=y, 2=z
  dor.GoToEnd();

  --dor; // start at the last valid pixel position

  for (unsigned int counter = 0; !dor.IsAtEnd(); ++counter)
  {
    index0 = dor.GetIndex();
    ASSERT_EQ(dor.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
    std::cout << index0 << std::endl;
    if (counter < 6)
    {
      --dor;
    }
    else
    {
      ++dor;
    }
  }
  std::cout << index0 << std::endl; // print the value at the beginning index
  std::cout << "   Done ! " << std::endl;


  // Verification of the Iterator in a subregion of the image
  {
    std::cout << "Verifying Iterator in a Region smaller than the whole image... " << std::endl;

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    RandomIteratorType cbot(myImage, region);

    cbot.SetNumberOfSamples(numberOfSamples); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    while (!cbot.IsAtEnd())
    {
      const ImageType::IndexType index = cbot.GetIndex();
      const ImageType::PixelType pixel = cbot.Get();

      ASSERT_EQ(index, pixel) << "Iterator in region test failed";

      ASSERT_TRUE(region.IsInside(index))
        << "Iterator in region test failed" << index << " is outside the region " << region;
      std::cout << index << std::endl;
      ++cbot;
    }

    std::cout << "   Done ! " << std::endl;
  }

  // Verification of the Const Iterator in a subregion of the image
  {
    std::cout << "Verifying Const Iterator in a Region smaller than the whole image... " << std::endl;

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    RandomConstIteratorType cbot(myImage, region);

    cbot.SetNumberOfSamples(numberOfSamples);
    cbot.GoToBegin();

    while (!cbot.IsAtEnd())
    {
      const ImageType::IndexType index = cbot.GetIndex();
      const ImageType::PixelType pixel = cbot.Get();

      ASSERT_EQ(index, pixel) << "Iterator in region test failed";
      ASSERT_TRUE(region.IsInside(index))
        << "Iterator in region test failed" << index << " is outside the region " << region;
      std::cout << index << std::endl;

      ++cbot;
    }

    std::cout << "   Done ! " << std::endl;
  }


  std::cout << "Test passed" << std::endl;
}
