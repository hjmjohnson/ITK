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

#include "itkAffineTransform.h"
#include "itkCompositeTransform.h"
#include "itkTranslationTransform.h"
#include "itkMath.h"
#include "itkTestingMacros.h"

namespace
{

const double epsilon = 1e-10;

template <typename TPoint>
bool
testPoint(const TPoint & p1, const TPoint & p2)
{
  bool pass = true;

  for (unsigned int i = 0; i < TPoint::PointDimension; ++i)
  {
    if (itk::Math::abs(p1[i] - p2[i]) > epsilon)
    {
      pass = false;
    }
  }
  return pass;
}

template <typename TMatrix>
bool
testMatrix(const TMatrix & m1, const TMatrix & m2)
{
  bool pass = true;

  for (unsigned int i = 0; i < TMatrix::RowDimensions; ++i)
  {
    for (unsigned int j = 0; j < TMatrix::ColumnDimensions; ++j)
    {
      if (itk::Math::abs(m1[i][j] - m2[i][j]) > epsilon)
      {
        pass = false;
      }
    }
  }
  return pass;
}

template <typename TArray2D>
bool
testJacobian(const TArray2D & m1, const TArray2D & m2)
{
  bool pass = true;

  for (unsigned int i = 0; i < m1.rows(); ++i)
  {
    for (unsigned int j = 0; j < m1.cols(); ++j)
    {
      if (itk::Math::abs(m1[i][j] - m2[i][j]) > epsilon)
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
    if (itk::Math::abs(v1[i] - v2[i]) > epsilon)
    {
      pass = false;
    }
  }
  return pass;
}

} // namespace

/******/

int
itkCompositeTransformTest(int, char *[])
{
  constexpr unsigned int VDimension = 2;

  /* Create composite transform */
  using CompositeType = itk::CompositeTransform<double, VDimension>;
  using ScalarType = CompositeType::ScalarType;

  auto compositeTransform = CompositeType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(compositeTransform, CompositeTransform, MultiTransform);

  /* Test obects */
  using Matrix2Type = itk::Matrix<ScalarType, VDimension, VDimension>;
  using Vector2Type = itk::Vector<ScalarType, VDimension>;


  /* Test that we have an empty the queue */
  ITK_TEST_EXPECT_EQUAL(compositeTransform->GetNumberOfTransforms(), 0u);
  ITK_TEST_EXPECT_EQUAL(compositeTransform->GetNumberOfParameters(), 0u);
  ITK_TEST_EXPECT_EQUAL(compositeTransform->GetNumberOfFixedParameters(), 0u);
  ITK_TEST_EXPECT_EQUAL(compositeTransform->GetParameters().Size(), 0u);
  ITK_TEST_EXPECT_EQUAL(compositeTransform->GetFixedParameters().Size(), 0u);

  {
    CompositeType::InputPointType inputPoint;
    inputPoint[0] = 1.1;
    inputPoint[1] = 2.2;
    CompositeType::InputVectorType inputVector;
    inputVector[0] = 9.1;
    inputVector[1] = 8.2;

    if (!testPoint(inputPoint, compositeTransform->TransformPoint(inputPoint)))
    {
      std::cout << "Failed transforming point with empty transform." << '\n';
      return EXIT_FAILURE;
    }

    if (!testVectorArray(inputVector, compositeTransform->TransformVector(inputVector)))
    {
      std::cout << "Failed transforming vector with empty transform." << '\n';
      return EXIT_FAILURE;
    }

    if (!testVectorArray(inputVector, compositeTransform->TransformVector(inputVector, inputPoint)))
    {
      std::cout << "Failed transforming vector with empty transform." << '\n';
      return EXIT_FAILURE;
    }
  }


  /* Add an affine transform */
  using AffineType = itk::AffineTransform<ScalarType, VDimension>;
  auto        affine = AffineType::New();
  Matrix2Type matrix2;
  matrix2[0][0] = 1;
  matrix2[0][1] = 2;
  matrix2[1][0] = 3;
  matrix2[1][1] = 4;
  Vector2Type vector2;
  vector2[0] = 5;
  vector2[1] = 6;
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);

  compositeTransform->AddTransform(affine);

  /* Test that we have one transform in the queue */
  if (compositeTransform->GetNumberOfTransforms() != 1)
  {
    std::cout << "Failed adding transform to queue." << '\n';
    return EXIT_FAILURE;
  }

  // std::cout << "Composite Transform:" << '\n' << compositeTransform;

  /* Retrieve the transform and check that it's the same */
  std::cout << "Retrieve 1st transform." << '\n';
  const AffineType::ConstPointer affineGet =
    dynamic_cast<const AffineType *>(compositeTransform->GetNthTransformConstPointer(0));
  if (affineGet.IsNull())
  {
    std::cout << "Failed retrieving transform from queue." << '\n';
    return EXIT_FAILURE;
  }

  std::cout << "Retrieve matrix and offset. " << '\n';
  const Matrix2Type matrix2Get = affineGet->GetMatrix();
  const Vector2Type vector2Get = affineGet->GetOffset();
  if (!testMatrix(matrix2, matrix2Get) || !testVectorArray(vector2, vector2Get))
  {
    std::cout << "Failed retrieving correct transform data." << '\n';
    return EXIT_FAILURE;
  }

  /* Get parameters with single transform.
   * Should be same as GetParameters from affine transform. */
  std::cout << "Get Parameters: " << '\n';
  CompositeType::ParametersType parametersTest = compositeTransform->GetParameters();
  CompositeType::ParametersType parametersTruth = affine->GetParameters();
  std::cout << "affine parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersTest from Composite: " << '\n'
            << parametersTest << '\n';

  if (!testVectorArray(parametersTest, parametersTruth))
  {
    std::cout << "Failed GetParameters() for single transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Set parameters with single transform. */
  CompositeType::ParametersType parametersNew(6);
  parametersNew[0] = 0;
  parametersNew[1] = 10;
  parametersNew[2] = 20;
  parametersNew[3] = 30;
  parametersNew[4] = 40;
  parametersNew[5] = 50;
  std::cout << "Set Parameters: " << '\n';
  compositeTransform->SetParameters(parametersNew);
  std::cout << "retrieving... " << '\n';
  CompositeType::ParametersType parametersReturned = compositeTransform->GetParameters();
  std::cout << "parametersNew: " << '\n'
            << parametersNew << '\n'
            << "parametersReturned: " << '\n'
            << parametersReturned << '\n';
  if (!testVectorArray(parametersNew, parametersReturned))
  {
    std::cout << "Failed SetParameters() for single transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Test fixed parameters set/get */
  parametersTest = compositeTransform->GetFixedParameters();
  parametersTruth = affine->GetFixedParameters();
  std::cout << "Get Fixed Parameters: " << '\n'
            << "affine parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersTest from Composite: " << '\n'
            << parametersTest << '\n';

  if (!testVectorArray(parametersTest, parametersTruth))
  {
    std::cout << "Failed GetFixedParameters() for single transform." << '\n';
    return EXIT_FAILURE;
  }

  parametersNew.SetSize(parametersTruth.Size());
  parametersNew.Fill(1);
  parametersNew[0] = 42;

  std::cout << "Set Fixed Parameters: " << '\n';
  compositeTransform->SetFixedParameters(parametersNew);
  std::cout << "retrieving... " << '\n';
  parametersReturned = compositeTransform->GetFixedParameters();
  std::cout << "parametersNew: " << '\n'
            << parametersNew << '\n'
            << "parametersReturned: " << '\n'
            << parametersReturned << '\n';
  if (!testVectorArray(parametersNew, parametersReturned))
  {
    std::cout << "Failed SetFixedParameters() for single transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Reset affine transform to original values */
  compositeTransform->ClearTransformQueue();

  affine = AffineType::New();
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);
  compositeTransform->AddTransform(affine);

  /* Setup test point and truth value for tests */
  CompositeType::InputPointType inputPoint;
  inputPoint[0] = 2;
  inputPoint[1] = 3;
  CompositeType::OutputPointType affineTruth;
  affineTruth[0] = 13;
  affineTruth[1] = 24;

  CompositeType::InputVectorType inputVector;
  inputVector[0] = 0.4;
  inputVector[1] = 0.6;

  CompositeType::InputCovariantVectorType  inputCVector;
  CompositeType::OutputCovariantVectorType outputCVector;
  inputCVector[0] = 0.4;
  inputCVector[1] = 0.6;

  /* Test transforming the point with just the single affine transform */
  CompositeType::OutputPointType outputPoint = compositeTransform->TransformPoint(inputPoint);
  if (!testPoint(outputPoint, affineTruth))
  {
    std::cout << "Failed transforming point with single transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Test inverse */
  auto inverseTransform = CompositeType::New();

  if (!compositeTransform->GetInverse(inverseTransform))
  {
    std::cout << "ERROR: GetInverse() failed." << '\n';
    return EXIT_FAILURE;
  }
  CompositeType::OutputPointType inverseTruth = inputPoint;
  CompositeType::OutputPointType inverseOutput = inverseTransform->TransformPoint(affineTruth);
  std::cout << "Transform point with inverse composite transform: " << '\n'
            << "  Test point: " << affineTruth << '\n'
            << "  Truth: " << inverseTruth << '\n'
            << "  Output: " << inverseOutput << '\n';
  if (!testPoint(inverseOutput, inverseTruth))
  {
    std::cout << "Failed transform point with inverse composite transform (1)." << '\n';
    return EXIT_FAILURE;
  }

  /* Test ComputeJacobianWithRespectToParameters */
  CompositeType::InputPointType jacPoint;
  jacPoint[0] = 1;
  jacPoint[1] = 2;
  CompositeType::JacobianType jacSingle;
  affine->ComputeJacobianWithRespectToParameters(jacPoint, jacSingle);
  std::cout << "Single jacobian:" << '\n' << jacSingle << '\n';
  CompositeType::JacobianType jacComposite;
  compositeTransform->ComputeJacobianWithRespectToParameters(jacPoint, jacComposite);
  std::cout << "Composite jacobian:" << '\n' << jacComposite << '\n';
  if (!testJacobian(jacComposite, jacSingle))
  {
    std::cout << "Failed getting jacobian for single transform." << '\n';
    return EXIT_FAILURE;
  }

  /*
   * Create and add 2nd transform
   */
  auto affine2 = AffineType::New();
  matrix2[0][0] = 11;
  matrix2[0][1] = 22;
  matrix2[1][0] = 33;
  matrix2[1][1] = 44;
  vector2[0] = 55;
  vector2[1] = 65;
  affine2->SetMatrix(matrix2);
  affine2->SetOffset(vector2);

  compositeTransform->ClearTransformQueue();
  compositeTransform->AppendTransform(affine2);
  compositeTransform->PrependTransform(affine);

  std::cout << '\n' << "Two-component Composite Transform:" << '\n' << compositeTransform;
  std::cout << '\n' << "Transform at queue position 0: " << '\n' << compositeTransform->GetNthTransformConstPointer(0);

  /* Test that we have two transforms in the queue */
  if (compositeTransform->GetNumberOfTransforms() != 2)
  {
    std::cout << "Failed adding 2nd transform to queue." << '\n';
    return EXIT_FAILURE;
  }

  /* Transform a point with both transforms. Remember that transforms
   * are applied in *reverse* queue order, with most-recently added transform first. */
  CompositeType::OutputPointType compositeTruth = affine2->TransformPoint(inputPoint);
  compositeTruth = affine->TransformPoint(compositeTruth);

  outputPoint = compositeTransform->TransformPoint(inputPoint);
  std::cout << "Transform point with two-component composite transform: " << '\n'
            << "  Test point: " << inputPoint << '\n'
            << "  Truth: " << compositeTruth << '\n'
            << "  Output: " << outputPoint << '\n';

  if (!testPoint(outputPoint, compositeTruth))
  {
    std::cout << "Failed transforming point with two transforms." << '\n';
    return EXIT_FAILURE;
  }

  CompositeType::OutputVectorType compositeTruthVector = affine2->TransformVector(inputVector);
  compositeTruthVector = affine->TransformVector(compositeTruthVector);
  const CompositeType::OutputVectorType outputVector = compositeTransform->TransformVector(inputVector);
  std::cout << "Transform vector with two-component composite transform: " << '\n'
            << "  Test vector: " << inputVector << '\n'
            << "  Truth: " << compositeTruthVector << '\n'
            << "  Output: " << outputVector << '\n';

  CompositeType::OutputCovariantVectorType compositeTruthCVector = affine2->TransformCovariantVector(inputCVector);
  compositeTruthCVector = affine->TransformCovariantVector(compositeTruthCVector);
  outputCVector = compositeTransform->TransformCovariantVector(inputCVector);
  std::cout << "Transform covariant vector with two-component composite transform: " << '\n'
            << "  Test vector: " << inputCVector << '\n'
            << "  Truth: " << compositeTruthCVector << '\n'
            << "  Output: " << outputCVector << '\n';


  CompositeType::InputDiffusionTensor3DType inputTensor;
  inputTensor[0] = 3.0;
  inputTensor[1] = 0.3;
  inputTensor[2] = 0.2;
  inputTensor[3] = 2.0;
  inputTensor[4] = 0.1;
  inputTensor[5] = 1.0;
  CompositeType::OutputDiffusionTensor3DType compositeTruthTensor = affine2->TransformDiffusionTensor3D(inputTensor);
  compositeTruthTensor = affine->TransformDiffusionTensor3D(compositeTruthTensor);
  const CompositeType::OutputDiffusionTensor3DType outputTensor =
    compositeTransform->TransformDiffusionTensor3D(inputTensor);
  std::cout << "Transform tensor with two-component composite transform: " << '\n'
            << "  Test tensor: " << inputTensor << '\n'
            << "  Truth: " << compositeTruthTensor << '\n'
            << "  Output: " << outputTensor << '\n';

  CompositeType::InputSymmetricSecondRankTensorType inputSTensor;
  inputSTensor(1, 0) = 0.5;
  inputSTensor(0, 0) = 3.0;
  inputSTensor(1, 1) = 2.0;

  CompositeType::OutputSymmetricSecondRankTensorType compositeTruthSTensor =
    affine2->TransformSymmetricSecondRankTensor(inputSTensor);
  compositeTruthSTensor = affine->TransformSymmetricSecondRankTensor(compositeTruthSTensor);
  const CompositeType::OutputSymmetricSecondRankTensorType outputSTensor =
    compositeTransform->TransformSymmetricSecondRankTensor(inputSTensor);
  std::cout << "Transform tensor with two-component composite transform: " << '\n'
            << "  Test tensor: " << inputSTensor << '\n'
            << "  Truth: " << compositeTruthSTensor << '\n'
            << "  Output: " << outputSTensor << '\n';

  /* Test inverse with two transforms, with only one set to optimize. */
  compositeTransform->SetAllTransformsToOptimize(false);
  compositeTransform->SetNthTransformToOptimizeOn(0);
  if (!compositeTransform->GetInverse(inverseTransform))
  {
    std::cout << "Expected GetInverse() to succeed." << '\n';
    return EXIT_FAILURE;
  }
  std::cout << "Inverse two-component transform: " << inverseTransform;

  /* Check that optimization flag inverse worked */
  if (inverseTransform->GetNthTransformToOptimize(0) || !inverseTransform->GetNthTransformToOptimize(1))
  {
    std::cout << "GetInverse failed for TransformsToOptimize flags." << '\n';
    return EXIT_FAILURE;
  }
  compositeTransform->SetAllTransformsToOptimizeOn(); // Set back to do all.
  inverseTransform->SetAllTransformsToOptimizeOn();

  /* Transform point with inverse */
  inverseTruth = inputPoint;
  inverseOutput = inverseTransform->TransformPoint(compositeTruth);
  std::cout << "Transform point with two-component inverse composite transform: " << '\n'
            << "  Test point: " << compositeTruth << '\n'
            << "  Truth: " << inverseTruth << '\n'
            << "  Output: " << inverseOutput << '\n';
  if (!testPoint(inverseOutput, inverseTruth))
  {
    std::cout << "Failed transform point with two-component inverse composite transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Get inverse transform again, but using other accessor. */

  std::cout << "Call GetInverseTransform():" << '\n';
  const CompositeType::ConstPointer inverseTransform2 =
    dynamic_cast<const CompositeType *>(compositeTransform->GetInverseTransform().GetPointer());
  if (!inverseTransform2)
  {
    std::cout << "Failed calling GetInverseTransform()." << '\n';
    return EXIT_FAILURE;
  }
  std::cout << "Transform point: " << '\n';
  inverseOutput = inverseTransform2->TransformPoint(compositeTruth);
  if (!testPoint(inverseOutput, inverseTruth))
  {
    std::cout << "Failed transform point with two-component inverse composite transform (2)." << '\n';
    return EXIT_FAILURE;
  }

  /* Test IsLinear() by calling on each sub transform */
  std::cout << "Test IsLinear" << '\n';
  bool allAreLinear = true;
  for (unsigned int n = 0; n < compositeTransform->GetNumberOfTransforms(); ++n)
  {
    if (!compositeTransform->GetNthTransformConstPointer(n)->IsLinear())
    {
      allAreLinear = false;
    }
  }
  if (compositeTransform->IsLinear() != allAreLinear)
  {
    std::cout << "compositeTransform returned unexpected value for IsLinear(). Expected " << allAreLinear << '\n';
    return EXIT_FAILURE;
  }

  /* Test GetNumberOfParameters */
  std::cout << "GetNumberOfParameters: " << '\n';
  unsigned int       affineParamsN = affine->GetNumberOfParameters();
  unsigned int       affine2ParamsN = affine2->GetNumberOfParameters();
  const unsigned int nParameters = compositeTransform->GetNumberOfParameters();
  std::cout << "Number of parameters: " << nParameters << '\n';
  if (nParameters != affineParamsN + affine2ParamsN)
  {
    std::cout << "GetNumberOfParameters failed for multi-transform." << '\n'
              << "Expected " << affineParamsN + affine2ParamsN << '\n';
  }

  /* Get parameters with multi-transform. They're filled from transforms in
   * same order as transforms are applied, from back of queue to front. */
  parametersTest = compositeTransform->GetParameters();
  parametersTruth.SetSize(affine2ParamsN + affineParamsN);
  /* Fill using different method than is used in the class.
     Remember we added affine2 2nd, so it's at front of queue */
  for (unsigned int n = 0; n < affine2ParamsN; ++n)
  {
    parametersTruth.SetElement(n, affine2->GetParameters().GetElement(n));
  }
  for (unsigned int n = 0; n < affineParamsN; ++n)
  {
    parametersTruth.SetElement(n + affine2ParamsN, affine->GetParameters().GetElement(n));
  }
  std::cout << "Get Multi-transform Parameters: " << '\n'
            << "parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersTest from Composite: " << '\n'
            << parametersTest << '\n';

  if (!testVectorArray(parametersTest, parametersTruth))
  {
    std::cout << "Failed GetParameters() for multi transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Set parameters with multi transform. */
  parametersNew.SetSize(parametersTruth.Size());
  parametersNew.Fill(3.14);
  parametersNew[0] = 19;
  parametersNew[parametersTruth.Size() - 1] = 71;
  std::cout << "Set Multi-transform Parameters: " << '\n';
  compositeTransform->SetParameters(parametersNew);
  std::cout << "retrieving... " << '\n';
  parametersReturned = compositeTransform->GetParameters();
  std::cout << "parametersNew: " << '\n'
            << parametersNew << '\n'
            << "parametersReturned: " << '\n'
            << parametersReturned << '\n';
  if (!testVectorArray(parametersNew, parametersReturned))
  {
    std::cout << "Failed SetParameters() for multi transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Test get fixed parameters with multi-transform */
  parametersTest = compositeTransform->GetFixedParameters();
  affineParamsN = affine->GetFixedParameters().Size();
  affine2ParamsN = affine2->GetFixedParameters().Size();
  parametersTruth.SetSize(affine2ParamsN + affineParamsN);
  parametersTruth.Fill(0); // Try this to quiet valgrind
  for (unsigned int n = 0; n < affine2ParamsN; ++n)
  {
    parametersTruth.SetElement(n, affine2->GetFixedParameters().GetElement(n));
  }
  for (unsigned int n = 0; n < affineParamsN; ++n)
  {
    parametersTruth.SetElement(n + affine2ParamsN, affine->GetFixedParameters().GetElement(n));
  }
  std::cout << "Get Multi-transform Fixed Parameters: " << '\n'
            << "parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersTest: " << '\n'
            << parametersTest << '\n';

  if (!testVectorArray(parametersTest, parametersTruth))
  {
    std::cout << "Failed GetFixedParameters() for multi transform." << '\n';
    return EXIT_FAILURE;
  }

  /* Test set fixed parameters with multi-transform */
  std::cout << "Set Multi-transform Fixed Parameters: " << '\n';
  compositeTransform->SetFixedParameters(parametersTruth);
  std::cout << "retrieving... " << '\n';
  parametersReturned = compositeTransform->GetFixedParameters();
  std::cout << "parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersReturned: " << '\n'
            << parametersReturned << '\n';
  // std::cout << "Composite Transform: " << '\n' << compositeTransform;
  if (!testVectorArray(parametersTruth, parametersReturned))
  {
    std::cout << "Failed SetFixedParameters() for multi transform." << '\n';
    return EXIT_FAILURE;
  }

  /*
   * Add a third transform
   */

  /* Add yet another affine transform */
  auto affine3 = AffineType::New();
  matrix2[0][0] = 1.1;
  matrix2[0][1] = 2.2;
  matrix2[1][0] = 3.3;
  matrix2[1][1] = 4.4;
  vector2[0] = 5.5;
  vector2[1] = 6.5;
  affine3->SetMatrix(matrix2);
  affine3->SetOffset(vector2);

  compositeTransform->AddTransform(affine3);
  // std::cout << "compositeTransform with 3 subs: "
  //          << '\n' << compositeTransform << '\n';

  /* Reset first affine to non-singular values */
  matrix2[0][0] = 1;
  matrix2[0][1] = 2;
  matrix2[1][0] = 3;
  matrix2[1][1] = 4;
  vector2[0] = 5;
  vector2[1] = 6;
  affine->SetMatrix(matrix2);
  affine->SetOffset(vector2);

  /* Test TransformsToOptimize flags */
  compositeTransform->SetAllTransformsToOptimizeOff();
  if (compositeTransform->GetNthTransformToOptimize(0) || compositeTransform->GetNthTransformToOptimize(1) ||
      compositeTransform->GetNthTransformToOptimize(2))
  {
    std::cout << "Failed clearing all TransformToOptimize flags. " << '\n';
    return EXIT_FAILURE;
  }

  compositeTransform->SetOnlyMostRecentTransformToOptimizeOn();
  if (compositeTransform->GetNthTransformToOptimize(0) || compositeTransform->GetNthTransformToOptimize(1) ||
      !compositeTransform->GetNthTransformToOptimize(2))
  {
    std::cout << "Failed setting only most recent TransformsToOptimize flag. " << '\n';
    return EXIT_FAILURE;
  }

  /* Test accessors */
  const CompositeType::TransformQueueType transformQueue = compositeTransform->GetTransformQueue();
  if (transformQueue.size() != 3)
  {
    std::cout << "Failed getting transform queue." << '\n';
    return EXIT_FAILURE;
  }
  std::cout << "Got TransformQueue." << '\n';

  const CompositeType::TransformsToOptimizeFlagsType flagsQueue = compositeTransform->GetTransformsToOptimizeFlags();
  if (flagsQueue.size() != 3)
  {
    std::cout << "Failed getting optimize flags queue." << '\n';
    return EXIT_FAILURE;
  }

  /* Get inverse and check TransformsToOptimize flags are correct */
  const CompositeType::ConstPointer inverseTransform3 =
    dynamic_cast<const CompositeType *>(compositeTransform->GetInverseTransform().GetPointer());
  if (!inverseTransform3)
  {
    std::cout << "Failed calling GetInverseTransform() (3)." << '\n';
    return EXIT_FAILURE;
  }
  if (!inverseTransform3->GetNthTransformToOptimize(0) || inverseTransform3->GetNthTransformToOptimize(1) ||
      inverseTransform3->GetNthTransformToOptimize(2))
  {
    std::cout << "Failed checking TransformsToOptimize flags on inverse. " << '\n';
    return EXIT_FAILURE;
  }

  /* Test get params with only 1st and last transforms set to optimize.
   * This implicitly tests the m_PreviousTransformsToOptimizeUpdateTime mechanism
   * for updating m_TransformsToOptimizeQueue.
   * This includes the affine and affine3 transforms */

  compositeTransform->SetNthTransformToOptimize(0, true);
  if (!compositeTransform->GetNthTransformToOptimize(0) || compositeTransform->GetNthTransformToOptimize(1) ||
      !compositeTransform->GetNthTransformToOptimize(2))
  {
    std::cout << "Failed setting last TransformToOptimize flag. "
              << "Composite Transform: " << '\n'
              << compositeTransform << '\n';
    return EXIT_FAILURE;
  }

  parametersTest = compositeTransform->GetParameters();
  affineParamsN = affine->GetNumberOfParameters();
  const unsigned int affine3ParamsN = affine3->GetNumberOfParameters();
  parametersTruth.SetSize(affineParamsN + affine3ParamsN);
  for (unsigned int n = 0; n < affine3ParamsN; ++n)
  {
    parametersTruth.SetElement(n, affine3->GetParameters().GetElement(n));
  }
  for (unsigned int n = 0; n < affineParamsN; ++n)
  {
    parametersTruth.SetElement(n + affine3ParamsN, affine->GetParameters().GetElement(n));
  }
  std::cout << "Get 1st and 3rd transform Parameters: " << '\n'
            << "parametersTruth: " << '\n'
            << parametersTruth << '\n'
            << "parametersTest from Composite: " << '\n'
            << parametersTest << '\n';

  if (!testVectorArray(parametersTest, parametersTruth))
  {
    std::cout << "Failed GetParameters() for 1st and 3rd transforms." << '\n';
    return EXIT_FAILURE;
  }

  /* Test ComputeJacobianWithRespectToParameters with three transforms, two of which (1st and 3rd) are active.
   * Remember that the point gets transformed by preceding transforms
   * before its used for individual Jacobian. */
  std::cout << "Test ComputeJacobianWithRespectToParameters with three transforms: " << '\n';
  CompositeType::InputPointType jacPoint2;
  jacPoint2[0] = 1;
  jacPoint2[1] = 2;
  CompositeType::JacobianType jacComposite2;
  compositeTransform->ComputeJacobianWithRespectToParameters(jacPoint2, jacComposite2);
  CompositeType::JacobianType jacAffine3;
  affine3->ComputeJacobianWithRespectToParameters(jacPoint2, jacAffine3);
  jacPoint2 = affine3->TransformPoint(jacPoint2);
  jacPoint2 = affine2->TransformPoint(jacPoint2);
  CompositeType::JacobianType jacAffine;
  affine->ComputeJacobianWithRespectToParameters(jacPoint2, jacAffine);
  CompositeType::JacobianType jacTruth;
  jacTruth.SetSize(jacAffine3.rows(), jacAffine.cols() + jacAffine3.cols());
  jacTruth.update(affine->GetMatrix() * affine2->GetMatrix() * jacAffine3, 0, 0);
  jacTruth.update(jacAffine, 0, jacAffine3.cols());
  std::cout << "transformed jacPoint: " << jacPoint2 << '\n';
  std::cout << "Affine jacobian:" << '\n' << jacAffine;
  std::cout << "affine3 jacobian:" << '\n' << jacAffine3;
  std::cout << "Truth jacobian:" << '\n' << jacTruth;
  std::cout << "Composite jacobian:" << '\n' << jacComposite2;
  if (!testJacobian(jacComposite2, jacTruth))
  {
    std::cout << "Failed getting jacobian for two active transforms." << '\n';
    return EXIT_FAILURE;
  }

  /* Test UpdateTransformParameters.
   * NOTE Once there are transforms that do something other than simple
   * addition in TransformUpdateParameters, this should be updated here.
   */
  {
    /* Single transform full update, of last transform only */
    compositeTransform->SetOnlyMostRecentTransformToOptimizeOn();
    CompositeType::ParametersType truth = compositeTransform->GetParameters();
    CompositeType::DerivativeType update(compositeTransform->GetNumberOfParameters());
    update.Fill(10);
    truth += update;
    compositeTransform->UpdateTransformParameters(update);
    CompositeType::ParametersType updateResult = compositeTransform->GetParameters();
    std::cout << "Testing UpdateTransformParameters 1. " << '\n';
    if (!testVectorArray(truth, updateResult))
    {
      std::cout << "UpdateTransformParameters 1 failed. " << '\n'
                << " truth:  " << truth << '\n'
                << " result: " << updateResult << '\n';
      return EXIT_FAILURE;
    }

    /* Update partially two transforms, with a scaling factor */
    compositeTransform->SetNthTransformToOptimizeOn(0);
    compositeTransform->SetNthTransformToOptimizeOff(1);
    truth = compositeTransform->GetParameters();
    update.SetSize(compositeTransform->GetNumberOfParameters());
    const AffineType::ScalarType factor = 0.5;
    for (unsigned int i = 0; i < compositeTransform->GetNumberOfParameters(); ++i)
    {
      update[i] = i;
      truth[i] += update[i] * factor;
    }
    compositeTransform->UpdateTransformParameters(update, factor);
    updateResult = compositeTransform->GetParameters();
    std::cout << "Testing UpdateTransformParameters 3. " << '\n';
    if (!testVectorArray(truth, updateResult))
    {
      std::cout << "UpdateTransformParameters 3 failed. " << '\n'
                << " truth:  " << truth << '\n'
                << " result: " << updateResult << '\n';
      return EXIT_FAILURE;
    }
  }

  /* Test RemoveTransform */
  const bool opt1 = compositeTransform->GetTransformsToOptimizeFlags()[0];
  const bool opt2 = compositeTransform->GetTransformsToOptimizeFlags()[1];
  compositeTransform->RemoveTransform();
  if (compositeTransform->GetNumberOfTransforms() != 2)
  {
    std::cout << "ERROR: expected 2 transforms, got " << compositeTransform->GetNumberOfTransforms() << '\n';
    return EXIT_FAILURE;
  }
  if (affine != compositeTransform->GetNthTransformConstPointer(0))
  {
    std::cout << "ERROR: 1st transform is not affine" << '\n';
    return EXIT_FAILURE;
  }
  if (affine2 != compositeTransform->GetNthTransformConstPointer(1))
  {
    std::cout << "ERROR: 2nd transform is not affine2" << '\n';
    return EXIT_FAILURE;
  }
  if (compositeTransform->GetTransformsToOptimizeFlags().size() != 2)
  {
    std::cout << "ERROR: TransformsToOptimizeQueue is not length 2. It is "
              << compositeTransform->GetTransformsToOptimizeFlags().size() << '\n';
    return EXIT_FAILURE;
  }
  if (compositeTransform->GetNthTransformToOptimize(0) != opt1)
  {
    std::cout << "ERROR: TransformsToOptimizeFlags[0] is not " << opt1 << '\n';
    return EXIT_FAILURE;
  }
  if (compositeTransform->GetNthTransformToOptimize(1) != opt2)
  {
    std::cout << "ERROR: TransformsToOptimizeFlags[1] is not " << opt2 << '\n';
    return EXIT_FAILURE;
  }

  /*
   * Test flattening transform queue in the case of nested composite
   * transforms
   */

  auto nestedCompositeTransform = CompositeType::New();
  auto compositeTransform1 = CompositeType::New();
  auto compositeTransform2 = CompositeType::New();
  auto compositeTransform3 = CompositeType::New();
  auto compositeTransform4 = CompositeType::New();

  using TranslationTransformType = itk::TranslationTransform<double, VDimension>;
  using TranslationTransformPointer = TranslationTransformType::Pointer;
  using TranslationTransformVector = std::vector<TranslationTransformPointer>;
  TranslationTransformVector translationTransformVector(12);
  for (itk::SizeValueType n = 0; n < 12; ++n)
  {
    translationTransformVector[n] = TranslationTransformType::New();
    TranslationTransformType::ParametersType params(VDimension);
    params.Fill(n);
    translationTransformVector[n]->SetParameters(params);
  }

  compositeTransform1->AddTransform(translationTransformVector[0]);
  compositeTransform1->AddTransform(translationTransformVector[1]);
  compositeTransform1->AddTransform(translationTransformVector[2]);

  compositeTransform2->AddTransform(translationTransformVector[3]);
  compositeTransform2->AddTransform(translationTransformVector[4]);

  compositeTransform3->AddTransform(translationTransformVector[5]);
  compositeTransform3->AddTransform(translationTransformVector[6]);

  compositeTransform4->AddTransform(translationTransformVector[7]);
  compositeTransform4->AddTransform(translationTransformVector[8]);
  compositeTransform4->AddTransform(translationTransformVector[9]);
  compositeTransform4->AddTransform(compositeTransform3);

  nestedCompositeTransform->AddTransform(compositeTransform1);
  nestedCompositeTransform->AddTransform(translationTransformVector[10]);
  nestedCompositeTransform->AddTransform(compositeTransform2);
  nestedCompositeTransform->AddTransform(compositeTransform4);
  nestedCompositeTransform->AddTransform(translationTransformVector[11]);

  std::cout << "Number of transforms before flattening = " << nestedCompositeTransform->GetNumberOfTransforms() << '\n';
  if (nestedCompositeTransform->GetNumberOfTransforms() != 5)
  {
    std::cerr << "Error.  Should be 5." << '\n';
    return EXIT_FAILURE;
  }

  nestedCompositeTransform->FlattenTransformQueue();
  std::cout << "Number of transforms after flattening = " << nestedCompositeTransform->GetNumberOfTransforms() << '\n';
  if (nestedCompositeTransform->GetNumberOfTransforms() != 12)
  {
    std::cerr << "Error.  Should be 12." << '\n';
    return EXIT_FAILURE;
  }

  /* Verify the transform order */
  bool passed = true;
  for (itk::SizeValueType n = 0; n < 12; ++n)
  {
    const TranslationTransformType::ParametersType & params = translationTransformVector[n]->GetParameters();
    if (itk::Math::NotExactlyEquals(params[0], n))
    {
      passed = false;
    }
  }
  if (!passed)
  {
    std::cout << "Transform are not in correct order after flattening: " << '\n';
    for (itk::SizeValueType n = 0; n < 12; ++n)
    {
      const TranslationTransformType::ParametersType & params = translationTransformVector[n]->GetParameters();
      std::cout << ' ' << params[0];
    }
    std::cout << '\n';
    return EXIT_FAILURE;
  }

  /* Test SetParameters with wrong size array */
  std::cout << "Test SetParameters with wrong size array." << '\n';
  parametersTruth.SetSize(1);
  bool caught = false;
  try
  {
    compositeTransform->SetParameters(parametersTruth);
  }
  catch (const itk::ExceptionObject & excp)
  {
    caught = true;
    std::cout << "\nCaught expected exception:" << '\n';
    std::cout << excp << '\n';
  }
  if (!caught)
  {
    std::cerr << "Expected exception calling SetParameters with wrong size" << '\n';

    return EXIT_FAILURE;
  }

  /* Test printing */
  compositeTransform->Print(std::cout);

  std::cout << "Passed test!" << '\n';
  return EXIT_SUCCESS;
}
