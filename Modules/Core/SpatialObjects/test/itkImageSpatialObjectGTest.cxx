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
// Disable warning for long symbol names in this file only

/*
 * This is a test file for the itkImageSpatialObject class.
 * The supported pixel types does not include itkRGBPixel, itkRGBAPixel, etc...
 * So far it only allows to manage images of simple types like unsigned short,
 * unsigned int, or itk::Vector<...>.
 */


#include "itkImageRegionIterator.h"

#include "itkImageSpatialObject.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkGTest.h"
#include <iomanip>


TEST(ImageSpatialObject, ConvertedLegacyTest)
{
#define VDimension 3

  using ScalarType = double;
  using Pixel = unsigned short;
  using ImageType = itk::Image<Pixel, VDimension>;
  using ImageSpatialObject = itk::ImageSpatialObject<VDimension, Pixel>;
  using Iterator = itk::ImageRegionIterator<ImageType>;
  using PointType = itk::Point<ScalarType, VDimension>;

  auto                          image = ImageType::New();
  constexpr ImageType::SizeType size{ 10, 10, 10 };
  auto                          origin = itk::MakeFilled<ImageType::PointType>(5);

  ImageType::RegionType region{ size };
  image->SetOrigin(origin);
  image->SetRegions(region);
  image->Allocate();

  Iterator it(image, region);
  Pixel    p = 0;

  for (; !it.IsAtEnd(); ++it, ++p)
  {
    it.Set(p);
  }
  it.GoToBegin();

  auto imageSO = ImageSpatialObject::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(imageSO, ImageSpatialObject, SpatialObject);


  constexpr ImageSpatialObject::IndexType sliceNumber{};
  imageSO->SetSliceNumber(sliceNumber);
  EXPECT_EQ(sliceNumber, imageSO->GetSliceNumber());

  imageSO->SetImage(image);
  imageSO->Update();

  auto offset = itk::MakeFilled<ImageSpatialObject::TransformType::OffsetType>(5);

  imageSO->GetModifiableObjectToParentTransform()->SetOffset(offset);
  imageSO->Update();


  auto r = itk::MakeFilled<PointType>(9);
  auto q = itk::MakeFilled<PointType>(15);

  std::cout << "Bounding Box = " << imageSO->GetMyBoundingBoxInWorldSpace()->GetBounds() << std::endl;

  EXPECT_FALSE(imageSO->IsInsideInWorldSpace(r));
  EXPECT_TRUE(imageSO->IsInsideInWorldSpace(q));

  q.Fill(15.1);
  double expectedValue = 555;

  double returnedValue = NAN;
  EXPECT_NO_THROW(imageSO->ValueAtInWorldSpace(q, returnedValue));


  std::cout << "ValueAt()...";
  EXPECT_DOUBLE_EQ(returnedValue, expectedValue) << "Test failed!" << '\n'
                                                 << "Error in ValueAt at point " << q << '\n'
                                                 << "Expected value " << expectedValue << '\n'
                                                 << " differs from " << returnedValue;

  std::cout << "[PASSED]" << std::endl;


  ImageSpatialObject::DerivativeVectorType derivative;
  imageSO->DerivativeAtInWorldSpace(q, 1, derivative);
  Pixel                                    expectedPixel = 1;
  ImageSpatialObject::DerivativeVectorType expectedDerivative;
  expectedDerivative[0] = expectedPixel;
  expectedPixel = 10;
  expectedDerivative[1] = expectedPixel;
  expectedPixel = 100;
  expectedDerivative[2] = expectedPixel;

  EXPECT_EQ(derivative, expectedDerivative);


  // Now testing the ValueAt() with an interpolator
  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType>;
  auto interpolator = InterpolatorType::New();
  imageSO->SetInterpolator(interpolator);
  EXPECT_EQ(interpolator, imageSO->GetInterpolator());

  expectedValue = 566.1;

  EXPECT_NO_THROW(imageSO->ValueAtInWorldSpace(q, returnedValue));


  std::cout << "ValueAt() with interpolator...";
  double epsilon = 0.001;
  EXPECT_LE(itk::Math::Absolute(returnedValue - expectedValue), epsilon)
    << std::setprecision(static_cast<int>(itk::Math::Absolute(std::log10(epsilon)))) << "Test failed!" << '\n'
    << "Error in ValueAt at point " << q << '\n'
    << "Expected value " << expectedValue << '\n'
    << " differs from " << returnedValue << " by more than " << epsilon;

  std::cout << "[PASSED]" << std::endl;


  imageSO->DerivativeAtInWorldSpace(q, 1, derivative);
  expectedDerivative[0] = 1;
  expectedDerivative[1] = 10;
  expectedDerivative[2] = 100;
  std::cout << "DerivativeAt() with interpolator ...";
  epsilon = 0.00001;
  EXPECT_LE(itk::Math::Absolute(derivative[0] - expectedDerivative[0]), epsilon)
    << std::setprecision(static_cast<int>(itk::Math::Absolute(std::log10(epsilon)))) << "Test failed!" << '\n'
    << "Error in ValueAt at point " << q << '\n'
    << "Expected value " << expectedDerivative << '\n'
    << " differs from " << derivative << " by more than " << epsilon;
  EXPECT_LE(itk::Math::Absolute(derivative[1] - expectedDerivative[1]), epsilon)
    << std::setprecision(static_cast<int>(itk::Math::Absolute(std::log10(epsilon)))) << "Test failed!" << '\n'
    << "Error in ValueAt at point " << q << '\n'
    << "Expected value " << expectedDerivative << '\n'
    << " differs from " << derivative << " by more than " << epsilon;
  EXPECT_LE(itk::Math::Absolute(derivative[2] - expectedDerivative[2]), epsilon)
    << std::setprecision(static_cast<int>(itk::Math::Absolute(std::log10(epsilon)))) << "Test failed!" << '\n'
    << "Error in ValueAt at point " << q << '\n'
    << "Expected value " << expectedDerivative << '\n'
    << " differs from " << derivative << " by more than " << epsilon;

  std::cout << "[PASSED]" << std::endl;


  std::cout << "Test finished." << std::endl;
}
