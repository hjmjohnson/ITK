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

#include "itkHilbertPath.h"
#include "itkNumericTraits.h"
#include "itkGTest.h"


namespace
{
template <typename PathType>
void
HilbertPathTestHelper(unsigned int maxHilbertPathOder)
{
  using IndexType = typename PathType::IndexType;

  auto path = PathType::New();

  for (unsigned int order = 1; order < maxHilbertPathOder; ++order)
  {
    path->SetHilbertOrder(order);
    EXPECT_EQ(order, path->GetHilbertOrder());

    path->Initialize();

    typename PathType::InputType input = 0;
    EXPECT_THROW(path->IncrementInput(input), itk::ExceptionObject);

    const typename PathType::InputType endOfInput = path->EndOfInput();
    std::cout << "End of input: " << typename itk::NumericTraits<typename PathType::InputType>::PrintType(endOfInput)
              << std::endl;

    for (unsigned int d = 0; d < path->NumberOfSteps(); ++d)
    {
      const IndexType index = path->Evaluate(d);

      EXPECT_EQ(d, path->EvaluateInverse(index))
        << "Incorrect match-up for path index (" << d << ") and multi-dimensional index (" << index << ')';
    }

    // path->EvaluateToIndex( 6 )

    for (unsigned int d = 0; d < path->NumberOfSteps(); ++d)
    {
      const IndexType index = path->TransformPathIndexToMultiDimensionalIndex(d);

      EXPECT_EQ(d, path->EvaluateInverse(index))
        << "Incorrect match-up for path index (" << d << ") and multi-dimensional index (" << index << ')';
    }
  }
}
} // namespace


TEST(HilbertPath, ConvertedLegacyTest)
{
  using IndexValueType = unsigned int;

  // Set a maximum Hilbert path order
  constexpr unsigned int maxHilbertPathOder{ 5 };

  // Test dimension = 2
  using HilbertPathType2D = itk::HilbertPath<IndexValueType, 2>;
  auto path2D = HilbertPathType2D::New();

  // Exercise basic object methods
  // Done outside the helper function in the test because GCC is limited
  // when calling overloaded base class functions.
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path2D, HilbertPath, Path);

  HilbertPathTestHelper<HilbertPathType2D>(maxHilbertPathOder);

  // Test dimension = 3
  using HilbertPathType3D = itk::HilbertPath<IndexValueType, 3>;
  auto path3D = HilbertPathType3D::New();

  // Exercise basic object methods
  // Done outside the helper function in the test because GCC is limited
  // when calling overloaded base class functions.
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path3D, HilbertPath, Path);

  HilbertPathTestHelper<HilbertPathType3D>(maxHilbertPathOder);

  // Test dimension = 4
  using HilbertPathType4D = itk::HilbertPath<IndexValueType, 4>;
  auto path4D = HilbertPathType4D::New();

  // Exercise basic object methods
  // Done outside the helper function in the test because GCC is limited
  // when calling overloaded base class functions.
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(path4D, HilbertPath, Path);

  HilbertPathTestHelper<HilbertPathType4D>(maxHilbertPathOder);
}
