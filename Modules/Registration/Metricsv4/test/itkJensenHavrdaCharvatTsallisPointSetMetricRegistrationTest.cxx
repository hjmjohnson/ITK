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

#include "itkJensenHavrdaCharvatTsallisPointSetToPointSetMetricv4.h"
#include "itkGradientDescentOptimizerv4.h"
#include "itkTransform.h"
#include "itkAffineTransform.h"
#include "itkRegistrationParameterScalesFromPhysicalShift.h"
#include "itkCommand.h"

#include <fstream>

template <typename TFilter>
class itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTestCommandIterationUpdate : public itk::Command
{
public:
  using Self = itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTestCommandIterationUpdate;

  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

protected:
  itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTestCommandIterationUpdate() = default;

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
    std::cout << "It: " << optimizer->GetCurrentIteration() << " metric value: " << optimizer->GetCurrentMetricValue();
    std::cout << std::endl;
  }
};

int
itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTest(int argc, char * argv[])
{
  constexpr unsigned int Dimension = 2;

  unsigned int numberOfIterations = 10;
  if (argc > 1)
  {
    numberOfIterations = std::stoi(argv[1]);
  }

  using PointSetType = itk::PointSet<unsigned char, Dimension>;

  using PointType = PointSetType::PointType;

  auto fixedPoints = PointSetType::New();

  auto movingPoints = PointSetType::New();


  // two ellipses, one rotated slightly
  /*
    // Having trouble with these, as soon as there's a slight rotation added.
    unsigned long count = 0;
    for( float theta = 0; theta < 2.0 * itk::Math::pi; theta += 0.1 )
      {
      float radius = 100.0;
      PointType fixedPoint;
      fixedPoint[0] = 2 * radius * std::cos( theta );
      fixedPoint[1] = radius * std::sin( theta );
      fixedPoints->SetPoint( count, fixedPoint );

      PointType movingPoint;
      movingPoint[0] = 2 * radius * std::cos( theta + (0.02 * itk::Math::pi) ) + 2.0;
      movingPoint[1] = radius * std::sin( theta + (0.02 * itk::Math::pi) ) + 2.0;
      movingPoints->SetPoint( count, movingPoint );

      count++;
      }
  */

  // two circles with a small offset
  PointType offset;
  for (unsigned int d = 0; d < Dimension; ++d)
  {
    offset[d] = 2.0;
  }
  unsigned long count = 0;
  for (float theta = 0; theta < 2.0 * itk::Math::pi; theta += 0.1)
  {
    PointType       fixedPoint;
    constexpr float radius = 100.0;
    fixedPoint[0] = radius * std::cos(theta);
    fixedPoint[1] = radius * std::sin(theta);
    if constexpr (Dimension > 2)
    {
      fixedPoint[2] = radius * std::sin(theta);
    }
    fixedPoints->SetPoint(count, fixedPoint);

    PointType movingPoint;
    movingPoint[0] = fixedPoint[0] + offset[0];
    movingPoint[1] = fixedPoint[1] + offset[1];
    if constexpr (Dimension > 2)
    {
      movingPoint[2] = fixedPoint[2] + offset[2];
    }
    movingPoints->SetPoint(count, movingPoint);

    count++;
  }

  using AffineTransformType = itk::AffineTransform<double, Dimension>;
  auto transform = AffineTransformType::New();
  transform->SetIdentity();

  // Instantiate the metric
  using PointSetMetricType = itk::JensenHavrdaCharvatTsallisPointSetToPointSetMetricv4<PointSetType>;
  auto metric = PointSetMetricType::New();
  metric->SetFixedPointSet(fixedPoints);
  metric->SetMovingPointSet(movingPoints);
  metric->SetPointSetSigma(1.0);
  metric->SetKernelSigma(10.0);
  metric->SetUseAnisotropicCovariances(false);
  metric->SetCovarianceKNeighborhood(5);
  metric->SetEvaluationKNeighborhood(10);
  metric->SetMovingTransform(transform);
  metric->SetAlpha(1.1);
  metric->Initialize();

  // scales estimator
  using RegistrationParameterScalesFromShiftType =
    itk::RegistrationParameterScalesFromPhysicalShift<PointSetMetricType>;
  const RegistrationParameterScalesFromShiftType::Pointer shiftScaleEstimator =
    RegistrationParameterScalesFromShiftType::New();
  shiftScaleEstimator->SetMetric(metric);
  // needed with pointset metrics
  shiftScaleEstimator->SetVirtualDomainPointSet(metric->GetVirtualTransformedPointSet());

  // optimizer
  using OptimizerType = itk::GradientDescentOptimizerv4;
  auto optimizer = OptimizerType::New();
  optimizer->SetMetric(metric);
  optimizer->SetNumberOfIterations(numberOfIterations);
  optimizer->SetScalesEstimator(shiftScaleEstimator);
  optimizer->SetMaximumStepSizeInPhysicalUnits(3.0);

  using CommandType = itkJensenHavrdaCharvatTsallisPointSetMetricRegistrationTestCommandIterationUpdate<OptimizerType>;
  auto observer = CommandType::New();
  optimizer->AddObserver(itk::IterationEvent(), observer);

  optimizer->SetMinimumConvergenceValue(0.0);
  optimizer->SetConvergenceWindowSize(10);
  optimizer->StartOptimization();

  std::cout << "numberOfIterations: " << numberOfIterations << std::endl;
  std::cout << "Moving-source final value: " << optimizer->GetCurrentMetricValue() << std::endl;
  std::cout << "Moving-source final position: " << optimizer->GetCurrentPosition() << std::endl;
  std::cout << "Optimizer scales: " << optimizer->GetScales() << std::endl;
  std::cout << "Optimizer learning rate: " << optimizer->GetLearningRate() << std::endl;

  // applying the resultant transform to moving points and verify result
  std::cout << "Fixed\tMoving\tMovingTransformed\tFixedTransformed\tDiff" << std::endl;
  bool                                                   passed = true;
  constexpr PointType::ValueType                         tolerance = 1e-2;
  const AffineTransformType::InverseTransformBasePointer movingInverse =
    metric->GetMovingTransform()->GetInverseTransform();
  const AffineTransformType::InverseTransformBasePointer fixedInverse =
    metric->GetFixedTransform()->GetInverseTransform();
  for (unsigned int n = 0; n < metric->GetNumberOfComponents(); ++n)
  {
    // compare the points in virtual domain
    PointType transformedMovingPoint = movingInverse->TransformPoint(movingPoints->GetPoint(n));
    PointType transformedFixedPoint = fixedInverse->TransformPoint(fixedPoints->GetPoint(n));
    PointType difference;
    difference[0] = transformedMovingPoint[0] - transformedFixedPoint[0];
    difference[1] = transformedMovingPoint[1] - transformedFixedPoint[1];
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
