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
#include "itkGTest.h"

namespace
{
constexpr double epsilon{ 1e-10 };

template <typename TMatrix>
bool
testMatrix(const TMatrix & m1, const TMatrix & m2)
{
  bool pass = true;

  for (unsigned int i = 0; i < TMatrix::RowDimensions; ++i)
  {
    for (unsigned int j = 0; j < TMatrix::ColumnDimensions; ++j)
    {
      if (itk::Math::Absolute(m1[i][j] - m2[i][j]) > epsilon)
      {
        pass = false;
      }
    }
  }
  return pass;
}

template <typename TVector>
bool
testVector(const TVector & v1, const TVector & v2)
{
  bool pass = true;

  for (unsigned int i = 0; i < TVector::Dimension; ++i)
  {
    if (itk::Math::Absolute(v1[i] - v2[i]) > epsilon)
    {
      pass = false;
    }
  }
  return pass;
}
} // namespace

TEST(TransformClone, ConvertedLegacyTest)
{
  using AffineTransformType = itk::AffineTransform<double, 3>;
  using Transform3DType = itk::Transform<double, 3, 3>;
  auto                                  affineXfrm = AffineTransformType::New();
  AffineTransformType::OutputVectorType axis;
  axis[0] = -1.0;
  axis[1] = 1.0;
  axis[2] = 0.0;
  affineXfrm->Rotate3D(axis, 1.3);
  axis[0] = 0.0;
  axis[1] = 0.0;
  axis[2] = -1.0;
  affineXfrm->Rotate3D(axis, 0.5);
  AffineTransformType::OutputVectorType offset;
  offset[0] = 999.0;
  offset[1] = -31415926.0;
  offset[2] = 32.768;
  affineXfrm->Translate(offset);

  const Transform3DType::Pointer     clonePtr = affineXfrm->Clone().GetPointer();
  const AffineTransformType::Pointer cloneAffineXfrm = dynamic_cast<AffineTransformType *>(clonePtr.GetPointer());

  ASSERT_FALSE(cloneAffineXfrm.IsNull()) << "Failed to downcast return value from Clone to "
                                         << "AffineTransform, reported type is "
                                         << clonePtr->GetTransformTypeAsString();
  const AffineTransformType::MatrixType & cloneMatrix = cloneAffineXfrm->GetMatrix();
  const AffineTransformType::OffsetType & cloneOffset = cloneAffineXfrm->GetOffset();
  EXPECT_TRUE(testMatrix(cloneMatrix, affineXfrm->GetMatrix())) << "Matrix mismatch between original and clone";
  EXPECT_TRUE(testVector(cloneOffset, affineXfrm->GetOffset())) << "Offset mismatch between original and clone";
  using CompositeTransformType = itk::CompositeTransform<double, 3>;
  auto compositeXfrm = CompositeTransformType::New();
  compositeXfrm->AddTransform(clonePtr);
  compositeXfrm->SetOnlyMostRecentTransformToOptimizeOn();

  const CompositeTransformType::Pointer cloneCompositeXfrm = compositeXfrm->Clone().GetPointer();

  ASSERT_EQ(compositeXfrm->GetNumberOfTransforms(), cloneCompositeXfrm->GetNumberOfTransforms())
    << "Number of transforms doesn't match";
  for (unsigned int i = 0; i < compositeXfrm->GetNumberOfTransforms(); ++i)
  {
    const AffineTransformType::ConstPointer originalXfrm =
      dynamic_cast<const AffineTransformType *>(compositeXfrm->GetNthTransformConstPointer(i));
    const AffineTransformType::ConstPointer cloneXfrm =
      dynamic_cast<const AffineTransformType *>(cloneCompositeXfrm->GetNthTransformConstPointer(i));

    ASSERT_FALSE(originalXfrm.IsNull() || cloneXfrm.IsNull()) << "Failed downcast to Affine Transform";
    EXPECT_TRUE(testMatrix(originalXfrm->GetMatrix(), cloneXfrm->GetMatrix()))
      << "ConstituentTransformMismatch  at " << i;

    if (compositeXfrm->GetNthTransformToOptimize(i) != cloneCompositeXfrm->GetNthTransformToOptimize(i))
    {
      std::cerr << "Transform optimize flag mismatch at " << i << std::endl;
    }
  }
}
