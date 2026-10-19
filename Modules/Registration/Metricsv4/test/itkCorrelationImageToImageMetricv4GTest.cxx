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
#include "itkCorrelationImageToImageMetricv4.h"
#include "itkTranslationTransform.h"
#include "itkMath.h"
#include "itkGTest.h"

/* Simple test to verify that class builds and runs.
 * Results are not verified. See ImageToImageMetricv4Test
 * for verification of basic metric functionality.
 *
 * TODO Numerical verification.
 */
namespace
{
template <typename TIndexType, typename TPointType>
double
itkCorrelationImageToImageMetricv4Test_GetToyImagePixelValue(TIndexType         index,
                                                             TPointType         offset,
                                                             const unsigned int Dim,
                                                             double             c)
{
  double v = 0.0;
  for (unsigned int i = 0; i < Dim; ++i)
  {
    v += (index[i] + offset[i]) * (index[i] + offset[i]);
  }

  v = std::exp(-1.0 * v / 8);
  v += c;

  return v;
}

template <typename TMetricPointer, typename TValue, typename TDerivativeType>
void
itkCorrelationImageToImageMetricv4Test_WithSpecifiedThreads(TMetricPointer &  metric,
                                                            TValue &          value,
                                                            TDerivativeType & derivative)
{
  using MetricType = typename TMetricPointer::ObjectType;

  /* Initialize. */
  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize()) << "Caught unexpected exception during Initialize";

  // Evaluate with GetValueAndDerivative
  typename MetricType::MeasureType    valueReturn1{};
  typename MetricType::DerivativeType derivativeReturn;
  std::cout << "Calling GetValueAndDerivative..." << std::endl;
  ASSERT_NO_THROW(metric->GetValueAndDerivative(valueReturn1, derivativeReturn))
    << "Caught unexpected exception during GetValueAndDerivative";


  std::cout << "value:" << valueReturn1 << std::endl;
  std::cout << "derivativeReturn:" << derivativeReturn << std::endl;

  /* Re-initialize. */
  std::cout << "Calling Initialize..." << std::endl;
  ASSERT_NO_THROW(metric->Initialize()) << "Caught unexpected exception during re-initialize";

  typename MetricType::MeasureType valueReturn2{};
  std::cout << "Calling GetValue..." << std::endl;
  ASSERT_NO_THROW(valueReturn2 = metric->GetValue()) << "Caught unexpected exception during GetValue";

  // Test same value returned by different methods
  std::cout << "Check Value return values..." << std::endl;
  if (itk::Math::NotExactlyEquals(valueReturn1, valueReturn2))
  {
    std::cerr << "Results for Value don't match: " << valueReturn1 << ", " << valueReturn2 << std::endl;
  }

  value = valueReturn1;
  derivative = derivativeReturn;
}
} // namespace

TEST(CorrelationImageToImageMetricv4, ConvertedLegacyTest)
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

  /* Fill images */
  itk::ImageRegionIterator<ImageType> itFixed(fixedImage, region);
  using IndexType = ImageType::IndexType;

  using PointType = ImageType::PointType;
  PointType p0;
  for (unsigned int i = 0; i < imageDimensionality; ++i)
  {
    p0[i] = 0;
  }

  itFixed.GoToBegin();
  while (!itFixed.IsAtEnd())
  {
    const IndexType ind = itFixed.ComputeIndex();
    const double    v = itkCorrelationImageToImageMetricv4Test_GetToyImagePixelValue(ind, p0, imageDimensionality, 0);
    itFixed.Set(v);
    ++itFixed;
  }

  itk::ImageRegionIteratorWithIndex<ImageType> itMoving(movingImage, region);

  itMoving.GoToBegin();

  PointType p1;
  p1[0] = 1;
  p1[1] = 0.5;
  p1[2] = 0.25;

  while (!itMoving.IsAtEnd())
  {
    const IndexType ind = itMoving.GetIndex();
    const double    v = itkCorrelationImageToImageMetricv4Test_GetToyImagePixelValue(ind, p1, imageDimensionality, 0);
    itMoving.Set(v);
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
  using MetricType = itk::CorrelationImageToImageMetricv4<ImageType, ImageType, ImageType>;

  auto metric = MetricType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(metric, CorrelationImageToImageMetricv4, ImageToImageMetricv4);

  /* Assign images and transforms.
   * By not setting a virtual domain image or virtual domain settings,
   * the metric will use the fixed image for the virtual domain. */
  metric->SetFixedImage(fixedImage);
  metric->SetMovingImage(movingImage);
  metric->SetFixedTransform(fixedTransform);
  metric->SetMovingTransform(movingTransform);

  metric->SetMaximumNumberOfWorkUnits(1);
  std::cerr << "Setting number of metric threads to " << metric->GetMaximumNumberOfWorkUnits() << std::endl;
  MetricType::MeasureType    value1 = NAN;
  MetricType::DerivativeType derivative1;

  itkCorrelationImageToImageMetricv4Test_WithSpecifiedThreads(metric, value1, derivative1);
  MetricType::MeasureType    value2 = NAN;
  MetricType::DerivativeType derivative2;
  metric->SetMaximumNumberOfWorkUnits(8);
  std::cerr << "Setting number of metric threads to " << metric->GetMaximumNumberOfWorkUnits() << std::endl;
  itkCorrelationImageToImageMetricv4Test_WithSpecifiedThreads(metric, value2, derivative2);

  constexpr double myeps{ 1e-8 };
  EXPECT_LE(itk::Math::Absolute(value1 - value2), 1e-8)
    << "Got different metric values when set threading number differently.";

  const vnl_vector<double> ddiff = vnl_vector<double>(derivative1) - vnl_vector<double>(derivative2);
  EXPECT_LE(ddiff.two_norm(), myeps) << "derivative1: " << derivative1 << std::endl
                                     << "derivative2: " << derivative2 << std::endl
                                     << "Got different derivative values when set threading number differently.";

  // Test that non-overlapping images will generate a warning
  // and return max value for metric value.
  MovingTransformType::ParametersType parameters(imageDimensionality,
                                                 static_cast<MovingTransformType::ParametersValueType>(1000));
  movingTransform->SetParameters(parameters);
  constexpr MetricType::MeasureType expectedMetricMax{ itk::NumericTraits<MetricType::MeasureType>::max() };
  std::cout << "Testing non-overlapping images. Expect a warning:" << std::endl;
  MetricType::MeasureType    valueReturn = NAN;
  MetricType::DerivativeType derivativeReturn;
  metric->GetValueAndDerivative(valueReturn, derivativeReturn);
  if (metric->GetNumberOfValidPoints() != 0 || itk::Math::NotExactlyEquals(valueReturn, expectedMetricMax))
  {
    std::cerr << "Failed testing for non-overlapping images. " << std::endl
              << "  Number of valid points: " << metric->GetNumberOfValidPoints() << std::endl
              << "  Metric value: " << valueReturn << std::endl
              << "  Expected metric max value: " << expectedMetricMax << std::endl;
  }
}
