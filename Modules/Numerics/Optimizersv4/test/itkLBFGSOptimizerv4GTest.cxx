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

#include "itkLBFGSOptimizerv4.h"
#include "itkMath.h"
#include "vnl/algo/vnl_lbfgs.h"
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
class itkLBFGSOptimizerv4TestMetric : public itk::ObjectToObjectMetricBase
{
public:
  using Self = itkLBFGSOptimizerv4TestMetric;
  using Superclass = itk::ObjectToObjectMetricBase;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;
  itkNewMacro(Self);

  itkOverrideGetNameOfClassMacro(itkLBFGSOptimizerv4TestMetric);

  enum
  {
    SpaceDimension = 2
  };

  using ParametersType = Superclass::ParametersType;
  using DerivativeType = Superclass::DerivativeType;
  using MeasureType = Superclass::MeasureType;

  itkLBFGSOptimizerv4TestMetric() = default;

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


TEST(LBFGSOptimizerv4, ConvertedLegacyTest)
{
  std::cout << "LBFGS Optimizerv4 Test \n \n";

  using OptimizerType = itk::LBFGSOptimizerv4;
  using vnlOptimizerType = vnl_lbfgs;

  // Declaration of an itkOptimizer
  auto itkOptimizer = OptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(itkOptimizer, LBFGSOptimizerv4, LBFGSOptimizerBasev4);


  // Declaration of the metric
  auto metric = itkLBFGSOptimizerv4TestMetric::New();

  // Set some optimizer parameters
  constexpr bool trace{ false };
  itkOptimizer->SetTrace(trace);
  EXPECT_EQ(trace, itkOptimizer->GetTrace());

  unsigned int maximumNumberOfFunctionEvaluations = 1000;
  itkOptimizer->SetMaximumNumberOfFunctionEvaluations(maximumNumberOfFunctionEvaluations);
  EXPECT_EQ(maximumNumberOfFunctionEvaluations, itkOptimizer->GetMaximumNumberOfFunctionEvaluations());

  double gradientConvergenceTolerance = 1e-3;
  itkOptimizer->SetGradientConvergenceTolerance(gradientConvergenceTolerance);
  EXPECT_EQ(gradientConvergenceTolerance, itkOptimizer->GetGradientConvergenceTolerance());

  double lineSearchAccuracy = 0.1;
  itkOptimizer->SetLineSearchAccuracy(lineSearchAccuracy);
  EXPECT_EQ(lineSearchAccuracy, itkOptimizer->GetLineSearchAccuracy());

  double defaultStepLength = 5.0;
  itkOptimizer->SetDefaultStepLength(defaultStepLength);
  EXPECT_EQ(defaultStepLength, itkOptimizer->GetDefaultStepLength());

  const OptimizerType::DerivativeType cachedDerivative{};
  EXPECT_EQ(cachedDerivative, itkOptimizer->GetCachedDerivative());

  const OptimizerType::ParametersType cachedCurrentPos{};
  EXPECT_EQ(cachedCurrentPos, itkOptimizer->GetCachedCurrentPosition());

  std::cout << "GetValue() before optimizer starts: " << itkOptimizer->GetValue() << std::endl;
  std::cout << "SetMetric." << std::endl;
  itkOptimizer->SetMetric(metric);

  std::cout << "Get vnl optimizer." << std::endl;
  vnlOptimizerType * vnlOptimizer = itkOptimizer->GetOptimizer();

  vnlOptimizer->set_check_derivatives(0);

  constexpr unsigned int        SpaceDimension{ 2 };
  OptimizerType::ParametersType initialValue(SpaceDimension);

  // We start not so far from  | 2 -2 |
  initialValue[0] = 100;
  initialValue[1] = -100;

  // Set the initial position by setting the metric
  // parameters.
  std::cout << "Set metric parameters." << std::endl;
  metric->SetParameters(initialValue);

  // Set some optimizer parameters
  maximumNumberOfFunctionEvaluations = 100;
  itkOptimizer->SetMaximumNumberOfFunctionEvaluations(maximumNumberOfFunctionEvaluations);
  EXPECT_EQ(maximumNumberOfFunctionEvaluations, itkOptimizer->GetMaximumNumberOfFunctionEvaluations());

  gradientConvergenceTolerance = 1e-4;
  itkOptimizer->SetGradientConvergenceTolerance(gradientConvergenceTolerance);
  EXPECT_EQ(gradientConvergenceTolerance, itkOptimizer->GetGradientConvergenceTolerance());

  lineSearchAccuracy = 0.9;
  itkOptimizer->SetLineSearchAccuracy(lineSearchAccuracy);
  EXPECT_EQ(lineSearchAccuracy, itkOptimizer->GetLineSearchAccuracy());

  defaultStepLength = 1.0;
  itkOptimizer->SetDefaultStepLength(defaultStepLength);
  EXPECT_EQ(defaultStepLength, itkOptimizer->GetDefaultStepLength());

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

  std::cout << "Stop description   = " << itkOptimizer->GetStopConditionDescription() << std::endl;

  std::cout << "End condition   = " << vnlOptimizer->get_failure_code() << std::endl;
  std::cout << "Number of iters = " << vnlOptimizer->get_num_iterations() << std::endl;
  std::cout << "Number of evals = " << vnlOptimizer->get_num_evaluations() << std::endl;
  std::cout << std::endl;

  OptimizerType::ParametersType finalPosition = itkOptimizer->GetCurrentPosition();

  std::cout << "Solution        = (" << finalPosition[0] << ',' << finalPosition[1] << ')' << std::endl;

  std::cout << "End condition   = " << itkOptimizer->GetStopConditionDescription() << std::endl;
  std::cout << "NumberOfIterations  = " << itkOptimizer->GetCurrentIteration() << std::endl;

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
  const auto numberOfIterations = itkOptimizer->GetNumberOfIterations();
  itkOptimizer->SetNumberOfIterations(5);
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

  EXPECT_EQ(itkOptimizer->GetCurrentIteration(), 5u);


  // Test with non-identity scales
  //
  itkOptimizer->SetNumberOfIterations(numberOfIterations);
  std::cout << std::endl << "Test with non-identiy scales." << std::endl;
  OptimizerType::ScalesType scales(2);
  scales[0] = 1.5;
  scales[1] = 0.75;
  itkOptimizer->SetScales(scales);

  std::cout << "Set metric parameters." << std::endl;
  metric->SetParameters(initialValue);

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

  std::cout << "Scales after optimization: " << itkOptimizer->GetScales() << std::endl;
  finalPosition = itkOptimizer->GetCurrentPosition();
  std::cout << "Solution        = (" << finalPosition[0] << ',' << finalPosition[1] << ')' << std::endl;

  // check results to see if it is within range
  for (unsigned int j = 0; j < 2; ++j)
  {
    EXPECT_NEAR(finalPosition[j], trueParameters[j], tolerance);
  }

  // Test with local-support transform. Should FAIL.
  // Such transforms are not yet supported.
  metric->SetHasLocalSupport(true);
  EXPECT_THROW(itkOptimizer->StartOptimization(), itk::ExceptionObject);
}
