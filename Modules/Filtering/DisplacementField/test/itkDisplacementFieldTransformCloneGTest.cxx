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

#include "itkAffineTransform.h"
#include "itkCompositeTransform.h"
#include "itkDisplacementFieldTransform.h"
#include "itkImageRegionConstIterator.h"
#include "itkMath.h"
#include "itkGTest.h"


namespace
{
template <typename TVector>
bool
testVector(const TVector & v1, const TVector & v2)
{
  bool             pass = true;
  constexpr double tolerance{ 1e-10 };

  for (unsigned int i = 0; i < v1.Size() && i < v2.Size(); ++i)
  {
    if (!itk::Math::FloatAlmostEqual(v1[i], v2[i], 10, tolerance))
    {
      pass = false;
    }
  }
  return pass;
}
} // namespace

TEST(DisplacementFieldTransformClone, ConvertedLegacyTest)
{
  constexpr unsigned int Dimensions{ 3 };

  using ParametersValueType = double;
  using DisplacementTransformType = itk::DisplacementFieldTransform<ParametersValueType, Dimensions>;
  using FieldType = DisplacementTransformType::DisplacementFieldType;

  // Create a displacement field transform
  auto displacementTransform = DisplacementTransformType::New();

  auto field = FieldType::New();

  constexpr int                 dimLength{ 20 };
  constexpr FieldType::SizeType size{ dimLength, dimLength, dimLength };
  FieldType::RegionType         region = { size };
  field->SetRegions(region);
  field->Allocate();

  auto zeroVector = itk::MakeFilled<DisplacementTransformType::OutputVectorType>(1);
  field->FillBuffer(zeroVector);
  displacementTransform->SetDisplacementField(field);

  const DisplacementTransformType::Pointer displacementTransformClone = displacementTransform->Clone();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(displacementTransformClone, DisplacementFieldTransform, Transform);


  ASSERT_FALSE(displacementTransformClone.IsNull());

  EXPECT_TRUE(
    testVector(displacementTransform->GetFixedParameters(), displacementTransformClone->GetFixedParameters()));

  const FieldType::ConstPointer originalField = displacementTransform->GetDisplacementField();
  const FieldType::ConstPointer cloneField = displacementTransformClone->GetDisplacementField();

  itk::ImageRegionConstIterator<FieldType> originalIt(originalField, originalField->GetLargestPossibleRegion());
  itk::ImageRegionConstIterator<FieldType> cloneIt(cloneField, cloneField->GetLargestPossibleRegion());

  for (; !originalIt.IsAtEnd() && !cloneIt.IsAtEnd(); ++originalIt, ++cloneIt)
  {
    EXPECT_TRUE(testVector(originalIt.Value(), cloneIt.Value()));
  }

  EXPECT_TRUE(originalIt.IsAtEnd());
  EXPECT_TRUE(cloneIt.IsAtEnd());
}
