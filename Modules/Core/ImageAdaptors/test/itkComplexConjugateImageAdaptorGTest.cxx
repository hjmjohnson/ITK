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

#include "itkComplexConjugateImageAdaptor.h"
#include "itkImageRegionIterator.h"
#include <random>
#include "itkGTest.h"


using PixelType = std::complex<float>;
using ImageType = itk::Image<PixelType, 2>;
using AdaptorType = itk::ComplexConjugateImageAdaptor<ImageType>;

TEST(ComplexConjugateImageAdaptor, ConvertedLegacyTest)
{
  // Create a test image.
  auto                          image = ImageType::New();
  constexpr ImageType::SizeType size{ 10, 10 };
  image->SetRegions(size);
  image->Allocate();
  const ImageType::RegionType region = image->GetLargestPossibleRegion();

  std::mt19937                          randomNumberEngine;
  std::uniform_real_distribution<float> randomNumberDistribution;

  itk::ImageRegionIterator<ImageType> iter(image, region);
  for (iter.GoToBegin(); !iter.IsAtEnd(); ++iter)
  {
    const PixelType pixel(randomNumberDistribution(randomNumberEngine), randomNumberDistribution(randomNumberEngine));
    iter.Set(pixel);
  }

  // Create adaptor.
  auto adaptor = AdaptorType::New();
  adaptor->SetImage(image);

  // Iterate over the pixels and check the functioning of the adaptor.
  itk::ImageRegionIterator<ImageType>   iterA(image, region);
  itk::ImageRegionIterator<AdaptorType> iterB(adaptor, region);

  for (iterA.GoToBegin(), iterB.GoToBegin(); !iterA.IsAtEnd(); ++iterA, ++iterB)
  {
    const PixelType imageValue = iterA.Get();
    const PixelType adaptedValue = iterB.Get();

    // Check that the adapted value is as expected.
    EXPECT_EQ(imageValue, std::conj(adaptedValue)) << "Unexpected adapted pixel value.";

    // Try setting the value and reading it again.
    iterB.Set(adaptedValue);
    const PixelType newValue = iterB.Get();
    EXPECT_EQ(adaptedValue, newValue) << "Setting adapted pixel value failed.";
  }

  // To improve code coverage
  adaptor->Print(std::cout);
}
