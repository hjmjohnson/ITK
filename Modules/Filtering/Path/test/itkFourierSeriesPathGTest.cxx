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

#include <iostream>
#include "itkFourierSeriesPath.h"
#include "itkGTest.h"

TEST(FourierSeriesPath, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };
  using PathType = itk::FourierSeriesPath<Dimension>;
  using InputType = PathType::InputType;
  using OffsetType = PathType::OffsetType;
  using VectorType = PathType::VectorType;

  auto path = PathType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path, FourierSeriesPath, ParametricPath);

  // Average value is (5,5)
  auto       cosV = itk::MakeFilled<VectorType>(5);
  VectorType sinV{};
  path->AddHarmonic(cosV, sinV);
  cosV.Fill(2.7);
  sinV.Fill(3.2);
  path->AddHarmonic(cosV, sinV);

  std::cout << "Evaluating at 0, 0.5, and 1.0: " << path->Evaluate(0) << ", " << path->Evaluate(0.5) << ", "
            << path->Evaluate(1.0) << std::endl;
  // Floating point can be imprecise, so convert to rounded int for comparison
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->Evaluate(1.0))[0]),
            static_cast<int>(0.5 + 1000 * (path->Evaluate(0.0))[0]))
    << "Evaluate() Failed";
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->Evaluate(1.0))[1]),
            static_cast<int>(0.5 + 1000 * (path->Evaluate(0.0))[1]))
    << "Evaluate() Failed";

  std::cout << "Evaluating to an index at 0, 0.5, and 1.0: " << path->EvaluateToIndex(0) << ", "
            << path->EvaluateToIndex(0.5) << ", " << path->EvaluateToIndex(1.0) << std::endl;
  EXPECT_EQ(path->EvaluateToIndex(1.0), path->EvaluateToIndex(0.0))
    << "FourierSeriesPathTest: EvaluateToIndex() Failed";

  std::cout << "Evaluating the derivative at 0, 0.5, and 1.0: " << path->EvaluateDerivative(0) << ", "
            << path->EvaluateDerivative(0.5) << ", " << path->EvaluateDerivative(1.0) << std::endl;
  // Floating point can be imprecise, so convert to rounded int for comparison
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(1.0))[0]),
            static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(0.0))[0]))
    << "EvaluateDerivative() Failed";
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(1.0))[1]),
            static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(0.0))[1]))
    << "EvaluateDerivative() Failed";

  InputType  input = 0;
  OffsetType offset = path->IncrementInput(input);
  std::cout << "Incrementing the input from 0 to " << input << ": " << offset << std::endl;

  input = 0.5;
  offset = path->IncrementInput(input);
  std::cout << "Incrementing the input from 0.5 to " << input << ": " << offset << std::endl;
  EXPECT_EQ(offset[0], -1) << "IncrementInput() Failed";
  EXPECT_EQ(offset[1], -1) << "IncrementInput() Failed";
}
