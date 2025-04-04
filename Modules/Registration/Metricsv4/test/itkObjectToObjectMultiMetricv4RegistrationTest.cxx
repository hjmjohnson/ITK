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
#include "itkLinearInterpolateImageFunction.h"
#include "itkImage.h"
#include "itkGaussianImageSource.h"
#include "itkCyclicShiftImageFilter.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"
#include "itkGradientDescentOptimizerv4.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkObjectToObjectMultiMetricv4.h"
#include "itkMeanSquaresImageToImageMetricv4.h"

/* This test performs a simple registration test using
 * a single metric and a multivariate metric containing
 * two copies of the metric, testing
 * that the results are the same.
 */

template <typename TFilter>
class itkObjectToObjectMultiMetricv4RegistrationTestCommandIterationUpdate : public itk::Command
{
public:
  using Self = itkObjectToObjectMultiMetricv4RegistrationTestCommandIterationUpdate;

  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

protected:
  itkObjectToObjectMultiMetricv4RegistrationTestCommandIterationUpdate() = default;

public:
  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * object, const itk::EventObject & event) override
  {
    if (typeid(event) != typeid(itk::IterationEvent))
    {
      return;
    }
    const auto * optimizer = dynamic_cast<const TFilter *>(object);

    if (!optimizer)
    {
      itkGenericExceptionMacro("Error dynamic_cast failed");
    }
    std::cout << "It- " << optimizer->GetCurrentIteration() << " gradient: " << optimizer->GetGradient()
              << " metric value: " << optimizer->GetCurrentMetricValue()
              << " Params: " << const_cast<TFilter *>(optimizer)->GetCurrentPosition() << std::endl;
  }
};

template <typename TImage>
void
ObjectToObjectMultiMetricv4RegistrationTestCreateImages(typename TImage::Pointer &    fixedImage,
                                                        typename TImage::Pointer &    movingImage,
                                                        typename TImage::OffsetType & imageShift)
{
  using PixelType = typename TImage::PixelType;
  using CoordinateRepresentationType = PixelType;

  // Create two simple images
  constexpr itk::SizeValueType   ImageSize = 100;
  constexpr itk::OffsetValueType boundary = 6;

  // Declare Gaussian Sources
  using GaussianImageSourceType = itk::GaussianImageSource<TImage>;

  auto size = TImage::SizeType::Filled(ImageSize);

  auto spacing =
    itk::MakeFilled<typename TImage::SpacingType>(itk::NumericTraits<CoordinateRepresentationType>::OneValue());

  const typename TImage::PointType origin{};

  auto fixedImageSource = GaussianImageSourceType::New();

  fixedImageSource->SetSize(size);
  fixedImageSource->SetOrigin(origin);
  fixedImageSource->SetSpacing(spacing);
  fixedImageSource->SetNormalized(false);
  fixedImageSource->SetScale(1.0f);
  fixedImageSource->Update();
  fixedImage = fixedImageSource->GetOutput();

  // zero-out the boundary
  itk::ImageRegionIteratorWithIndex<TImage> it(fixedImage, fixedImage->GetLargestPossibleRegion());
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
  {
    for (itk::SizeValueType n = 0; n < TImage::ImageDimension; ++n)
    {
      if (it.GetIndex()[n] < boundary || (static_cast<itk::OffsetValueType>(size[n]) - it.GetIndex()[n]) <= boundary)
      {
        it.Set(PixelType{});
        break;
      }
    }
  }

  // shift the fixed image to get the moving image
  using CyclicShiftFilterType = itk::CyclicShiftImageFilter<TImage, TImage>;
  auto                                                  shiftFilter = CyclicShiftFilterType::New();
  const typename CyclicShiftFilterType::OffsetValueType maxImageShift = boundary - 1;
  imageShift.Fill(maxImageShift);
  imageShift[0] = maxImageShift / 2;
  shiftFilter->SetInput(fixedImage);
  shiftFilter->SetShift(imageShift);
  shiftFilter->Update();
  movingImage = shiftFilter->GetOutput();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TMetric>
int
ObjectToObjectMultiMetricv4RegistrationTestRun(typename TMetric::Pointer &                    metric,
                                               int                                            numberOfIterations,
                                               typename TMetric::MeasureType &                valueResult,
                                               typename TMetric::DerivativeType &             derivativeResult,
                                               typename TMetric::InternalComputationValueType maxStep,
                                               bool                                           estimateStepOnce)
{
  // calculate initial metric value
  metric->Initialize();
  const typename TMetric::MeasureType initialValue = metric->GetValue();

  // scales estimator
  using RegistrationParameterScalesFromShiftType = itk::RegistrationParameterScalesFromPhysicalShift<TMetric>;
  const typename RegistrationParameterScalesFromShiftType::Pointer shiftScaleEstimator =
    RegistrationParameterScalesFromShiftType::New();
  shiftScaleEstimator->SetMetric(metric);

  //
  // optimizer
  //
  using OptimizerType = itk::GradientDescentOptimizerv4;
  auto optimizer = OptimizerType::New();

  optimizer->SetMetric(metric);
  optimizer->SetNumberOfIterations(numberOfIterations);
  optimizer->SetScalesEstimator(shiftScaleEstimator);
  optimizer->SetMaximumStepSizeInPhysicalUnits(maxStep);
  optimizer->SetDoEstimateLearningRateOnce(estimateStepOnce);
  optimizer->SetDoEstimateLearningRateAtEachIteration(!estimateStepOnce);

  using CommandType = itkObjectToObjectMultiMetricv4RegistrationTestCommandIterationUpdate<OptimizerType>;
  auto observer = CommandType::New();
  // optimizer->AddObserver( itk::IterationEvent(), observer );

  optimizer->StartOptimization();

  std::cout << "# of iterations: " << optimizer->GetNumberOfIterations() << std::endl;
  std::cout << "DoEstimateLearningRateOnce: " << optimizer->GetDoEstimateLearningRateOnce()
            << " GetDoEstimateLearningRateAtEachIteration: " << optimizer->GetDoEstimateLearningRateAtEachIteration()
            << std::endl;
  derivativeResult = optimizer->GetCurrentPosition();
  std::cout << "Transform final parameters: " << derivativeResult << " mag: " << derivativeResult.magnitude()
            << std::endl;

  // final metric value
  valueResult = metric->GetValue();
  std::cout << "metric value: initial: " << initialValue << ", final: " << valueResult << std::endl;

  // scales
  std::cout << "scales: " << optimizer->GetScales() << std::endl;
  std::cout << "optimizer learning rate at end: " << optimizer->GetLearningRate() << std::endl;

  return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////
int
itkObjectToObjectMultiMetricv4RegistrationTest(int argc, char * argv[])
{
  constexpr int Dimension = 2;
  using ImageType = itk::Image<double, Dimension>;

  int numberOfIterations = 30;
  if (argc > 1)
  {
    numberOfIterations = std::stoi(argv[1]);
  }

  // create an affine transform
  using TranslationTransformType = itk::TranslationTransform<double, Dimension>;
  auto translationTransform = TranslationTransformType::New();
  translationTransform->SetIdentity();

  // create images
  ImageType::Pointer    fixedImage = nullptr;
  ImageType::Pointer    movingImage = nullptr;
  ImageType::OffsetType imageShift{};
  ObjectToObjectMultiMetricv4RegistrationTestCreateImages<ImageType>(fixedImage, movingImage, imageShift);

  using CorrelationMetricType = itk::CorrelationImageToImageMetricv4<ImageType, ImageType>;
  auto correlationMetric = CorrelationMetricType::New();
  correlationMetric->SetFixedImage(fixedImage);
  correlationMetric->SetMovingImage(movingImage);
  correlationMetric->SetMovingTransform(translationTransform);
  correlationMetric->Initialize();

  translationTransform->SetIdentity();

  std::cout << std::endl << "*** Single image metric: " << std::endl;
  CorrelationMetricType::MeasureType    singleValueResult = 0.0;
  CorrelationMetricType::DerivativeType singleDerivativeResult{};
  ObjectToObjectMultiMetricv4RegistrationTestRun<CorrelationMetricType>(
    correlationMetric, numberOfIterations, singleValueResult, singleDerivativeResult, 1.0, true);

  std::cout << "*** multi-variate metric: " << std::endl;
  auto metric2 = CorrelationMetricType::New();
  metric2->SetFixedImage(fixedImage);
  metric2->SetMovingImage(movingImage);
  metric2->SetMovingTransform(translationTransform);

  using MultiMetricType = itk::ObjectToObjectMultiMetricv4<Dimension, Dimension>;
  auto multiMetric = MultiMetricType::New();
  multiMetric->AddMetric(correlationMetric);
  multiMetric->AddMetric(metric2);
  multiMetric->AddMetric(metric2);
  multiMetric->Initialize();

  translationTransform->SetIdentity();

  CorrelationMetricType::MeasureType    multiValueResult = 0.0;
  CorrelationMetricType::DerivativeType multiDerivativeResult{};
  ObjectToObjectMultiMetricv4RegistrationTestRun<MultiMetricType>(
    multiMetric, numberOfIterations, multiValueResult, multiDerivativeResult, 1.0, true);

  // Comparison between single-metric and multi-variate metric registrations
  auto tolerance = static_cast<CorrelationMetricType::DerivativeValueType>(1e-6);
  if (itk::Math::abs(multiDerivativeResult[0] - singleDerivativeResult[0]) > tolerance ||
      itk::Math::abs(multiDerivativeResult[1] - singleDerivativeResult[1]) > tolerance)
  {
    std::cerr << "multi-variate registration derivative: " << multiDerivativeResult
              << " are different from single-variate derivative: " << singleDerivativeResult << std::endl;
    return EXIT_FAILURE;
  }
  if (itk::Math::abs(multiValueResult - singleValueResult) > tolerance)
  {
    std::cerr << "multi-variate registration value: " << multiValueResult
              << " is different from single-variate value: " << singleValueResult << std::endl;
    return EXIT_FAILURE;
  }

  // compare results with truth
  tolerance = static_cast<CorrelationMetricType::DerivativeValueType>(0.05);
  if (itk::Math::abs(multiDerivativeResult[0] - imageShift[0]) / imageShift[0] > tolerance ||
      itk::Math::abs(multiDerivativeResult[1] - imageShift[1]) / imageShift[1] > tolerance)
  {
    std::cerr << "multi-variate registration results: " << multiDerivativeResult
              << " are not as expected: " << imageShift << std::endl;
    return EXIT_FAILURE;
  }


  //
  // Try with step estimation at every iteration
  // Comparison between single-metric and multi-variate metric registrations
  //
  std::cout << std::endl << "*** Single image metric 2: " << std::endl;
  translationTransform->SetIdentity();
  ObjectToObjectMultiMetricv4RegistrationTestRun<CorrelationMetricType>(
    correlationMetric, numberOfIterations, singleValueResult, singleDerivativeResult, 0.25, false);

  std::cout << std::endl << "*** Multi-variate image metric 2: " << std::endl;
  translationTransform->SetIdentity();
  ObjectToObjectMultiMetricv4RegistrationTestRun<MultiMetricType>(
    multiMetric, numberOfIterations, multiValueResult, multiDerivativeResult, 0.25, false);

  if (itk::Math::abs(multiDerivativeResult[0] - singleDerivativeResult[0]) > tolerance ||
      itk::Math::abs(multiDerivativeResult[1] - singleDerivativeResult[1]) > tolerance)
  {
    std::cerr << "multi-variate registration derivative: " << multiDerivativeResult
              << " are different from single-variate derivative: " << singleDerivativeResult << std::endl;
    return EXIT_FAILURE;
  }
  if (itk::Math::abs(multiValueResult - singleValueResult) > tolerance)
  {
    std::cerr << "multi-variate registration value: " << multiValueResult
              << " is different from single-variate value: " << singleValueResult << std::endl;
    return EXIT_FAILURE;
  }

  // compare results with truth
  tolerance = static_cast<CorrelationMetricType::DerivativeValueType>(0.05);
  if (itk::Math::abs(multiDerivativeResult[0] - imageShift[0]) / imageShift[0] > tolerance ||
      itk::Math::abs(multiDerivativeResult[1] - imageShift[1]) / imageShift[1] > tolerance)
  {
    std::cerr << "multi-variate registration results: " << multiDerivativeResult
              << " are not as expected: " << imageShift << std::endl;
    return EXIT_FAILURE;
  }

  //
  // Test with two different metric types
  //
  using MeanSquaresMetricType = itk::MeanSquaresImageToImageMetricv4<ImageType, ImageType>;
  auto meanSquaresMetric = MeanSquaresMetricType::New();
  meanSquaresMetric->SetFixedImage(fixedImage);
  meanSquaresMetric->SetMovingImage(movingImage);
  meanSquaresMetric->SetMovingTransform(translationTransform);

  auto multiMetric2 = MultiMetricType::New();
  multiMetric2->AddMetric(correlationMetric);
  multiMetric2->AddMetric(meanSquaresMetric);
  multiMetric2->Initialize();

  translationTransform->SetIdentity();
  std::cout << "*** Multi-metric with different metric types: " << std::endl;
  ObjectToObjectMultiMetricv4RegistrationTestRun<MultiMetricType>(
    multiMetric2, numberOfIterations, multiValueResult, multiDerivativeResult, 1.0, true);

  // compare results with truth
  tolerance = static_cast<MeanSquaresMetricType::DerivativeValueType>(0.05);
  if (itk::Math::abs(multiDerivativeResult[0] - imageShift[0]) / imageShift[0] > tolerance ||
      itk::Math::abs(multiDerivativeResult[1] - imageShift[1]) / imageShift[1] > tolerance)
  {
    std::cerr << "multi-variate registration results: " << multiDerivativeResult
              << " are not as expected: " << imageShift << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
