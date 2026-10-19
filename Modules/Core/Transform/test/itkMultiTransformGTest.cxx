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

#include "itkMultiTransform.h"
#include "itkGTest.h"

#include <iostream>

#include "itkAffineTransform.h"
#include "itkTranslationTransform.h"
#include "itkDisplacementFieldTransform.h"

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
testVectorArray(const TVector & v1, const TVector & v2)
{
  bool pass = true;

  for (unsigned int i = 0; i < v1.Size(); ++i)
  {
    if (itk::Math::Absolute(v1[i] - v2[i]) > epsilon)
    {
      pass = false;
    }
  }
  return pass;
}

/******/

constexpr unsigned int itkMultiTransformTestNDimensions{ 2 };

template <class TScalar = double, unsigned int VDimension = itkMultiTransformTestNDimensions>
class MultiTransformTestTransform : public itk::MultiTransform<TScalar, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MultiTransformTestTransform);

  /** Standard class type aliases. */
  using Self = MultiTransformTestTransform;
  using Superclass = itk::MultiTransform<TScalar, VDimension, VDimension>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(MultiTransformTestTransform);

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro(Self);

  /** Sub transform type **/
  using TransformType = typename Superclass::TransformType;
  using typename Superclass::TransformTypePointer;
  /** InverseTransform type. */
  using typename Superclass::InverseTransformBasePointer;
  using typename Superclass::InputPointType;
  using typename Superclass::JacobianType;

  typename Superclass::OutputPointType
  TransformPoint(const InputPointType & point) const override
  {
    return point;
  }

  void
  ComputeJacobianWithRespectToParameters(const InputPointType & itkNotUsed(p),
                                         JacobianType &         itkNotUsed(jacobian)) const override
  {
    itkExceptionMacro("ComputeJacobianWithRespectToParamters( InputPointType, JacobianType is unimplemented for "
                      << this->GetNameOfClass());
  }

protected:
  MultiTransformTestTransform() = default;
  ~MultiTransformTestTransform() override = default;
};

} // namespace

/******/

TEST(MultiTransform, ConvertedLegacyTest)
{
  constexpr unsigned int VDimension{ itkMultiTransformTestNDimensions };

  /* Create multi-transform */
  using MultiTransformType = MultiTransformTestTransform<double, VDimension>;
  using Superclass = MultiTransformType::Superclass;
  using ScalarType = Superclass::ScalarType;

  auto multiTransform = MultiTransformType::New();

  /* Test objects */
  using Matrix2Type = itk::Matrix<ScalarType, VDimension, VDimension>;
  using Vector2Type = itk::Vector<ScalarType, VDimension>;

  /* Test that we have an empty the queue */
  EXPECT_EQ(multiTransform->GetNumberOfTransforms(), 0u) << "Failed. Expected GetNumberOfTransforms to return 0.";

  EXPECT_TRUE(multiTransform->IsTransformQueueEmpty()) << "ERROR: expected IsTransformQueueEmpty to return true.";

  /* Add an affine transform */
  using AffineType = itk::AffineTransform<ScalarType, VDimension>;
  auto        affine = AffineType::New();
  Matrix2Type matrix2;
  matrix2[0][0] = 0;
  matrix2[0][1] = -1;
  matrix2[1][0] = 1;
  matrix2[1][1] = 0;
  Vector2Type vector2;
  vector2[0] = 10;
  vector2[1] = 100;
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);

  multiTransform->AddTransform(affine);

  /* Test that we have one transform in the queue */
  EXPECT_FALSE(multiTransform->IsTransformQueueEmpty()) << "ERROR: expected IsTransformQueueEmpty to return false.";
  EXPECT_EQ(multiTransform->GetNumberOfTransforms(), 1u) << "Failed adding transform to queue.";

  /* Retrieve the transform and check that it's the same */
  std::cout << "Retrieve 1st transform." << std::endl;
  const AffineType::ConstPointer affineGet =
    dynamic_cast<const AffineType *>(multiTransform->GetNthTransformConstPointer(0));
  ASSERT_FALSE(affineGet.IsNull()) << "Failed retrieving transform from queue.";

  std::cout << "Retrieve matrix and offset. " << std::endl;
  const Matrix2Type matrix2Get = affineGet->GetMatrix();
  const Vector2Type vector2Get = affineGet->GetOffset();
  EXPECT_TRUE(testMatrix(matrix2, matrix2Get)) << "Failed retrieving correct transform data.";
  EXPECT_TRUE(testVectorArray(vector2, vector2Get)) << "Failed retrieving correct transform data.";

  /* Get parameters with single transform.
   * Should be same as GetParameters from affine transform. */
  std::cout << "Get Parameters: " << std::endl;
  Superclass::ParametersType parametersTest = multiTransform->GetParameters();
  Superclass::ParametersType parametersTruth = affine->GetParameters();
  std::cout << "affine parametersTruth: " << std::endl
            << parametersTruth << std::endl
            << "parametersTest from Multi: " << std::endl
            << parametersTest << std::endl;

  EXPECT_TRUE(testVectorArray(parametersTest, parametersTruth)) << "Failed GetParameters() for single transform.";

  /* Set parameters with single transform. */
  Superclass::ParametersType parametersNew(6);
  parametersNew[0] = 0;
  parametersNew[1] = 10;
  parametersNew[2] = 20;
  parametersNew[3] = 30;
  parametersNew[4] = 40;
  parametersNew[5] = 50;
  std::cout << "Set Parameters: " << std::endl;
  multiTransform->SetParameters(parametersNew);
  std::cout << "retrieving... " << std::endl;
  Superclass::ParametersType parametersReturned = multiTransform->GetParameters();
  std::cout << "parametersNew: " << std::endl
            << parametersNew << std::endl
            << "parametersReturned: " << std::endl
            << parametersReturned << std::endl;
  EXPECT_TRUE(testVectorArray(parametersNew, parametersReturned)) << "Failed SetParameters() for single transform.";

  /* Test fixed parameters set/get */
  parametersTest = multiTransform->GetFixedParameters();
  parametersTruth = affine->GetFixedParameters();
  std::cout << "Get Fixed Parameters: " << std::endl
            << "affine parametersTruth: " << std::endl
            << parametersTruth << std::endl
            << "parametersTest from Multi: " << std::endl
            << parametersTest << std::endl;

  EXPECT_TRUE(testVectorArray(parametersTest, parametersTruth)) << "Failed GetFixedParameters() for single transform.";

  parametersNew.SetSize(parametersTruth.Size());
  parametersNew.Fill(1);
  parametersNew[0] = 42;

  std::cout << "Set Fixed Parameters: " << std::endl;
  multiTransform->SetFixedParameters(parametersNew);
  std::cout << "retrieving... " << std::endl;
  parametersReturned = multiTransform->GetFixedParameters();
  std::cout << "parametersNew: " << std::endl
            << parametersNew << std::endl
            << "parametersReturned: " << std::endl
            << parametersReturned << std::endl;
  EXPECT_TRUE(testVectorArray(parametersNew, parametersReturned))
    << "Failed SetFixedParameters() for single transform.";

  /* Reset affine transform to original values */
  multiTransform->ClearTransformQueue();

  EXPECT_EQ(multiTransform->GetNumberOfTransforms(), 0u)
    << "Failed. Expected GetNumberOfTransforms to return 0 after ClearTransformQueue.";

  affine = AffineType::New();
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);
  multiTransform->AddTransform(affine);

  /* Test inverse */
  auto inverseMultiTransform = MultiTransformType::New();
  EXPECT_TRUE(multiTransform->GetInverse(inverseMultiTransform)) << "ERROR: GetInverse() failed.";
  auto inverseAffine = AffineType::New();
  EXPECT_TRUE(affine->GetInverse(inverseAffine)) << "FAILED getting inverse of affine.";
  EXPECT_TRUE(testVectorArray(inverseAffine->GetParameters(), inverseMultiTransform->GetParameters()))
    << "ERROR: Wrong parameters for single-transform inverse.";

  /* Test IsLinear() */
  std::cout << "Test IsLinear" << std::endl;
  EXPECT_TRUE(multiTransform->IsLinear()) << "ERROR: expected true for IsLinear but got false.";

  /* GetTransformCategory */
  EXPECT_EQ(multiTransform->GetTransformCategory(), affine->GetTransformCategory())
    << "ERROR: GetTransformCategory returned " << multiTransform->GetTransformCategory() << " instead of "
    << affine->GetTransformCategory();

  /*
   * Create and add 2nd transform, displacement field
   */

  /* Create a displacement field transform */
  using DisplacementTransformType = itk::DisplacementFieldTransform<double, VDimension>;
  auto displacementTransform = DisplacementTransformType::New();
  using FieldType = DisplacementTransformType::DisplacementFieldType;
  auto field = FieldType::New(); // This is based on itk::Image


  constexpr int         dimLength{ 4 };
  constexpr auto        size = itk::MakeFilled<FieldType::SizeType>(dimLength);
  FieldType::RegionType region{ size };
  field->SetRegions(region);
  field->Allocate();

  DisplacementTransformType::OutputVectorType vector;
  vector[0] = 0.5;
  vector[1] = 1.0;
  field->FillBuffer(vector);

  displacementTransform->SetDisplacementField(field);

  /* set inverse field */
  auto inverseField = FieldType::New(); // This is based on itk::Image
  inverseField->SetRegions(region);
  inverseField->Allocate();
  DisplacementTransformType::OutputVectorType inverseVector;
  inverseVector[0] = 0.5;
  inverseVector[1] = 1.0;
  inverseField->FillBuffer(inverseVector);
  displacementTransform->SetInverseDisplacementField(inverseField);

  std::cout << std::endl << " ** Adding 2nd transform ** " << std::endl << std::endl;

  multiTransform->ClearTransformQueue();
  multiTransform->AppendTransform(displacementTransform);
  multiTransform->PrependTransform(affine);

  std::cout << std::endl << "Two-component Multi Transform:" << std::endl << multiTransform;

  /* Test that we have two transforms in the queue */
  EXPECT_EQ(multiTransform->GetNumberOfTransforms(), 2u) << "Failed adding 2nd transform to queue.";

  EXPECT_EQ(multiTransform->GetNthTransformConstPointer(0), affine)
    << "ERROR: 1st transform is not affine as expected.";

  EXPECT_EQ(multiTransform->GetNthTransformConstPointer(1), displacementTransform)
    << "ERROR: 2nd transform is not displacementTransform as expected.";

  /* Test inverse with two transforms. */
  EXPECT_TRUE(multiTransform->GetInverse(inverseMultiTransform)) << "Expected GetInverse() to succeed.";
  std::cout << std::endl << "Inverse two-component transform: " << inverseMultiTransform;

  /* Test inverse parameters using settings from above. */

  EXPECT_TRUE(testVectorArray(inverseAffine->GetParameters(),
                              inverseMultiTransform->GetNthTransformConstPointer(0)->GetParameters()))
    << "ERROR: Wrong parameters for affine in two-transform inverse.";

  auto inverseDisplacement = DisplacementTransformType::New();
  EXPECT_TRUE(displacementTransform->GetInverse(inverseDisplacement))
    << "FAILED getting inverse of displacementTransform.";

  EXPECT_TRUE(testVectorArray(inverseDisplacement->GetParameters(),
                              inverseMultiTransform->GetNthTransformConstPointer(1)->GetParameters()))
    << "ERROR: Wrong parameters for displacementTransform in two-transform inverse.";

  /* Test IsLinear() */
  std::cout << "Test IsLinear" << std::endl;
  EXPECT_FALSE(multiTransform->IsLinear()) << "ERROR: expected false for IsLinear but got true.";

  /* Test GetNumberOfParameters */
  std::cout << "GetNumberOfParameters: " << std::endl;
  unsigned int       affineParamsN = affine->GetNumberOfParameters();
  unsigned int       displacementParamsN = displacementTransform->GetNumberOfParameters();
  const unsigned int nParameters = multiTransform->GetNumberOfParameters();
  std::cout << "Number of parameters: " << nParameters << std::endl;
  if (nParameters != affineParamsN + displacementParamsN)
  {
    std::cout << "GetNumberOfParameters failed for two-transform." << std::endl
              << "Expected " << affineParamsN + displacementParamsN << std::endl;
  }

  /* Test GetNumberOfLocalParameters */
  std::cout << "GetNumberOfLocalParameters: " << std::endl;
  const unsigned int affineLocalParamsN = affine->GetNumberOfLocalParameters();
  const unsigned int displacementLocalParamsN = displacementTransform->GetNumberOfLocalParameters();
  const unsigned int nLocalParameters = multiTransform->GetNumberOfLocalParameters();
  std::cout << "Number of local parameters: " << nParameters << std::endl;
  if (nLocalParameters != affineLocalParamsN + displacementLocalParamsN)
  {
    std::cout << "GetNumberOfLocalParameters failed for two-transform." << std::endl
              << "Expected " << affineLocalParamsN + displacementLocalParamsN << std::endl;
  }

  /* Get parameters with multi-transform. They're filled from transforms in same order as queue. */
  parametersTest = multiTransform->GetParameters();
  parametersTruth.SetSize(displacementParamsN + affineParamsN);
  /* Fill using different method than is used in the class. */
  for (unsigned int n = 0; n < affineParamsN; ++n)
  {
    parametersTruth.SetElement(n, affine->GetParameters().GetElement(n));
  }
  for (unsigned int n = 0; n < displacementParamsN; ++n)
  {
    parametersTruth.SetElement(n + affineParamsN, displacementTransform->GetParameters().GetElement(n));
  }
  std::cout << "Get Multi-transform Parameters: " << std::endl
            << "parametersTruth: " << std::endl
            << parametersTruth << std::endl
            << "parametersTest from Multi: " << std::endl
            << parametersTest << std::endl;

  EXPECT_TRUE(testVectorArray(parametersTest, parametersTruth)) << "Failed GetParameters() for two-transform.";

  /* Set parameters with multi transform. */
  parametersNew.SetSize(parametersTruth.Size());
  parametersNew.Fill(3.14);
  parametersNew[0] = 19;
  parametersNew[parametersTruth.Size() - 1] = 71;
  std::cout << "Set Multi-transform Parameters: " << std::endl;
  multiTransform->SetParameters(parametersNew);
  std::cout << "retrieving... " << std::endl;
  parametersReturned = multiTransform->GetParameters();
  // std::cout << "parametersNew: " << std::endl << parametersNew << std::endl << "parametersReturned: " << std::endl <<
  // parametersReturned << std::endl;
  EXPECT_TRUE(testVectorArray(parametersNew, parametersReturned)) << "Failed SetParameters() for two-transform.";

  /* reset the original parameters */
  multiTransform->SetParameters(parametersTruth);

  /* Test get fixed parameters with multi-transform */
  std::cout << "Get Multi-transform Fixed Parameters: " << std::endl;
  parametersTest = multiTransform->GetFixedParameters();
  affineParamsN = affine->GetFixedParameters().Size();
  displacementParamsN = displacementTransform->GetFixedParameters().Size();
  parametersTruth.SetSize(displacementParamsN + affineParamsN);
  parametersTruth.Fill(0); // Try this to quiet valgrind
  for (unsigned int n = 0; n < affineParamsN; ++n)
  {
    parametersTruth.SetElement(n, affine->GetFixedParameters().GetElement(n));
  }
  for (unsigned int n = 0; n < displacementParamsN; ++n)
  {
    parametersTruth.SetElement(n + affineParamsN, displacementTransform->GetFixedParameters().GetElement(n));
  }
  std::cout << std::endl
            << "Fixed: parametersTruth: " << std::endl
            << parametersTruth << std::endl
            << "parametersTest: " << std::endl
            << parametersTest << std::endl;

  EXPECT_TRUE(testVectorArray(parametersTest, parametersTruth)) << "Failed GetFixedParameters() for multi transform.";

  /* Test set fixed parameters with multi-transform */
  std::cout << "Set Multi-transform Fixed Parameters: " << std::endl;
  multiTransform->SetFixedParameters(parametersTruth);
  std::cout << "retrieving... " << std::endl;
  parametersReturned = multiTransform->GetFixedParameters();
  std::cout << "parametersTruth: " << std::endl
            << parametersTruth << std::endl
            << "parametersReturned: " << std::endl
            << parametersReturned << std::endl;

  EXPECT_TRUE(testVectorArray(parametersTruth, parametersReturned))
    << "Failed SetFixedParameters() for multi transform.";

  /* reset the original inverse field */
  displacementTransform->SetInverseDisplacementField(inverseField);

  /* Test GetNumberOfFixedParameters */
  std::cout << "GetNumberOfFixedParameters: " << std::endl;
  const unsigned int affineFixedParamsN = affine->GetFixedParameters().size();
  const unsigned int displacementFixedParamsN = displacementTransform->GetFixedParameters().size();
  const unsigned int nFixedParameters = multiTransform->GetNumberOfFixedParameters();
  std::cout << "Number of Fixed parameters: " << nParameters << std::endl;
  if (nFixedParameters != affineFixedParamsN + displacementFixedParamsN)
  {
    std::cout << "GetNumberOfFixedParameters failed for two-transform." << std::endl
              << "Expected " << affineFixedParamsN + displacementFixedParamsN << std::endl;
  }

  /*
   * Add a third transform
   */
  auto affine3 = AffineType::New();
  matrix2[0][0] = 0;
  matrix2[0][1] = -1;
  matrix2[1][0] = 1;
  matrix2[1][1] = 0;
  vector2[0] = 10;
  vector2[1] = 100;
  affine3->SetMatrix(matrix2);
  affine3->SetOffset(vector2);

  multiTransform->AddTransform(affine3);

  /* Reset first affine to non-singular values */
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);

  /* Test accessors */
  const Superclass::TransformQueueType transformQueue = multiTransform->GetTransformQueue();
  EXPECT_EQ(transformQueue.size(), 3u) << "Failed getting transform queue.";
  std::cout << "Got TransformQueue." << std::endl;

  std::cout << "MultiTransform with 3 transforms: " << std::endl << multiTransform << std::endl;

  /* Get inverse */
  auto inverseTransform3 = MultiTransformType::New();
  EXPECT_TRUE(multiTransform->GetInverse(inverseTransform3)) << "Failed calling GetInverse() (3).";

  /* Test UpdateTransformParameters.
   * NOTE Once there are transforms that do something other than simple
   * addition in TransformUpdateParameters, this should be updated here.
   */
  {
    std::cout << "Testing UpdateTransformParameters 1. " << std::endl;
    Superclass::ParametersType       truth = multiTransform->GetParameters();
    Superclass::DerivativeType       update(multiTransform->GetNumberOfParameters(), 10.0);
    constexpr AffineType::ScalarType factor{ 0.5 };
    truth += update * factor;
    multiTransform->UpdateTransformParameters(update, factor);
    const Superclass::ParametersType updateResult = multiTransform->GetParameters();
    EXPECT_TRUE(testVectorArray(truth, updateResult)) << "UpdateTransformParameters 1 failed. " << std::endl
                                                      << " truth:  " << truth << std::endl
                                                      << " result: " << updateResult;

    /* Test with wrong size for update */
    update.SetSize(1);
    EXPECT_THROW(multiTransform->UpdateTransformParameters(update, factor), itk::ExceptionObject);
  }

  /* Test SetParameters with wrong size array */
  std::cout << std::endl << "Test SetParameters with wrong size array. EXPECT EXCEPTION:" << std::endl;
  parametersTruth.SetSize(1);
  EXPECT_THROW(multiTransform->SetParameters(parametersTruth), itk::ExceptionObject);

  /* Test SetFixedParameters with wrong size array */
  std::cout << std::endl << "Test SetFixedParameters with wrong size array. EXPECT EXCEPTION:" << std::endl;
  EXPECT_THROW(multiTransform->SetFixedParameters(parametersTruth), itk::ExceptionObject);

  /* GetTransformCategory */
  EXPECT_EQ(multiTransform->GetTransformCategory(), MultiTransformType::TransformCategoryEnum::UnknownTransformCategory)
    << "ERROR: GetTransformCategory returned " << multiTransform->GetTransformCategory() << " instead of Unknown.";

  /* RemoveTransform. From end of queue */
  multiTransform->RemoveTransform();
  EXPECT_EQ(multiTransform->GetNumberOfTransforms(), 2u)
    << "ERROR: Wrong number of transforms after RemoveTransform: " << multiTransform->GetNumberOfTransforms();

  /* Get front and back transforms */
  if (multiTransform->GetFrontTransform() != affine)
  {
    std::cout << "ERROR: GetFrontTransform failed." << std::endl;
  }
  if (multiTransform->GetBackTransform() != displacementTransform)
  {
    std::cout << "ERROR: GetBackTransform failed." << std::endl;
  }

  /* Test printing */
  multiTransform->Print(std::cout);

  std::cout << "Passed test!" << std::endl;
}
