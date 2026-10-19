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


#include "itkNeighborhoodOperatorImageFunction.h"

#include "itkGaussianOperator.h"
#include "itkGTest.h"

TEST(NeighborhoodOperatorImageFunction, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 3 };
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;
  using NeighborhoodOperatorType = itk::GaussianOperator<PixelType, Dimension>;
  using FunctionType = itk::NeighborhoodOperatorImageFunction<ImageType, PixelType>;

  // Create and allocate the image
  auto                          image = ImageType::New();
  constexpr ImageType::SizeType size{ 50, 50, 50 };
  ImageType::RegionType         region = { size };

  image->SetRegions(region);
  image->Allocate();

  constexpr ImageType::PixelType initialValue{ 27 };
  image->FillBuffer(initialValue);


  auto function = FunctionType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(function, NeighborhoodOperatorImageFunction, ImageFunction);


  function->SetInputImage(image);

  NeighborhoodOperatorType oper;
  oper.CreateToRadius(3);

  function->SetOperator(oper);

  auto index = itk::Index<3>::Filled(25);

  // EvaluateAtIndex
  const FunctionType::OutputType Blur = function->EvaluateAtIndex(index);

  // since the input image is constant
  // the should be equal to the initial value
  EXPECT_NEAR(initialValue, Blur, 10e-7) << "Error in Blur computation";

  // EvaluateAtContinuousIndex

  auto continuousIndex = itk::MakeFilled<FunctionType::ContinuousIndexType>(25);

  function->EvaluateAtContinuousIndex(continuousIndex);

  // EvaluateAtPoint

  FunctionType::PointType point;
  point[0] = 25;
  point[1] = 25;
  point[2] = 25;

  function->Evaluate(point);


  std::cout << function << std::endl;
}
