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

#include "itkEllipseSpatialObject.h"
#include "itkSpatialObjectToImageFilter.h"
#include "itkCommand.h"
#include "itkGTest.h"

namespace
{
class ShowProgressObject
{
public:
  ShowProgressObject(itk::ProcessObject * o) { m_Process = o; }
  void
  ShowProgress()
  {
    std::cout << "Progress " << m_Process->GetProgress() << std::endl;
  }
  itk::ProcessObject::Pointer m_Process;
};
} // namespace

TEST(SpatialObjectToImageFilter, ConvertedLegacyTest)
{
  using EllipseType = itk::EllipseSpatialObject<2>;

  auto ellipse = EllipseType::New();
  ellipse->SetRadiusInObjectSpace(10);
  ellipse->Update();

  // Center the circle in the image
  auto offset = itk::MakeFilled<EllipseType::TransformType::OffsetType>(25);
  ellipse->GetModifiableObjectToParentTransform()->SetOffset(offset);
  ellipse->Update();

  using ImageType = itk::Image<double, 2>;

  using SpatialObjectToImageFilterType = itk::SpatialObjectToImageFilter<EllipseType, ImageType>;
  auto imageFilter = SpatialObjectToImageFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(imageFilter, SpatialObjectToImageFilter, ImageSource);

  imageFilter->SetInput(ellipse);

  constexpr SpatialObjectToImageFilterType::ValueType insideValue{ 2 };
  imageFilter->SetInsideValue(insideValue);
  EXPECT_EQ(insideValue, imageFilter->GetInsideValue());

  constexpr SpatialObjectToImageFilterType::ValueType outsideValue{ 0 };
  imageFilter->SetOutsideValue(0);
  EXPECT_EQ(outsideValue, imageFilter->GetOutsideValue());

  constexpr unsigned int childrenDepth{ 1 };
  imageFilter->SetChildrenDepth(childrenDepth);
  EXPECT_EQ(childrenDepth, imageFilter->GetChildrenDepth());

  ImageType::IndexType indx;
  indx[0] = 10;
  indx[1] = 10;
  imageFilter->SetIndex(indx);
  EXPECT_EQ(indx, imageFilter->GetIndex());

  auto size = ImageType::SizeType::Filled(50);
  imageFilter->SetSize(size);
  EXPECT_EQ(size, imageFilter->GetSize());

  // Testing spacing
  std::cout << "Testing Spacing: ";

  constexpr float  floatCheckValue{ 1.5 };
  constexpr double doubleCheckValue{ 1.25 };
  constexpr float  vspacingFloat[2]{ floatCheckValue, floatCheckValue };
  constexpr double vspacingDouble[2]{ doubleCheckValue, doubleCheckValue };
  {
    imageFilter->SetSpacing(vspacingFloat);
    const double * spacing_result = imageFilter->GetSpacing();
    for (unsigned int i = 0; i < 2; ++i)
    {
      EXPECT_EQ(spacing_result[i], floatCheckValue) << "[FAILURE] floatCheckValue";
    }
  }
  {
    imageFilter->SetSpacing(vspacingDouble);
    const double * spacing_result = imageFilter->GetSpacing();
    for (unsigned int i = 0; i < 2; ++i)
    {
      EXPECT_EQ(spacing_result[i], doubleCheckValue) << "[FAILURE] doubleCheckValue";
    }
  }
  const auto spacing_vector_result = imageFilter->GetSpacingVector();
  for (unsigned int i = 0; i < 2; ++i)
  {
    EXPECT_EQ(spacing_vector_result[i], doubleCheckValue) << "[FAILURE] spacing_vector_result";
  }


  {
    // NOTE: Passing all zeros does not change the spacing, but the timestamp is modified.
    constexpr double allzeros[2]{ 0.0, 0.0 };
    imageFilter->Update();
    auto preTimestamp = imageFilter->GetTimeStamp();
    EXPECT_THROW(imageFilter->SetSpacing(allzeros), itk::ExceptionObject)
      << "[FAILURE] : Attempting to set spacing values to zero should have thrown an exception.";

    auto postTimestamp = imageFilter->GetTimeStamp();
    EXPECT_NE(preTimestamp, postTimestamp) << "Time Stamp not modified with passing all zero values to SetSpacing.";
    if (preTimestamp != postTimestamp)
    {
      std::cout << "Time Stamp modified." << std::endl;
    }
  }

  std::cout << "[PASSED]" << std::endl;

  // Testing Origin
  std::cout << "Testing Origin: ";

  constexpr float  voriginFloat[2]{ floatCheckValue, floatCheckValue };
  constexpr double voriginDouble[2]{ doubleCheckValue, doubleCheckValue };


  {
    imageFilter->SetOrigin(voriginFloat);
    const double * origin_result = imageFilter->GetOrigin();
    for (unsigned int i = 0; i < 2; ++i)
    {
      EXPECT_EQ(origin_result[i], floatCheckValue) << "[FAILURE]";
    }
  }
  {
    imageFilter->SetOrigin(voriginDouble);
    const double * origin_result = imageFilter->GetOrigin();
    for (unsigned int i = 0; i < 2; ++i)
    {
      EXPECT_EQ(origin_result[i], doubleCheckValue) << "[FAILURE]";
    }
  }

  const auto origin_point_result = imageFilter->GetOriginPoint();

  for (unsigned int i = 0; i < 2; ++i)
  {
    EXPECT_EQ(origin_point_result[i], doubleCheckValue) << "[FAILURE]";
  }


  std::cout << "[PASSED]" << std::endl;

  // Now test with common values
  constexpr double spacingDouble[2]{ 1.0, 1.0 };
  constexpr double originDouble[2]{ 0.0, 0.0 };
  imageFilter->SetSpacing(spacingDouble);
  imageFilter->SetOrigin(originDouble);
  // Testing PrintSelf
  std::cout << imageFilter << std::endl;

  // Test Progress Reporter
  ShowProgressObject progressWatch(imageFilter);
  using CommandType = itk::SimpleMemberCommand<ShowProgressObject>;
  auto command = CommandType::New();
  command->SetCallbackFunction(&progressWatch, &ShowProgressObject::ShowProgress);
  imageFilter->AddObserver(itk::ProgressEvent(), command);

  // Update the filter
  imageFilter->Update();

  const ImageType::Pointer image = imageFilter->GetOutput();

  std::cout << "Testing Output Image: ";

  ImageType::IndexType index;
  // Test only centered pixels
  for (int i = -5; i < 5; ++i)
  {
    for (int j = -5; j < 5; ++j)
    {
      index[0] = 25 + i;
      index[1] = 25 + j;

      EXPECT_EQ(image->GetPixel(index), 2.0) << "[FAILURE]";
    }
  }

  std::cout << "[PASSED]" << std::endl;

  // Test the UseObjectValue
  constexpr bool useObjectValue{ true };
  imageFilter->SetUseObjectValue(useObjectValue);
  ITK_GTEST_SET_GET_BOOLEAN(imageFilter, UseObjectValue, useObjectValue);

  imageFilter->Update();

  std::cout << "Print filter info:" << std::endl;
  std::cout << imageFilter << std::endl;

  std::cout << "Testing SetUseObjectValue: ";

  // Test only centered pixels
  for (int i = -5; i < 5; ++i)
  {
    for (int j = -5; j < 5; ++j)
    {
      index[0] = 25 + i;
      index[1] = 25 + j;

      EXPECT_EQ(image->GetPixel(index), 1.0) << "[FAILURE]";
    }
  }


  std::cout << "Test finished" << std::endl;
}
