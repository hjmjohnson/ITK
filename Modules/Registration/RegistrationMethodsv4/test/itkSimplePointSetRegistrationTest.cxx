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

#include "itkImageRegistrationMethodv4.h"

#include "itkAffineTransform.h"
#include "itkEuclideanDistancePointSetToPointSetMetricv4.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"
#include "itkTestingMacros.h"

template <typename TFilter>
class CommandIterationUpdate : public itk::Command
{
public:
  using Self = CommandIterationUpdate;
  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

protected:
  CommandIterationUpdate() = default;

public:
  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * object, const itk::EventObject & event) override
  {
    if (object == nullptr)
    {
      itkExceptionMacro("Command update on null object");
    }
    std::cout << "Observing from class " << object->GetNameOfClass();
    if (!object->GetObjectName().empty())
    {
      std::cout << " \"" << object->GetObjectName() << '"';
    }
    std::cout << std::endl;
    const auto * filter = static_cast<const TFilter *>(object);

    if (typeid(event) != typeid(itk::MultiResolutionIterationEvent) || object == nullptr)
    {
      return;
    }

    const unsigned int                                         currentLevel = filter->GetCurrentLevel();
    typename TFilter::TransformParametersAdaptorsContainerType adaptors =
      filter->GetTransformParametersAdaptorsPerLevel();

    const itk::ObjectToObjectOptimizerBase * optimizerBase = filter->GetOptimizer();
    using GradientDescentOptimizerv4Type = itk::GradientDescentOptimizerv4;
    const typename GradientDescentOptimizerv4Type::ConstPointer optimizer =
      dynamic_cast<const GradientDescentOptimizerv4Type *>(optimizerBase);
    if (!optimizer)
    {
      itkGenericExceptionMacro("Error dynamic_cast failed");
    }
    typename GradientDescentOptimizerv4Type::DerivativeType gradient = optimizer->GetGradient();

    std::cout << "  CL Current level:           " << currentLevel << std::endl;
    if (adaptors[currentLevel])
    {
      std::cout << "   RFP Required fixed params: " << adaptors[currentLevel]->GetRequiredFixedParameters()
                << std::endl;
    }
    std::cout << "   LR Final learning rate:    " << optimizer->GetLearningRate() << std::endl;
    std::cout << "   FM Final metric value:     " << optimizer->GetCurrentMetricValue() << std::endl;
    std::cout << "   SC Optimizer scales:       " << optimizer->GetScales() << std::endl;
    std::cout << "   FG Final metric gradient (sample of values): ";
    if (gradient.GetSize() < 10)
    {
      std::cout << gradient;
    }
    else
    {
      for (itk::SizeValueType i = 0; i < gradient.GetSize(); i += (gradient.GetSize() / 16))
      {
        std::cout << gradient[i] << ' ';
      }
    }
    std::cout << std::endl;
  }
};

int
itkSimplePointSetRegistrationTest(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  constexpr unsigned int Dimension = 2;
  constexpr unsigned int numberOfIterations = 20;

  using PointSetType = itk::PointSet<unsigned int, Dimension>;

  using PointSetMetricType = itk::EuclideanDistancePointSetToPointSetMetricv4<PointSetType>;
  auto metric = PointSetMetricType::New();

  using PointSetType = PointSetMetricType::FixedPointSetType;
  using PointType = PointSetType::PointType;

  using PixelType = double;
  using FixedImageType = itk::Image<PixelType, Dimension>;
  using MovingImageType = itk::Image<PixelType, Dimension>;


  auto fixedPoints = PointSetType::New();

  auto movingPoints = PointSetType::New();

  // two circles with a small offset
  PointType offset;
  for (unsigned int d = 0; d < PointSetType::PointDimension; ++d)
  {
    offset[d] = 2.0;
  }
  unsigned long count = 0;
  for (float theta = 0; theta < 2.0 * itk::Math::pi; theta += 0.1)
  {
    auto label = static_cast<unsigned int>(1.5 + count / 100);

    PointType       fixedPoint;
    constexpr float radius = 100.0;
    fixedPoint[0] = radius * std::cos(theta);
    fixedPoint[1] = radius * std::sin(theta);
    if constexpr (PointSetType::PointDimension > 2)
    {
      fixedPoint[2] = radius * std::sin(theta);
    }
    fixedPoints->SetPoint(count, fixedPoint);
    fixedPoints->SetPointData(count, label);

    PointType movingPoint;
    movingPoint[0] = fixedPoint[0] + offset[0];
    movingPoint[1] = fixedPoint[1] + offset[1];
    if constexpr (PointSetType::PointDimension > 2)
    {
      movingPoint[2] = fixedPoint[2] + offset[2];
    }
    movingPoints->SetPoint(count, movingPoint);
    movingPoints->SetPointData(count, label);

    count++;
  }

  // virtual image domain is [-110,-110]  [110,110]

  FixedImageType::SizeType      fixedImageSize;
  FixedImageType::PointType     fixedImageOrigin;
  FixedImageType::DirectionType fixedImageDirection;
  FixedImageType::SpacingType   fixedImageSpacing;

  fixedImageSize.Fill(221);
  fixedImageOrigin.Fill(-110);
  fixedImageDirection.SetIdentity();
  fixedImageSpacing.Fill(1);

  auto fixedImage = FixedImageType::New();
  fixedImage->SetRegions(fixedImageSize);
  fixedImage->SetOrigin(fixedImageOrigin);
  fixedImage->SetDirection(fixedImageDirection);
  fixedImage->SetSpacing(fixedImageSpacing);
  fixedImage->Allocate();

  using AffineTransformType = itk::AffineTransform<double, PointSetType::PointDimension>;
  auto transform = AffineTransformType::New();
  transform->SetIdentity();

  metric->SetFixedPointSet(fixedPoints);
  metric->SetMovingPointSet(movingPoints);
  metric->SetVirtualDomainFromImage(fixedImage);
  metric->SetMovingTransform(transform);
  metric->Initialize();

  // scales estimator
  using RegistrationParameterScalesFromShiftType =
    itk::RegistrationParameterScalesFromPhysicalShift<PointSetMetricType>;
  const RegistrationParameterScalesFromShiftType::Pointer shiftScaleEstimator =
    RegistrationParameterScalesFromShiftType::New();
  shiftScaleEstimator->SetMetric(metric);
  shiftScaleEstimator->SetTransformForward(true);
  // needed with pointset metrics
  shiftScaleEstimator->SetVirtualDomainPointSet(metric->GetVirtualTransformedPointSet());

  // optimizer
  using OptimizerType = itk::GradientDescentOptimizerv4;
  auto optimizer = OptimizerType::New();
  optimizer->SetMetric(metric);
  optimizer->SetNumberOfIterations(numberOfIterations);
  optimizer->SetScalesEstimator(shiftScaleEstimator);
  optimizer->SetMaximumStepSizeInPhysicalUnits(0.1);
  optimizer->SetMinimumConvergenceValue(0.0);
  optimizer->SetConvergenceWindowSize(10);

  using AffineRegistrationType = itk::ImageRegistrationMethodv4<FixedImageType, MovingImageType>;
  auto affineSimple = AffineRegistrationType::New();
  affineSimple->SetObjectName("affineSimple");

  affineSimple->SetFixedPointSet(fixedPoints);
  ITK_TEST_SET_GET_VALUE(fixedPoints, affineSimple->GetFixedPointSet());

  affineSimple->SetMovingPointSet(movingPoints);
  ITK_TEST_SET_GET_VALUE(movingPoints, affineSimple->GetMovingPointSet());

  affineSimple->SetInitialTransform(transform);
  affineSimple->SetMetric(metric);
  affineSimple->SetOptimizer(optimizer);

  using AffineCommandType = CommandIterationUpdate<AffineRegistrationType>;
  auto affineObserver = AffineCommandType::New();
  affineSimple->AddObserver(itk::MultiResolutionIterationEvent(), affineObserver);

  ITK_TRY_EXPECT_NO_EXCEPTION(affineSimple->Update());


  // applying the resultant transform to moving points and verify result
  std::cout << "Fixed\tMoving\tMovingTransformed\tFixedTransformed\tDiff" << std::endl;
  bool                                                   passed = true;
  constexpr PointType::ValueType                         tolerance = 1e-2;
  const AffineTransformType::InverseTransformBasePointer affineInverseTransform =
    affineSimple->GetModifiableTransform()->GetInverseTransform();
  for (unsigned int n = 0; n < movingPoints->GetNumberOfPoints(); ++n)
  {
    // compare the points in virtual domain
    PointType       transformedMovingPoint = affineInverseTransform->TransformPoint(movingPoints->GetPoint(n));
    PointType       fixedPoint = fixedPoints->GetPoint(n);
    const PointType transformedFixedPoint =
      affineSimple->GetModifiableTransform()->TransformPoint(fixedPoints->GetPoint(n));
    PointType difference;
    difference[0] = transformedMovingPoint[0] - fixedPoint[0];
    difference[1] = transformedMovingPoint[1] - fixedPoint[1];
    std::cout << fixedPoints->GetPoint(n) << '\t' << movingPoints->GetPoint(n) << '\t' << transformedMovingPoint << '\t'
              << transformedFixedPoint << '\t' << difference << std::endl;
    if (itk::Math::abs(difference[0]) > tolerance || itk::Math::abs(difference[1]) > tolerance)
    {
      passed = false;
    }
  }
  if (!passed)
  {
    std::cerr << "Results do not match truth within tolerance." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
