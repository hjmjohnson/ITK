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
#include "itkPolyLineParametricPath.h"
#include "itkGTest.h"

TEST(PolyLineParametricPath, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };

  using PathType = itk::PolyLineParametricPath<Dimension>;
  using InputType = PathType::InputType;
  using OffsetType = PathType::OffsetType;
  using VertexType = PathType::VertexType;

  auto path = PathType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path, PolyLineParametricPath, ParametricPath);

  auto v = itk::MakeFilled<VertexType>(1);
  path->AddVertex(v);
  v[0] = 2;
  v[1] = 3;
  path->AddVertex(v);
  v[0] = 3;
  v[1] = 4;
  path->AddVertex(v);
  v[0] = 0;
  v[1] = 5;
  path->AddVertex(v);
  v.Fill(1);
  path->AddVertex(v);

  std::cout << "Evaluating at 0, 0.5, and 4.0: " << path->Evaluate(0) << ", " << path->Evaluate(0.5) << ", "
            << path->Evaluate(4.0) << std::endl;

  std::cout << "Evaluating to an index at 0, 0.5, and 1.0: " << path->EvaluateToIndex(0) << ", "
            << path->EvaluateToIndex(0.5) << ", " << path->EvaluateToIndex(1.0) << std::endl;
  EXPECT_EQ(path->EvaluateToIndex(4.0), path->EvaluateToIndex(0)) << "EvaluateToIndex() Failed";

  std::cout << "Evaluating the derivative at 0, 0.5, and 1.0: " << path->EvaluateDerivative(0) << ", "
            << path->EvaluateDerivative(0.5) << ", " << path->EvaluateDerivative(1.0) << std::endl;
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(0.5))[0]), 1000) << "EvaluateDerivative() Failed";
  EXPECT_EQ(static_cast<int>(0.5 + 1000 * (path->EvaluateDerivative(0.5))[1]), 2000) << "EvaluateDerivative() Failed";

  InputType  input = 0;
  OffsetType offset = path->IncrementInput(input);
  std::cout << "Incrementing the input from 0 to " << input << ": " << offset << std::endl;

  input = 0.5;
  offset = path->IncrementInput(input);
  std::cout << "Incrementing the input from 0.5 to " << input << ": " << offset << std::endl;

  // Test a degenerate path
  std::cout << "Generating degenerate path" << std::endl;
  auto path2 = PathType::New();

  // Add a bunch of points closely spaced together
  for (double k = 0; k < 10; k += 0.1)
  {
    v.Fill(k);
    path2->AddVertex(v);
  }

  // Add a point that is very far away from the first points
  v.Fill(100);
  path2->AddVertex(v);
  PathType::InputType path2Input = path2->StartOfInput();

  constexpr PathType::OffsetType zeroOffset{};

  std::cout << "Starting degenerate path test" << std::endl;
  while (true)
  {
    offset = path2->IncrementInput(path2Input);
    if (offset == zeroOffset)
    {
      break;
    }
  }
}
