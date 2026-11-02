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

#include <set>
#include "itkLBFGS2Optimizerv4.h"
#include "itkMath.h"
#include "itkGTest.h"
#include <iostream>

/**
 * \class itkLBFGSOptimizerv4TestMetric
 *
 *  The objectif function is the quadratic form:
 *
 *  1/2 x^T A x - b^T x
 *
 *  Where A is represented as an itkMatrix and
 *  b is represented as an itkVector
 *
 *  The system in this example is:
 *
 *     | 3  2 ||x|   | 2|   |0|
 *     | 2  6 ||y| + |-8| = |0|
 *
 *
 *   the solution is the vector | 2 -2 |
 *
 */
namespace
{
class itkLBFGS2Optimizerv4TestMetric : public itk::ObjectToObjectMetricBase
{
public:
  using Self = itkLBFGS2Optimizerv4TestMetric;
  using Superclass = itk::ObjectToObjectMetricBase;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;
  itkNewMacro(Self);

  itkOverrideGetNameOfClassMacro(itkLBFGS2Optimizerv4TestMetric);

  enum
  {
    SpaceDimension = 2
  };

  using ParametersType = Superclass::ParametersType;
  using DerivativeType = Superclass::DerivativeType;
  using MeasureType = Superclass::MeasureType;

  itkLBFGS2Optimizerv4TestMetric() = default;

  MeasureType
  GetValue() const override
  {
    const double x = this->m_Parameters[0];
    const double y = this->m_Parameters[1];

    std::cout << "GetValue ( " << x << " , " << y << ") = ";

    const double val = 0.5 * (3 * x * x + 4 * x * y + 6 * y * y) - 2 * x + 8 * y;

    std::cout << val << std::endl;

    return val;
  }

  void
  GetDerivative(DerivativeType & derivative) const override
  {
    const double x = this->m_Parameters[0];
    const double y = this->m_Parameters[1];

    std::cout << "GetDerivative ( " << x << " , " << y << ") = ";

    derivative = DerivativeType(SpaceDimension);
    derivative[0] = -(3 * x + 2 * y - 2);
    derivative[1] = -(2 * x + 6 * y + 8);

    std::cout << '(' << derivative[0] << " , " << derivative[1] << ')' << std::endl;
  }

  void
  GetValueAndDerivative(MeasureType & value, DerivativeType & derivative) const override
  {
    value = GetValue();
    GetDerivative(derivative);
  }

  void
  Initialize() override
  {
    m_Parameters.SetSize(SpaceDimension);
  }

  Superclass::NumberOfParametersType
  GetNumberOfLocalParameters() const override
  {
    return SpaceDimension;
  }

  Superclass::NumberOfParametersType
  GetNumberOfParameters() const override
  {
    return SpaceDimension;
  }

  void
  SetParameters(ParametersType & params) override
  {
    this->m_Parameters = params;
  }

  const ParametersType &
  GetParameters() const override
  {
    return this->m_Parameters;
  }

  bool
  HasLocalSupport() const override
  {
    return m_HasLocalSupport;
  }

  void
  SetHasLocalSupport(bool hls)
  {
    m_HasLocalSupport = hls;
  }

  void
  UpdateTransformParameters(const DerivativeType &, ParametersValueType) override
  {}

private:
  ParametersType m_Parameters;
  bool           m_HasLocalSupport{ false };
};
} // namespace


TEST(LBFGS2Optimizerv4, ConvertedLegacyTest)
{
  std::cout << "LBFGS2 Optimizerv4 Test \n \n";

  using OptimizerType = itk::LBFGS2Optimizerv4;

  // Declaration of an itkOptimizer
  auto itkOptimizer = OptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(itkOptimizer, LBFGS2Optimizerv4Template, GradientDescentOptimizerv4Template);


  // Declaration of the metric
  auto metric = itkLBFGS2Optimizerv4TestMetric::New();

  // Set some optimizer parameters
  auto hessianApproximationAccuracy = 5;
  itkOptimizer->SetHessianApproximationAccuracy(hessianApproximationAccuracy);
  EXPECT_EQ(hessianApproximationAccuracy, itkOptimizer->GetHessianApproximationAccuracy());

  constexpr typename OptimizerType::PrecisionType solutionAccuracy = 1e-5;
  itkOptimizer->SetSolutionAccuracy(solutionAccuracy);
  EXPECT_EQ(solutionAccuracy, itkOptimizer->GetSolutionAccuracy());

  auto deltaConvergenceDistance = 0;
  itkOptimizer->SetDeltaConvergenceDistance(deltaConvergenceDistance);
  EXPECT_EQ(deltaConvergenceDistance, itkOptimizer->GetDeltaConvergenceDistance());

  constexpr typename OptimizerType::PrecisionType deltaConvergenceTolerance = 0;
  itkOptimizer->SetDeltaConvergenceTolerance(deltaConvergenceTolerance);
  EXPECT_EQ(deltaConvergenceTolerance, itkOptimizer->GetDeltaConvergenceTolerance());

  auto maximumIterations = 0;
  itkOptimizer->SetMaximumIterations(maximumIterations);
  EXPECT_EQ(maximumIterations, itkOptimizer->GetMaximumIterations());

  auto numberOfIterations = static_cast<itk::SizeValueType>(maximumIterations);
  EXPECT_EQ(numberOfIterations, itkOptimizer->GetNumberOfIterations());

  itkOptimizer->SetNumberOfIterations(maximumIterations);
  EXPECT_EQ(numberOfIterations, itkOptimizer->GetNumberOfIterations());

  constexpr typename OptimizerType::LineSearchMethodEnum lineSearchMethod =
    OptimizerType::LineSearchMethodEnum::LINESEARCH_DEFAULT;
  itkOptimizer->SetLineSearch(lineSearchMethod);
  EXPECT_EQ(lineSearchMethod, itkOptimizer->GetLineSearch());

  auto maximumLineSearchEvaluations = 20;
  itkOptimizer->SetMaximumLineSearchEvaluations(maximumLineSearchEvaluations);
  EXPECT_EQ(maximumLineSearchEvaluations, itkOptimizer->GetMaximumLineSearchEvaluations());

  constexpr typename OptimizerType::PrecisionType minimumLineSearchStep = 1e-20;
  itkOptimizer->SetMinimumLineSearchStep(minimumLineSearchStep);
  EXPECT_EQ(minimumLineSearchStep, itkOptimizer->GetMinimumLineSearchStep());

  constexpr typename OptimizerType::PrecisionType maximumLineSearchStep = 1e+20;
  itkOptimizer->SetMaximumLineSearchStep(maximumLineSearchStep);
  EXPECT_EQ(maximumLineSearchStep, itkOptimizer->GetMaximumLineSearchStep());

  constexpr typename OptimizerType::PrecisionType lineSearchAccuracy = 1e-4;
  itkOptimizer->SetLineSearchAccuracy(lineSearchAccuracy);
  EXPECT_EQ(lineSearchAccuracy, itkOptimizer->GetLineSearchAccuracy());

  constexpr typename OptimizerType::PrecisionType wolfeCoefficient = 0;
  itkOptimizer->SetWolfeCoefficient(wolfeCoefficient);
  EXPECT_EQ(wolfeCoefficient, itkOptimizer->GetWolfeCoefficient());

  constexpr typename OptimizerType::PrecisionType lineSearchGradientAccuracy = 0.9;
  itkOptimizer->SetLineSearchGradientAccuracy(lineSearchGradientAccuracy);
  EXPECT_EQ(lineSearchGradientAccuracy, itkOptimizer->GetLineSearchGradientAccuracy());

  // itkOptimizer->SetMachinePrecisionTolerance():

  constexpr typename OptimizerType::PrecisionType orthantwiseCoefficient = 0;
  itkOptimizer->SetOrthantwiseCoefficient(orthantwiseCoefficient);
  EXPECT_EQ(orthantwiseCoefficient, itkOptimizer->GetOrthantwiseCoefficient());

  auto orthantwiseStart = 0;
  itkOptimizer->SetOrthantwiseStart(orthantwiseStart);
  EXPECT_EQ(orthantwiseStart, itkOptimizer->GetOrthantwiseStart());

  auto orthantwiseEnd = 1;
  itkOptimizer->SetOrthantwiseEnd(orthantwiseEnd);
  EXPECT_EQ(orthantwiseEnd, itkOptimizer->GetOrthantwiseEnd());

  auto estimateScalesAtEachIteration = true;
  ITK_GTEST_SET_GET_BOOLEAN(itkOptimizer, EstimateScalesAtEachIteration, estimateScalesAtEachIteration);

  std::cout << "GetValue() before optimizer starts: ";
  std::cout << itkOptimizer->GetValue() << std::endl;
  std::cout << "SetMetric." << std::endl;
  itkOptimizer->SetMetric(metric);


  constexpr unsigned int        SpaceDimension{ 2 };
  OptimizerType::ParametersType initialValue(SpaceDimension);

  // We start not so far from  | 2 -2 |
  initialValue[0] = 100;
  initialValue[1] = -100;

  // Set the initial position by setting the metric
  // parameters.
  std::cout << "Set metric parameters." << std::endl;
  metric->SetParameters(initialValue);

  std::cout << "Stop description   = " << itkOptimizer->GetStopConditionDescription() << std::endl;

  std::cout << "Start optimization." << std::endl;
  try
  {
    itkOptimizer->StartOptimization();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Exception thrown ! " << std::endl;
    std::cerr << "An error occurred during Optimization" << std::endl;
    std::cerr << "Location    = " << e.GetLocation() << std::endl;
    std::cerr << "Description = " << e.GetDescription() << std::endl;
    FAIL();
  }


  OptimizerType::ParametersType finalPosition = itkOptimizer->GetCurrentPosition();

  std::cout << "Solution        = (" << finalPosition[0] << ',' << finalPosition[1] << ')' << std::endl;

  std::cout << "End condition   = " << itkOptimizer->GetStopConditionDescription() << std::endl;
  std::cout << "NumberOfIterations  = " << itkOptimizer->GetCurrentIteration() << std::endl;

  std::cout << "CurrentParameterNorm: " << itkOptimizer->GetCurrentParameterNorm() << std::endl;
  std::cout << "CurrentGradientNorm: " << itkOptimizer->GetCurrentGradientNorm() << std::endl;
  std::cout << "CurrentStepSize: " << itkOptimizer->GetCurrentStepSize() << std::endl;
  std::cout << "CurrentNumberOfEvaluations: " << itkOptimizer->GetCurrentNumberOfEvaluations() << std::endl;

  //
  // check results to see if it is within range
  //
  constexpr double trueParameters[2]{ 2, -2 };
  constexpr double tolerance{ 1e-2 };
  for (unsigned int j = 0; j < 2; ++j)
  {
    EXPECT_NEAR(finalPosition[j], trueParameters[j], tolerance);
  }

  // Get the final value of the optimizer
  std::cout << "Testing GetValue() : ";
  const OptimizerType::MeasureType finalValue = itkOptimizer->GetValue();
  EXPECT_NEAR(finalValue, -10.0, 0.01);


  //
  // Test stopping when number of iterations reached
  //
  maximumIterations = 5;
  itkOptimizer->SetMaximumIterations(maximumIterations);
  metric->SetParameters(initialValue);

  try
  {
    itkOptimizer->StartOptimization();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Exception thrown ! " << std::endl;
    std::cerr << "An error occurred during Optimization" << std::endl;
    std::cerr << e << std::endl;
    FAIL();
  }

  std::cout << "Solution        = (" << finalPosition[0] << ',' << finalPosition[1] << ')' << std::endl;
  std::cout << "NumberOfIterations  = " << itkOptimizer->GetCurrentIteration() << std::endl;

  EXPECT_EQ(itkOptimizer->GetCurrentIteration(), 2u);

  // Test streaming enumeration for LBFGS2Optimizerv4Enums::LineSearchMethod elements
  const std::set<itk::LBFGS2Optimizerv4Enums::LineSearchMethod> allLineSearchMethod{
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_DEFAULT,
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_MORETHUENTE,
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_BACKTRACKING_ARMIJO,
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_BACKTRACKING,
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_BACKTRACKING_WOLFE,
    itk::LBFGS2Optimizerv4Enums::LineSearchMethod::LINESEARCH_BACKTRACKING_STRONG_WOLFE
  };
  for (const auto & ee : allLineSearchMethod)
  {
    std::cout << "STREAMED ENUM VALUE LBFGS2Optimizerv4Enums::LineSearchMethod: " << ee << std::endl;
  }
}
