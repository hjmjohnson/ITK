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

#include "itkMultiResolutionImageRegistrationMethod.h"
#include "itkTranslationTransform.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkRegularStepGradientDescentOptimizer.h"

#include "itkTextOutput.h"
#include "itkGTest.h"


/**
 *  This program test one instantiation of the
 *  itk::MultiResolutionImageRegistrationMethod class
 *
 *  This file tests initialization errors.
 */

TEST(MultiResolutionImageRegistrationMethod, ConvertedLegacyTest)
{

  itk::OutputWindow::SetInstance(itk::TextOutput::New().GetPointer());

  constexpr unsigned int dimension{ 3 };

  // Fixed Image Type
  using FixedImageType = itk::Image<float, dimension>;

  // Moving Image Type
  //  using MovingImageType = itk::Image<signed char,dimension>;
  using MovingImageType = itk::Image<float, dimension>;

  // Transform Type
  using TransformType = itk::TranslationTransform<double, dimension>;

  // Optimizer Type
  using OptimizerType = itk::RegularStepGradientDescentOptimizer;

  // Metric Type
  using MetricType = itk::MeanSquaresImageToImageMetric<FixedImageType, MovingImageType>;

  // Interpolation technique
  using InterpolatorType = itk::LinearInterpolateImageFunction<MovingImageType, double>;

  // Fixed Image Pyramid Type
  using FixedImagePyramidType = itk::RecursiveMultiResolutionPyramidImageFilter<FixedImageType, FixedImageType>;

  // Moving Image Pyramid Type
  using MovingImagePyramidType = itk::RecursiveMultiResolutionPyramidImageFilter<MovingImageType, MovingImageType>;


  // Registration Method
  using RegistrationType = itk::MultiResolutionImageRegistrationMethod<FixedImageType, MovingImageType>;


  auto metric = MetricType::New();
  auto transform = TransformType::New();
  auto optimizer = OptimizerType::New();
  auto fixedImage = FixedImageType::New();
  auto movingImage = MovingImageType::New();
  auto interpolator = InterpolatorType::New();
  auto fixedImagePyramid = FixedImagePyramidType::New();
  auto movingImagePyramid = MovingImagePyramidType::New();

  auto registration = RegistrationType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(registration, MultiResolutionImageRegistrationMethod, ProcessObject);


  auto size = FixedImageType::SizeType::Filled(8);

  const FixedImageType::RegionType region(size);
  fixedImage->SetRegions(region);
  fixedImage->Allocate();
  fixedImage->FillBuffer(3.0);

  movingImage->SetRegions(region);
  movingImage->Allocate();
  movingImage->FillBuffer(4.0);

  registration->SetMetric(metric);
  EXPECT_EQ(metric, registration->GetMetric());

  registration->SetOptimizer(optimizer);
  EXPECT_EQ(optimizer, registration->GetOptimizer());

  registration->SetTransform(transform);
  EXPECT_EQ(transform, registration->GetTransform());

  registration->SetFixedImage(fixedImage);
  EXPECT_EQ(fixedImage, registration->GetFixedImage());

  registration->SetMovingImage(movingImage);
  EXPECT_EQ(movingImage, registration->GetMovingImage());

  registration->SetInterpolator(interpolator);
  EXPECT_EQ(interpolator, registration->GetInterpolator());

  registration->SetFixedImagePyramid(fixedImagePyramid);
  EXPECT_EQ(fixedImagePyramid, registration->GetFixedImagePyramid());

  registration->SetMovingImagePyramid(movingImagePyramid);
  EXPECT_EQ(movingImagePyramid, registration->GetMovingImagePyramid());

  registration->SetFixedImageRegion(fixedImage->GetBufferedRegion());
  EXPECT_EQ(fixedImage->GetBufferedRegion(), registration->GetFixedImageRegion());

  constexpr itk::SizeValueType numberOfLevels{ 2 };
  registration->SetNumberOfLevels(numberOfLevels);
  EXPECT_EQ(numberOfLevels, registration->GetNumberOfLevels());

  using ParametersType = RegistrationType::ParametersType;
  ParametersType initialParameters(transform->GetNumberOfParameters(), 0);
  registration->SetInitialTransformParameters(initialParameters);
  EXPECT_EQ(initialParameters, registration->GetInitialTransformParameters());

  constexpr typename ParametersType::ValueType initialTransformParametersOfNextLevelVal(0.0);
  const ParametersType initialTransformParametersOfNextLevel(1, initialTransformParametersOfNextLevelVal);
  registration->SetInitialTransformParametersOfNextLevel(initialTransformParametersOfNextLevel);
  EXPECT_EQ(initialTransformParametersOfNextLevel, registration->GetInitialTransformParametersOfNextLevel());

  // Exercise Get methods
  std::cout << "CurrentLevel: " << registration->GetCurrentLevel() << std::endl;


  /****************************************************
   * Test out initialization errors
   ****************************************************/
#define TEST_INITIALIZATION_ERROR(ComponentName, badComponent, goodComponent) \
  registration->Set##ComponentName(badComponent);                             \
  EXPECT_THROW(registration->Update(), itk::ExceptionObject);                 \
  registration->Set##ComponentName(goodComponent);                            \
  ITK_MACROEND_NOOP_STATEMENT

  TEST_INITIALIZATION_ERROR(Metric, nullptr, metric);
  TEST_INITIALIZATION_ERROR(Optimizer, nullptr, optimizer);
  TEST_INITIALIZATION_ERROR(Transform, nullptr, transform);
  TEST_INITIALIZATION_ERROR(FixedImage, nullptr, fixedImage);
  TEST_INITIALIZATION_ERROR(MovingImage, nullptr, movingImage);
  TEST_INITIALIZATION_ERROR(Interpolator, nullptr, interpolator);
  TEST_INITIALIZATION_ERROR(FixedImagePyramid, nullptr, fixedImagePyramid);
  TEST_INITIALIZATION_ERROR(MovingImagePyramid, nullptr, movingImagePyramid);
  TEST_INITIALIZATION_ERROR(InitialTransformParameters, ParametersType(1), initialParameters);
}
