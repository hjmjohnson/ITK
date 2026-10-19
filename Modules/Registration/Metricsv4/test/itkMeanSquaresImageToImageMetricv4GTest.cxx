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
#include "itkMeanSquaresImageToImageMetricv4.h"
#include "itkTranslationTransform.h"
#include "itkMath.h"
#include "itkGTest.h"

/* Simple test to verify that class builds and runs.
 * Results are not verified. See ImageToImageMetricv4Test
 * for verification of basic metric functionality.
 *
 * TODO Numerical verification.
 */

TEST(MeanSquaresImageToImageMetricv4, ConvertedLegacyTest)
{

  constexpr unsigned int imageSize{ 5 };
  constexpr unsigned int imageDimensionality{ 3 };
  using ImageType = itk::Image<double, imageDimensionality>;

  auto                        size = ImageType::SizeType::Filled(imageSize);
  const ImageType::RegionType region{ size };

  /* Create simple test images. */
  auto fixedImage = ImageType::New();
  fixedImage->SetRegions(region);
  fixedImage->Allocate();

  auto movingImage = ImageType::New();
  movingImage->SetRegions(region);
  movingImage->Allocate();

  /* Fill images */
  itk::ImageRegionIterator<ImageType> itFixed(fixedImage, region);
  itFixed.GoToBegin();
  unsigned int count = 1;
  while (!itFixed.IsAtEnd())
  {
    itFixed.Set(count * count);
    count++;
    ++itFixed;
  }

  itk::ImageRegionIteratorWithIndex<ImageType> itMoving(movingImage, region);

  itMoving.GoToBegin();
  count = 1;

  while (!itMoving.IsAtEnd())
  {
    itMoving.Set(1.0 / (count * count));
    count++;
    ++itMoving;
  }

  /* Transforms */
  using FixedTransformType = itk::TranslationTransform<double, imageDimensionality>;
  using MovingTransformType = itk::TranslationTransform<double, imageDimensionality>;

  auto fixedTransform = FixedTransformType::New();
  auto movingTransform = MovingTransformType::New();

  fixedTransform->SetIdentity();
  movingTransform->SetIdentity();

  /* The metric */
  using MetricType = itk::MeanSquaresImageToImageMetricv4<ImageType, ImageType, ImageType>;

  auto metric = MetricType::New();

  /* Assign images and transforms.
   * By not setting a virtual domain image or virtual domain settings,
   * the metric will use the fixed image for the virtual domain. */
  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedTransform(fixedTransform);
  metric->SetMovingTransform(movingTransform);

  /* Initialize. */
  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize());

  // Evaluate with GetValueAndDerivative
  MetricType::MeasureType    valueReturn1 = NAN;
  MetricType::DerivativeType derivativeReturn;
  std::cout << "Calling GetValueAndDerivative..." << std::endl;
  ASSERT_NO_THROW(metric->GetValueAndDerivative(valueReturn1, derivativeReturn));

  /* Re-initialize. */
  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize());

  MetricType::MeasureType valueReturn2 = NAN;
  std::cout << "Calling GetValue..." << std::endl;
  ASSERT_NO_THROW(valueReturn2 = metric->GetValue());

  // Test same value returned by different methods
  std::cout << "Check Value return values..." << std::endl;
  if (itk::Math::NotExactlyEquals(valueReturn1, valueReturn2))
  {
    std::cerr << "Results for Value don't match: " << valueReturn1 << ", " << valueReturn2 << std::endl;
  }
  else
  {
    std::cout << "Metric value = " << valueReturn1 << std::endl;
    std::cout << "Gradient value = " << derivativeReturn << std::endl;
  }

  // Test that using floating point correction produces
  // a different result
  std::cout << "Testing with different floating point correction settings." << std::endl;
  metric->SetMaximumNumberOfWorkUnits(1);
  metric->SetUseFloatingPointCorrection(false); // default
  MetricType::DerivativeType derivativeWithOutFPC;
  metric->GetValueAndDerivative(valueReturn1, derivativeWithOutFPC);
  metric->SetUseFloatingPointCorrection(true);
  metric->SetFloatingPointCorrectionResolution(1e1); // severe truncation
  MetricType::DerivativeType derivativeWithFPC;
  metric->GetValueAndDerivative(valueReturn1, derivativeWithFPC);
  EXPECT_NE(derivativeWithFPC, derivativeWithOutFPC)
    << "Expected different derivative result when using floating-point correction";
}
