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

#include "itkAmoebaOptimizer.h"
#include "itkConjugateGradientOptimizer.h"
#include "itkCumulativeGaussianOptimizer.h"
#include "itkLBFGSOptimizer.h"
#include "itkVersorTransformOptimizer.h"
#include "itkQuaternionRigidTransformGradientDescentOptimizer.h"
#include "itkOnePlusOneEvolutionaryOptimizer.h"
#include "itkGTest.h"


#include <iostream>


/**
 *
 *  This file performs only simple C++ tests of
 *  the base classes in the Optimizers hierarchy.
 *
 *  Nothing numerical is computed in these tests,
 *  only code conformance.
 */

TEST(OptimizersHierarchy, ConvertedLegacyTest)
{

  using OptimizerType = itk::Optimizer;
  auto genericOptimizer = OptimizerType::New();

  constexpr unsigned int spaceDimension{ 10 };

  OptimizerType::ParametersType       initialPosition(spaceDimension);
  const OptimizerType::ParametersType currentPosition(spaceDimension);
  OptimizerType::ScalesType           parameterScale(spaceDimension, 1.5);
  initialPosition.Fill(2.0);

  genericOptimizer->SetInitialPosition(initialPosition);
  genericOptimizer->SetScales(parameterScale);

  const OptimizerType::ScalesType & parameterScaleGot = genericOptimizer->GetScales();

  constexpr double tolerance{ 1e-10 };

  for (unsigned int i = 0; i < spaceDimension; ++i)
  {
    EXPECT_NEAR(parameterScaleGot[i], parameterScale[i], tolerance)
      << "Scale parameters are damaged after being set." << std::endl
      << "Scale was set to: " << parameterScale << std::endl
      << "Scale was got as: " << parameterScaleGot;
  }

  OptimizerType::ParametersType initialPositionGot = genericOptimizer->GetInitialPosition();

  for (unsigned int i = 0; i < spaceDimension; ++i)
  {
    EXPECT_NEAR(initialPositionGot[i], initialPosition[i], tolerance)
      << "InitialPosition parameters are damaged after being set." << std::endl
      << "InitialPosition was set to: " << initialPosition << std::endl
      << "InitialPosition was got as: " << initialPositionGot;
  }

  using NonLinearOptimizerType = itk::NonLinearOptimizer;
  auto nonLinearOptimizer = NonLinearOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(nonLinearOptimizer, NonLinearOptimizer, Optimizer);


  using SingleValuedNonLinearOptimizerType = itk::SingleValuedNonLinearOptimizer;
  auto singleValuedOptimizer = SingleValuedNonLinearOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(singleValuedOptimizer, SingleValuedNonLinearOptimizer, NonLinearOptimizer);


  using AmoebaOptimizerType = itk::AmoebaOptimizer;
  auto amoeba = AmoebaOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(amoeba, AmoebaOptimizer, SingleValuedNonLinearVnlOptimizer);


  using ConjugateGradientOptimizerType = itk::ConjugateGradientOptimizer;
  auto conjugate = ConjugateGradientOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(conjugate, ConjugateGradientOptimizer, SingleValuedNonLinearVnlOptimizer);


  using LBFGSOptimizerType = itk::LBFGSOptimizer;
  auto lbfgs = LBFGSOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(lbfgs, LBFGSOptimizer, SingleValuedNonLinearVnlOptimizer);


  // Note that a "Versor" is a Unit Quaternion
  using VersorOptimizerType = itk::VersorTransformOptimizer;
  auto versorOpt = VersorOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(versorOpt, VersorTransformOptimizer, RegularStepGradientDescentBaseOptimizer);


  using QuaternionOptimizerType = itk::QuaternionRigidTransformGradientDescentOptimizer;
  auto quaternionOpt = QuaternionOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(
    quaternionOpt, QuaternionRigidTransformGradientDescentOptimizer, GradientDescentOptimizer);

  using OnePlusOneEvolutionaryOptimizerType = itk::OnePlusOneEvolutionaryOptimizer;
  auto onePlusOne = OnePlusOneEvolutionaryOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(onePlusOne, OnePlusOneEvolutionaryOptimizer, SingleValuedNonLinearOptimizer);

  using CumulativeGaussianOptimizerType = itk::CumulativeGaussianOptimizer;
  auto cumGaussOpt = CumulativeGaussianOptimizerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(cumGaussOpt, CumulativeGaussianOptimizer, MultipleValuedNonLinearOptimizer);


  using CumulativeGaussianCostFunctionType = itk::CumulativeGaussianCostFunction;
  auto cumGaussCostFunc = CumulativeGaussianCostFunctionType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(cumGaussCostFunc, CumulativeGaussianCostFunction, MultipleValuedCostFunction);


  // Not used; empty method body; called for coverage purposes
  const CumulativeGaussianCostFunctionType::ParametersType parameters{};
  CumulativeGaussianCostFunctionType::DerivativeType       derivative;
  cumGaussCostFunc->GetDerivative(parameters, derivative);
}
