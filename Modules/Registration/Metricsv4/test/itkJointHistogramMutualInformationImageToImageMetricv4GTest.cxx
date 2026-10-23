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

#include "itkMath.h"
#include "itkJointHistogramMutualInformationImageToImageMetricv4.h"
#include "itkTranslationTransform.h"
#include "itkGTest.h"

/* Checks value/derivative path consistency, agreement of the analytic
 * derivative with a central finite difference of the value, and the
 * non-overlap contract. See ImageToImageMetricv4Test for basic metric
 * functionality. */

TEST(JointHistogramMutualInformationImageToImageMetricv4, ConvertedLegacyTest)
{
  constexpr unsigned int imageSize{ 20 };
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

  /* Fill with a smooth blob plus gradients; moving is a monotone nonlinear
   * remap of fixed so the marginals differ and MI varies with alignment. */
  itk::ImageRegionIteratorWithIndex<ImageType> itFixed(fixedImage, region);
  itk::ImageRegionIterator<ImageType>          itMoving(movingImage, region);
  constexpr double                             center = (imageSize - 1) / 2.0;
  for (itFixed.GoToBegin(), itMoving.GoToBegin(); !itFixed.IsAtEnd(); ++itFixed, ++itMoving)
  {
    const ImageType::IndexType index = itFixed.GetIndex();
    double                     radius2 = 0.0;
    for (unsigned int dim = 0; dim < imageDimensionality; ++dim)
    {
      radius2 += ((index[dim] - center) / (imageSize / 3.0)) * ((index[dim] - center) / (imageSize / 3.0));
    }
    const double value = std::exp(-radius2) + 0.3 * index[0] / imageSize + 0.15 * index[1] / imageSize;
    itFixed.Set(value);
    itMoving.Set(value * value * value);
  }

  /* Transforms */
  using FixedTransformType = itk::TranslationTransform<double, imageDimensionality>;
  using MovingTransformType = itk::TranslationTransform<double, imageDimensionality>;
  auto fixedTransform = FixedTransformType::New();
  auto movingTransform = MovingTransformType::New();
  fixedTransform->SetIdentity();
  movingTransform->SetIdentity();

  /* The metric */
  using MetricType = itk::JointHistogramMutualInformationImageToImageMetricv4<ImageType, ImageType, ImageType>;
  auto metric = MetricType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(
    metric, JointHistogramMutualInformationImageToImageMetricv4, ImageToImageMetricv4);

  // Fewer than 7 bins degenerates the padded-PDF derivative stencils to zero.
  constexpr itk::SizeValueType numberOfHistogramBins{ 20 };
  metric->SetNumberOfHistogramBins(numberOfHistogramBins);
  EXPECT_EQ(numberOfHistogramBins, metric->GetNumberOfHistogramBins());

  constexpr double varianceForJointPDFSmoothing{ 1.5 };
  metric->SetVarianceForJointPDFSmoothing(varianceForJointPDFSmoothing);
  EXPECT_EQ(varianceForJointPDFSmoothing, metric->GetVarianceForJointPDFSmoothing());

  /* Assign images and transforms.
   * By not setting a virtual domain image or virtual domain settings,
   * the metric will use the fixed image for the virtual domain. */
  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedTransform(fixedTransform);
  metric->SetMovingTransform(movingTransform);

  EXPECT_NO_THROW(metric->Initialize());

  // Evaluate
  MetricType::MeasureType valueReturn1 = NAN;
  EXPECT_NO_THROW(valueReturn1 = metric->GetValue());

  MetricType::MeasureType    valueReturn2 = NAN;
  MetricType::DerivativeType derivativeReturn;
  EXPECT_NO_THROW(metric->GetValueAndDerivative(valueReturn2, derivativeReturn));

  EXPECT_EQ(valueReturn1, valueReturn2) << "Value return results are not identical";

  // Analytic derivative must point downhill and match a central finite difference.
  {
    constexpr double                    detune = 1.0;
    constexpr double                    h = 0.5;
    MovingTransformType::ParametersType offsetParameters(movingTransform->GetNumberOfParameters(), 0.0);
    offsetParameters[0] = detune;
    movingTransform->SetParameters(offsetParameters);
    MetricType::MeasureType    detunedValue = NAN;
    MetricType::DerivativeType detunedDerivative;
    metric->GetValueAndDerivative(detunedValue, detunedDerivative);
    offsetParameters[0] = detune + h;
    movingTransform->SetParameters(offsetParameters);
    const MetricType::MeasureType valuePlus = metric->GetValue();
    offsetParameters[0] = detune - h;
    movingTransform->SetParameters(offsetParameters);
    const MetricType::MeasureType valueMinus = metric->GetValue();
    movingTransform->SetIdentity();
    const double finiteDifference = (valuePlus - valueMinus) / (2.0 * h);
    const double analytic = detunedDerivative[0];
    // Band brackets the measured analytic/central-difference ratio (~1.08 at h=0.5)
    // tightly enough to trip on a lost 1/log2 or stray factor-of-2 scale regression.
    EXPECT_GE(itk::Math::Absolute(finiteDifference), 1e-10)
      << "Analytic derivative disagrees with finite difference of the value";
    EXPECT_LT(analytic * finiteDifference, 0.0) << "Analytic derivative disagrees with finite difference of the value";
    EXPECT_GE(itk::Math::Absolute(analytic), 0.7 * itk::Math::Absolute(finiteDifference))
      << "Analytic derivative disagrees with finite difference of the value";
    EXPECT_LE(itk::Math::Absolute(analytic), 1.4 * itk::Math::Absolute(finiteDifference))
      << "Analytic derivative disagrees with finite difference of the value";
  }

  std::cout << "JointPDF: " << metric->GetJointPDF() << std::endl;

  // Test that non-overlapping images will generate a warning
  // and return max value for metric value.
  MovingTransformType::ParametersType parameters(movingTransform->GetNumberOfParameters(),
                                                 static_cast<MovingTransformType::ParametersValueType>(1000));
  movingTransform->SetParameters(parameters);
  constexpr MetricType::MeasureType expectedMetricMax{ itk::NumericTraits<MetricType::MeasureType>::max() };
  std::cout << "Testing non-overlapping images. Expect a warning:" << std::endl;
  metric->GetValueAndDerivative(valueReturn2, derivativeReturn);
  EXPECT_EQ(metric->GetNumberOfValidPoints(), 0u) << "Failed testing for non-overlapping images.";
  EXPECT_DOUBLE_EQ(valueReturn2, expectedMetricMax) << "Failed testing for non-overlapping images.";
  movingTransform->SetIdentity();
}
