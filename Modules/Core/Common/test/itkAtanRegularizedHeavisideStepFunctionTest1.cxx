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

#include "itkAtanRegularizedHeavisideStepFunction.h"
#include "itkTestingMacros.h"

int
itkAtanRegularizedHeavisideStepFunctionTest1(int, char *[])
{
  using InputType = double;
  using OutputType = double;

  using HeavisideFunctionBaseType = itk::AtanRegularizedHeavisideStepFunction<InputType, OutputType>;

  auto functionBase0 = HeavisideFunctionBaseType::New();

  std::cout << "GetNameOfClass() = " << functionBase0->GetNameOfClass() << std::endl;
  functionBase0->Print(std::cout);

  constexpr double epsilon = -1.0;

  ITK_TRY_EXPECT_EXCEPTION(functionBase0->SetEpsilon(epsilon));


  constexpr double epsilon0 = 1.0;
  constexpr double epsilon1 = 1e-4;

  ITK_TEST_SET_GET_VALUE(epsilon0, functionBase0->GetEpsilon());

  functionBase0->SetEpsilon(epsilon1);
  ITK_TEST_SET_GET_VALUE(epsilon1, functionBase0->GetEpsilon());

  constexpr double epsilon2 = 0.5;
  functionBase0->SetEpsilon(epsilon2);

  constexpr int minValue = -20;
  constexpr int maxValue = 20;

  constexpr InputType incValue = 0.1;

  for (int x = minValue; x < maxValue; ++x)
  {
    const InputType  ix = x * incValue;
    const OutputType f = functionBase0->Evaluate(ix);
    const OutputType df = functionBase0->EvaluateDerivative(ix);
    std::cout << ix << ' ' << f << ' ' << df << std::endl;
  }

  return EXIT_SUCCESS;
}
