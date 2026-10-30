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

/**
 *
 *  This program illustrates the AdaptImageFilter
 *
 *  The example shows how an Accessor can be used to
 *  convert an RGBPixel image to an image that has
 *  vector pixel type.
 *
 *  This allows access to an RGB image as an image of vectors.
 *
 */


#include "itkAdaptImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkRGBToVectorPixelAccessor.h"
#include "itkMath.h"
#include "itkGTest.h"

#include <algorithm> // For generate.
#include <random>    // For mt19937.


//-------------------------
//
//   Main code
//
//-------------------------
TEST(RGBToVectorAdaptImageFilter, ConvertedLegacyTest)
{


  //-------------------------------------
  //     Typedefs for convenience
  //-------------------------------------
  using RGBPixelType = itk::RGBPixel<float>;
  using RGBImageType = itk::Image<RGBPixelType, 2>;

  using myRGBIteratorType = itk::ImageRegionIteratorWithIndex<RGBImageType>;

  using AccessorType = itk::Accessor::RGBToVectorPixelAccessor<float>;

  using VectorPixelType = AccessorType::ExternalType;

  using myImageType = itk::Image<VectorPixelType, 2>;

  using myVectorIteratorType = itk::ImageRegionIteratorWithIndex<myImageType>;

  auto size = RGBImageType::SizeType::Filled(100);

  RGBImageType::IndexType index;
  index[0] = 0;
  index[1] = 0;

  const RGBImageType::RegionType region{ index, size };

  auto myImage = RGBImageType::New();


  myImage->SetRegions(region);
  myImage->Allocate();

  myRGBIteratorType it1(myImage, myImage->GetRequestedRegion());

  std::mt19937                          randomNumberEngine{};
  std::uniform_real_distribution<float> randomNumberDistribution{};

  // Value to initialize the pixels
  RGBImageType::PixelType color;

  // Initializing all the pixel in the image
  it1.GoToBegin();
  while (!it1.IsAtEnd())
  {
    std::generate(color.begin(), color.end(), [&randomNumberEngine, &randomNumberDistribution] {
      return randomNumberDistribution(randomNumberEngine);
    });
    it1.Set(color);
    ++it1;
  }

  // Convert to a Vector image
  using AdaptFilterType = itk::AdaptImageFilter<RGBImageType, myImageType, AccessorType>;

  auto adaptImageToVector = AdaptFilterType::New();

  adaptImageToVector->SetInput(myImage);
  adaptImageToVector->UpdateLargestPossibleRegion();

  myVectorIteratorType it(adaptImageToVector->GetOutput(), adaptImageToVector->GetOutput()->GetRequestedRegion());

  it.GoToBegin();
  it1.GoToBegin();
  while (!it.IsAtEnd())
  {
    VectorPixelType    v = it.Get();
    const RGBPixelType c = it1.Get();

    EXPECT_EQ(v[0], c.GetRed()) << "at index " << it.GetIndex();
    EXPECT_EQ(v[1], c.GetGreen()) << "at index " << it.GetIndex();
    EXPECT_EQ(v[2], c.GetBlue()) << "at index " << it.GetIndex();

    ++it;
    ++it1;
  }
}
