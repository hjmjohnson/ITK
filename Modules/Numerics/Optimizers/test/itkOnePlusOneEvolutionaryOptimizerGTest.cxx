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

#include "itkOnePlusOneEvolutionaryOptimizer.h"
#include "itkNormalVariateGenerator.h"
#include "itkCommand.h"
#include "itkMath.h"
#include "itkGTest.h"

namespace
{

/**
 * \class OnePlusOneCostFunction
 *
 *  The objectif function is the quadratic form:
 *
 *  1/2 x^T A x - b^T x
 *
 *  Where A is a matrix and b is a vector
 *  The system in this example is:
 *
 *     | 3  2 ||x|   | 2|   |0|
 *     | 2  6 ||y| + |-8| = |0|
 *
 *
 *   the solution is the vector | 2 -2 |
 *
 */
class OnePlusOneCostFunction : public itk::SingleValuedCostFunction
{
public:
  using Self = OnePlusOneCostFunction;
  using Superclass = itk::SingleValuedCostFunction;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;
  itkNewMacro(Self);
  itkOverrideGetNameOfClassMacro(OnePlusOneCostFunction);

  enum
  {
    SpaceDimension = 2
  };

  using ParametersType = Superclass::ParametersType;
  using MeasureType = Superclass::MeasureType;

  OnePlusOneCostFunction() = default;


  MeasureType
  GetValue(const ParametersType & parameters) const override
  {
    const double x = parameters[0];
    const double y = parameters[1];

    std::cout << "GetValue( ";
    std::cout << x << ' ';
    std::cout << y << ") = ";

    const MeasureType measure = 0.5 * (3 * x * x + 4 * x * y + 6 * y * y) - 2 * x + 8 * y;

    std::cout << measure << std::endl;

    return measure;
  }

  void
  GetDerivative(const ParametersType & itkNotUsed(parameters), DerivativeType & itkNotUsed(derivative)) const override
  {
    itkGenericExceptionMacro("OnePlusOneEvolutionaryOptimizer is not supposed to call GetDerivative()");
  }

  unsigned int
  GetNumberOfParameters() const override
  {
    return SpaceDimension;
  }
};

class OnePlusOneCommandIterationUpdate : public itk::Command
{
public:
  using Self = OnePlusOneCommandIterationUpdate;
  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

protected:
  OnePlusOneCommandIterationUpdate() = default;

public:
  using OptimizerType = itk::OnePlusOneEvolutionaryOptimizer;
  using OptimizerPointer = const OptimizerType *;

  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * object, const itk::EventObject & event) override
  {
    auto optimizer = static_cast<OptimizerPointer>(object);
    if (!itk::IterationEvent().CheckEvent(&event))
    {
      return;
    }
    const double currentValue = optimizer->GetValue();
    // Only print out when the Metric value changes
    if (itk::Math::Absolute(m_LastMetricValue - currentValue) > 1e-7)
    {
      std::cout << optimizer->GetCurrentIteration() << "   ";
      std::cout << currentValue << "   ";
      std::cout << optimizer->GetCurrentPosition() << std::endl;
      m_LastMetricValue = currentValue;
    }
  }

private:
  double m_LastMetricValue{ 0.0 };
};

} // namespace


TEST(OnePlusOneEvolutionaryOptimizer, ConvertedLegacyTest)
{
  using OptimizerType = itk::OnePlusOneEvolutionaryOptimizer;

  // Declaration of an itkOptimizer
  auto itkOptimizer = OptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(
    itkOptimizer, OnePlusOneEvolutionaryOptimizer, SingleValuedNonLinearOptimizer);


  EXPECT_FALSE(itkOptimizer->GetInitialized());

  const OnePlusOneCommandIterationUpdate::Pointer observer = OnePlusOneCommandIterationUpdate::New();
  itkOptimizer->AddObserver(itk::IterationEvent(), observer);

  // Declaration of the CostFunction
  const OnePlusOneCostFunction::Pointer costFunction = OnePlusOneCostFunction::New();


  itkOptimizer->SetCostFunction(costFunction);


  using ParametersType = OnePlusOneCostFunction::ParametersType;

  const unsigned int spaceDimension = costFunction->GetNumberOfParameters();

  // We start not so far from  | 2 -2 |
  ParametersType initialPosition(spaceDimension);

  initialPosition[0] = 100;
  initialPosition[1] = -100;

  auto maximize = false;
  itkOptimizer->MinimizeOn();
  EXPECT_EQ(!maximize, itkOptimizer->GetMinimize());
  ITK_GTEST_SET_GET_BOOLEAN(itkOptimizer, Maximize, maximize);

  constexpr unsigned int maximumIteration{ 8000 };
  itkOptimizer->SetMaximumIteration(8000);
  EXPECT_EQ(maximumIteration, itkOptimizer->GetMaximumIteration());

  auto growthFactor = 1.05;
  itkOptimizer->SetGrowthFactor(growthFactor);
  EXPECT_EQ(growthFactor, itkOptimizer->GetGrowthFactor());

  auto shrinkFactor = std::pow(growthFactor, -0.25);
  itkOptimizer->SetShrinkFactor(shrinkFactor);
  EXPECT_EQ(shrinkFactor, itkOptimizer->GetShrinkFactor());

  auto initialRadius = 1.01;
  itkOptimizer->SetInitialRadius(initialRadius);
  EXPECT_EQ(initialRadius, itkOptimizer->GetInitialRadius());

  auto epsilon = 0.1;
  itkOptimizer->SetEpsilon(epsilon);
  EXPECT_EQ(epsilon, itkOptimizer->GetEpsilon());

  auto catchGetValueException = false;
  itkOptimizer->SetCatchGetValueException(catchGetValueException);
  EXPECT_EQ(catchGetValueException, itkOptimizer->GetCatchGetValueException());

  auto metricWorstPossibleValue = 0;
  itkOptimizer->SetMetricWorstPossibleValue(metricWorstPossibleValue);
  EXPECT_EQ(metricWorstPossibleValue, itkOptimizer->GetMetricWorstPossibleValue());

  initialRadius = 10;
  itkOptimizer->Initialize(initialRadius);
  EXPECT_EQ(initialRadius, itkOptimizer->GetInitialRadius());
  EXPECT_EQ(growthFactor, itkOptimizer->GetGrowthFactor());
  EXPECT_EQ(shrinkFactor, itkOptimizer->GetShrinkFactor());

  EXPECT_TRUE(itkOptimizer->GetInitialized());

  using GeneratorType = itk::Statistics::NormalVariateGenerator;
  auto generator = GeneratorType::New();
  itkOptimizer->SetNormalVariateGenerator(generator);

  itkOptimizer->SetInitialPosition(initialPosition);

  EXPECT_NO_THROW(itkOptimizer->StartOptimization());


  ParametersType finalPosition = itkOptimizer->GetCurrentPosition();
  std::cout << "Solution        = (";
  std::cout << finalPosition[0] << ',';
  std::cout << finalPosition[1] << ')' << std::endl;

  //
  // check results to see if it is within range
  //
  constexpr double trueParameters[2]{ 2, -2 };
  for (unsigned int j = 0; j < 2; ++j)
  {
    EXPECT_NEAR(finalPosition[j], trueParameters[j], 0.01);
  }

  // Exercise various member functions.
  std::cout << "Maximize: " << itkOptimizer->GetMaximize() << std::endl;
  std::cout << "Epsilon: " << itkOptimizer->GetEpsilon() << std::endl;
  std::cout << "NumberOfIterations: " << itkOptimizer->GetMaximumIteration() << std::endl;

  itkOptimizer->Print(std::cout);
  std::cout << "Stop description   = " << itkOptimizer->GetStopConditionDescription() << std::endl;
}
