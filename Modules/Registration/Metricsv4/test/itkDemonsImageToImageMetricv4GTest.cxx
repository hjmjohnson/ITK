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
#include "itkDemonsImageToImageMetricv4.h"
#include "itkTranslationTransform.h"
#include "itkGaussianSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkGTest.h"
#include "itkMath.h"

/* Simple test to verify that class builds and runs.
 * Results are not verified. See ImageToImageMetricv4Test
 * for verification of basic metric functionality.
 *
 * TODO Numerical verification.
 */

TEST(DemonsImageToImageMetricv4, ConvertedLegacyTest)
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
  using TranslationTransformType = itk::TranslationTransform<double, imageDimensionality>;
  using DisplacementTransformType =
    itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, imageDimensionality>;

  auto translationTransform = TranslationTransformType::New();
  translationTransform->SetIdentity();

  auto displacementTransform = DisplacementTransformType::New();
  using DisplacementFieldType = DisplacementTransformType::DisplacementFieldType;
  auto field = DisplacementFieldType::New();
  field->SetRegions(fixedImage->GetLargestPossibleRegion());
  field->CopyInformation(fixedImage);
  field->Allocate();
  constexpr DisplacementTransformType::OutputVectorType zeroVector{};
  field->FillBuffer(zeroVector);
  displacementTransform->SetDisplacementField(field);
  displacementTransform->SetGaussianSmoothingVarianceForTheUpdateField(5);
  displacementTransform->SetGaussianSmoothingVarianceForTheTotalField(6);

  /* The metric */
  using MetricType = itk::DemonsImageToImageMetricv4<ImageType, ImageType, ImageType>;

  auto metric = MetricType::New();

  /* Assign images and transforms.
   * By not setting a virtual domain image or virtual domain settings,
   * the metric will use the fixed image for the virtual domain. */
  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedTransform(translationTransform);
  metric->SetMovingTransform(displacementTransform);

  /* Test 1st with fixed image gradient source. This is the default */
  metric->SetGradientSource(itk::ObjectToObjectMetricBaseTemplateEnums::GradientSource::GRADIENT_SOURCE_FIXED);
  EXPECT_EQ(metric->GetGradientSource(),
            itk::ObjectToObjectMetricBaseTemplateEnums::GradientSource::GRADIENT_SOURCE_FIXED)
    << "Failed setting fixed image gradient source.";

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

  /* Test with moving image as gradient source. The default is
   * to have the fixed image used for image gradients.  */
  metric->SetFixedTransform(translationTransform);
  metric->SetMovingTransform(displacementTransform);
  metric->SetGradientSource(itk::ObjectToObjectMetricBaseTemplateEnums::GradientSource::GRADIENT_SOURCE_MOVING);
  EXPECT_EQ(metric->GetGradientSource(),
            itk::ObjectToObjectMetricBaseTemplateEnums::GradientSource::GRADIENT_SOURCE_MOVING)
    << "Failed setting moving image gradient source.";

  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize());

  // Evaluate with GetValueAndDerivative
  std::cout << "Calling GetValueAndDerivative..." << std::endl;
  ASSERT_NO_THROW(metric->GetValueAndDerivative(valueReturn1, derivativeReturn));

  /* Re-initialize. */
  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize());

  std::cout << "Calling GetValue..." << std::endl;
  ASSERT_NO_THROW(valueReturn2 = metric->GetValue());

  // Test same value returned by different methods
  std::cout << "Check Value return values..." << std::endl;
  if (itk::Math::NotExactlyEquals(valueReturn1, valueReturn2))
  {
    std::cerr << "Moving image gradient source: results for Value don't match: " << valueReturn1 << ", " << valueReturn2
              << std::endl;
  }

  /* Test expected exceptions when transform is not right type */
  metric->SetMovingTransform(translationTransform);
  EXPECT_THROW(metric->Initialize(), itk::ExceptionObject);

  /* Exercise accessor method */
  constexpr auto testValue = static_cast<MetricType::InternalComputationValueType>(0.5);
  metric->SetIntensityDifferenceThreshold(testValue);
  EXPECT_EQ(metric->GetIntensityDifferenceThreshold(), testValue) << "Set/GetIntensityDifferenceThreshold failed.";

  /* Print self */
  metric->Print(std::cout);
}
