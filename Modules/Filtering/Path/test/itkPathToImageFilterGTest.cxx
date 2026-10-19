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

#include "itkPolyLineParametricPath.h"
#include "itkPathToImageFilter.h"
#include "itkMath.h"
#include "itkGTest.h"


TEST(PathToImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };
  using PixelType = double;

  using ImageType = itk::Image<PixelType, Dimension>;
  using PolyLineParametricPathType = itk::PolyLineParametricPath<Dimension>;
  using VertexType = PolyLineParametricPathType::VertexType;
  using PathToImageFilterType = itk::PathToImageFilter<PolyLineParametricPathType, ImageType>;


  // Set up the path
  auto path = PolyLineParametricPathType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path, PolyLineParametricPath, ParametricPath);

  std::cout << "Making a square Path with v0 at (30,30) and v2 at (33,33)" << std::endl;
  auto v = itk::MakeFilled<VertexType>(30);
  path->AddVertex(v);
  v[0] = 33;
  v[1] = 30;
  path->AddVertex(v);
  v.Fill(33);
  path->AddVertex(v);
  v[0] = 30;
  v[1] = 33;
  path->AddVertex(v);
  v.Fill(30);
  path->AddVertex(v);


  auto pathToImageFilter = PathToImageFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(pathToImageFilter, PathToImageFilter, ImageSource);

  pathToImageFilter->SetInput(path);

  constexpr PathToImageFilterType::ValueType pathValue{ 1 };
  pathToImageFilter->SetPathValue(pathValue);
  EXPECT_EQ(pathValue, pathToImageFilter->GetPathValue());

  constexpr PathToImageFilterType::ValueType backgroundValue{ 0 };
  pathToImageFilter->SetBackgroundValue(backgroundValue);
  EXPECT_EQ(backgroundValue, pathToImageFilter->GetBackgroundValue());

  auto size = ImageType::SizeType::Filled(256);
  pathToImageFilter->SetSize(size);
  EXPECT_EQ(size, pathToImageFilter->GetSize());

  // Test spacing
  //
  double pathImageSpacing[2];
  for (double & i : pathImageSpacing)
  {
    i = 1.0;
  }
  pathToImageFilter->SetSpacing(pathImageSpacing);
  const double * spacing_result = pathToImageFilter->GetSpacing();

  for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
  {
    EXPECT_EQ(spacing_result[i], 1.0);
  }

  // Test origin
  //
  double origin_double[2];
  for (double & i : origin_double)
  {
    i = 0.0;
  }
  pathToImageFilter->SetOrigin(origin_double);
  const double * origin_result = pathToImageFilter->GetOrigin();

  for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
  {
    EXPECT_EQ(origin_result[i], 0.0);
  }

  // Update the filter
  EXPECT_NO_THROW(pathToImageFilter->Update());

  const ImageType::Pointer image = pathToImageFilter->GetOutput();

  // Test the output image
  //

  ImageType::IndexType index;

  // Test only pixels on or in the path
  for (int i = 0; i <= 3; ++i)
  {
    for (int j = 0; j <= 3; ++j)
    {
      index[0] = 30 + i;
      index[1] = 30 + j;

      //           ? 0-Inside the closed path, but not on it : 1-On the path
      const double targetValue = (0 < i && i < 3 && 0 < j && j < 3) ? 0 : 1;
      EXPECT_DOUBLE_EQ(image->GetPixel(index), targetValue);
    }
  }
}
