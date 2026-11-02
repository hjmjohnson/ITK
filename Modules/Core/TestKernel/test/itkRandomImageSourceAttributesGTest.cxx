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

#include "itkRandomImageSource.h"
#include "itkGTest.h"


namespace
{
template <typename TImage>
void
itkRandomImageSourceAttributesTestHelper(const typename TImage::SizeType      size,
                                         const typename TImage::SpacingType   spacing,
                                         const typename TImage::PointType     origin,
                                         const typename TImage::DirectionType direction,
                                         const typename TImage::ValueType     min,
                                         const typename TImage::ValueType     max)
{

  using ImageSourceType = itk::RandomImageSource<TImage>;
  auto randomImageSource = ImageSourceType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(randomImageSource, RandomImageSource, ImageSource);


  randomImageSource->SetSize(size);
  EXPECT_EQ(*size.GetSize(), *randomImageSource->GetSize());

  randomImageSource->SetSpacing(spacing);
  EXPECT_EQ(spacing, randomImageSource->GetSpacing());

  randomImageSource->SetOrigin(origin);
  EXPECT_EQ(origin, randomImageSource->GetOrigin());

  randomImageSource->SetDirection(direction);
  EXPECT_EQ(direction, randomImageSource->GetDirection());

  randomImageSource->SetMin(min);
  EXPECT_EQ(min, randomImageSource->GetMin());

  randomImageSource->SetMax(max);
  EXPECT_EQ(max, randomImageSource->GetMax());
}
} // namespace


TEST(RandomImageSourceAttributes, ConvertedLegacyTest)
{

  constexpr unsigned int Dimension2D{ 2 };
  constexpr unsigned int Dimension3D{ 3 };

  using PixelType = float;

  {
    using ImageType2D = itk::Image<PixelType, Dimension2D>;

    constexpr ImageType2D::SizeType   size{ 25, 25 };
    const ImageType2D::SpacingType    spacing{ { { 0.7, 2.1 } } };
    const ImageType2D::PointType      origin{ { { -1.7, 5.2 } } };
    constexpr itk::SpacePrecisionType d[4]{ 0, 1.0, 1.0, 0 };
    const ImageType2D::DirectionType  direction = ImageType2D::DirectionType::InternalMatrixType(d);
    constexpr ImageType2D::ValueType  min{ 0.0 };
    constexpr ImageType2D::ValueType  max{ 1000.0 };

    itkRandomImageSourceAttributesTestHelper<ImageType2D>(size, spacing, origin, direction, min, max);
  }

  {
    using ImageType3D = itk::Image<PixelType, Dimension3D>;

    constexpr ImageType3D::SizeType   size{ 14, 17, 36 };
    const ImageType3D::SpacingType    spacing{ { { 0.7, 0.4, 1.2 } } };
    const ImageType3D::PointType      origin{ { { -1.7, 5.2, 3.4 } } };
    constexpr itk::SpacePrecisionType d[9]{ 0, 1.0, 0, 1.0, 0, 0, 0, 1.0, 0 };
    const ImageType3D::DirectionType  direction = ImageType3D::DirectionType::InternalMatrixType(d);
    constexpr ImageType3D::ValueType  min{ 0.0 };
    constexpr ImageType3D::ValueType  max{ 10.0 };

    itkRandomImageSourceAttributesTestHelper<ImageType3D>(size, spacing, origin, direction, min, max);
  }


  std::cout << "Test finished." << std::endl;
}
