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

#include "itkEuler2DTransform.h"
#include "itkGTest.h"

#include <iomanip>
#include <iostream>

#include "itkMath.h"


namespace
{
bool
CheckEqual(const itk::Point<double, 2> & p1, const itk::Point<double, 2> & p2)
{
  constexpr double epsilon{ 1e-5 };

  for (unsigned int i = 0; i < 2; ++i)
  {
    if (itk::Math::Absolute(p1[i] - p2[i]) > epsilon)
    {
      std::cout << p1 << " != " << p2 << ":[ FAILED ]" << std::endl;
      return false;
    }
  }
  std::cout << p1 << " == " << p2 << ":[ PASSED ]" << std::endl;
  return true;
}

} // namespace

TEST(Euler2DTransform, ConvertedLegacyTest)
{
  std::cout << "==================================" << std::endl;
  std::cout << "Testing Euler Angles 2D Transform" << std::endl << std::endl;

  constexpr double       epsilon{ 1e-10 };
  constexpr unsigned int N{ 2 };
  bool                   Ok = true;

  using EulerTransformType = itk::Euler2DTransform<double>;
  auto eulerTransform = EulerTransformType::New();

  // Testing Identity
  std::cout << "Testing identity transform: ";
  eulerTransform->SetIdentity();

  EulerTransformType::OffsetType offset = eulerTransform->GetOffset();
  EXPECT_EQ(offset[0], 0.0) << "[ FAILED ]";
  EXPECT_EQ(offset[1], 0.0) << "[ FAILED ]";

  std::cout << "[ PASSED ]" << std::endl;

  // 15 degrees in radians
  const double angle = 15.0 * std::atan(1.0f) / 45.0;
  const double sinth = std::sin(angle);
  const double costh = std::cos(angle);

  std::cout << "Testing Rotation:";
  eulerTransform->SetRotation(angle);

  // Rotate an itk::Point
  constexpr EulerTransformType::InputPointType::ValueType pInit[2]{ 10, 10 };
  EulerTransformType::InputPointType                      p = pInit;
  EulerTransformType::InputPointType                      q;

  q[0] = p[0] * costh - p[1] * sinth;
  q[1] = p[0] * sinth + p[1] * costh;

  EulerTransformType::OutputPointType r = eulerTransform->TransformPoint(p);
  for (unsigned int i = 0; i < N; ++i)
  {
    if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
    {
      Ok = false;
      break;
    }
  }
  EXPECT_TRUE(Ok) << "Error rotating point   : " << p << std::endl
                  << "Result should be       : " << q << std::endl
                  << "Reported Result is     : " << r;

  std::cout << " [ PASSED ] " << std::endl;


  std::cout << "Testing Translation:";

  eulerTransform->SetRotation(0);

  EulerTransformType::OffsetType::ValueType ioffsetInit[2] = { 1, 4 };
  const EulerTransformType::OffsetType      ioffset = ioffsetInit;

  eulerTransform->SetOffset(ioffset);

  q = p + ioffset;

  r = eulerTransform->TransformPoint(p);
  for (unsigned int i = 0; i < N; ++i)
  {
    if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
    {
      Ok = false;
      break;
    }
  }
  EXPECT_TRUE(Ok) << "Error translating point: " << p << std::endl
                  << "Result should be       : " << q << std::endl
                  << "Reported Result is     : " << r;

  std::cout << " [ PASSED ] " << std::endl;


  // Testing Parameters
  std::cout << "Testing Parameters: ";
  EulerTransformType::ParametersType parameters = eulerTransform->GetParameters();

  EXPECT_EQ(parameters[0], 0.0) << " [ FAILED ] ";
  EXPECT_EQ(parameters[1], 1.0) << " [ FAILED ] ";
  EXPECT_EQ(parameters[2], 4.0) << " [ FAILED ] ";
  std::cout << " [ PASSED ] " << std::endl;

  // Testing Jacobian
  std::cout << "Testing Jacobian: ";
  EulerTransformType::JacobianType jacobian;
  eulerTransform->ComputeJacobianWithRespectToParameters(pInit, jacobian);

  EXPECT_EQ(jacobian[0][0], -10.0) << " [ FAILED ] ";
  EXPECT_EQ(jacobian[0][1], 1.0) << " [ FAILED ] ";
  EXPECT_EQ(jacobian[0][2], 0.0) << " [ FAILED ] ";
  EXPECT_EQ(jacobian[1][0], 10.0) << " [ FAILED ] ";
  EXPECT_EQ(jacobian[1][1], 0.0) << " [ FAILED ] ";
  EXPECT_EQ(jacobian[1][2], 1.0) << " [ FAILED ] ";
  std::cout << " [ PASSED ] " << std::endl;

  std::cout << "Testing Angle from matrix : ";
  eulerTransform->SetIdentity();
  eulerTransform->SetRotation(0.2);

  auto t2 = EulerTransformType::New();
  t2->SetIdentity();
  t2->Compose(eulerTransform);
  EXPECT_LE(itk::Math::Absolute(t2->GetParameters()[0] - 0.2), 0.0001) << " [ FAILED ] ";
  std::cout << " [ PASSED ] " << std::endl;

  {
    // Test instantiation, inverse computation, back transform etc.
    using TransformType = EulerTransformType;
    auto t1 = TransformType::New();

    // Set parameters
    TransformType::ParametersType parameters2(t1->GetNumberOfParameters());

    parameters2[0] = -21.0 / 180.0 * itk::Math::pi;
    parameters2[1] = 67.8;
    parameters2[2] = -0.2;

    TransformType::InputPointType center;
    center[0] = 12.0;
    center[1] = -8.9;

    t1->SetParameters(parameters2);
    t1->SetCenter(center);

    TransformType::InputPointType p1;
    p1[0] = 96.8;
    p1[1] = -3.2;

    const TransformType::InputPointType p2 = t1->TransformPoint(p1);

    // Test inverse
    TransformType::Pointer t22;
    t1->CloneInverseTo(t22);

    const TransformType::InputPointType p3 = t22->TransformPoint(p2);

    std::cout << "Test CloneInverseTo(): ";
    EXPECT_TRUE(CheckEqual(p1, p3));

    auto t2dash = TransformType::New();
    t1->GetInverse(t2dash);
    TransformType::InputPointType p3dash;
    p3dash = t2dash->TransformPoint(p2);

    std::cout << "Test GetInverse(): ";
    EXPECT_TRUE(CheckEqual(p1, p3dash));

    t2dash = dynamic_cast<TransformType *>(t1->GetInverseTransform().GetPointer());
    ASSERT_NE(t2dash, nullptr) << "Cannot compute inverse transformation";
    p3dash = t2dash->TransformPoint(p2);

    std::cout << "Test GetInverseTransform(): ";
    EXPECT_TRUE(CheckEqual(p1, p3dash));

    // Test clone
    TransformType::Pointer t3;
    t1->CloneTo(t3);

    const TransformType::InputPointType p4 = t3->TransformPoint(p1);

    std::cout << "Test Clone(): ";
    EXPECT_TRUE(CheckEqual(p2, p4));

    // Test compose
    auto t4 = TransformType::New();

    parameters2[0] = 14.7 / 180.0 * itk::Math::pi;
    parameters2[1] = 67.1;
    parameters2[2] = 67.1;

    center.Fill(4.0);

    t4->SetParameters(parameters2);
    t4->SetCenter(center);

    TransformType::Pointer t5;
    t1->CloneTo(t5);
    t5->Compose(t4, false);

    TransformType::InputPointType p5 = t1->TransformPoint(p1);
    TransformType::InputPointType p6 = t4->TransformPoint(p5);
    TransformType::InputPointType p7 = t5->TransformPoint(p1);

    std::cout << "Test Compose(.,false): ";
    EXPECT_TRUE(CheckEqual(p6, p7));

    t1->CloneTo(t5);
    t5->Compose(t4, true);

    p5 = t4->TransformPoint(p1);
    p6 = t1->TransformPoint(p5);
    p7 = t5->TransformPoint(p1);

    std::cout << "Test Compose(.,true): ";
    EXPECT_TRUE(CheckEqual(p6, p7));

    // Really test the jacobian
    std::cout << "Testing Jacobian: ";
    TransformType::JacobianType jacobian2;
    t4->ComputeJacobianWithRespectToParameters(p1, jacobian2);

    TransformType::JacobianType approxJacobian = jacobian2;
    for (unsigned int k = 0; k < t1->GetNumberOfParameters(); ++k)
    {
      constexpr double              delta{ 0.001 };
      TransformType::ParametersType plusParameters;
      TransformType::ParametersType minusParameters;

      plusParameters = parameters2;
      minusParameters = parameters2;
      plusParameters[k] += delta;
      minusParameters[k] -= delta;

      TransformType::OutputPointType plusPoint;
      TransformType::OutputPointType minusPoint;

      t4->SetParameters(plusParameters);
      plusPoint = t4->TransformPoint(p1);
      t4->SetParameters(minusParameters);
      minusPoint = t4->TransformPoint(p1);
      for (unsigned int j = 0; j < 2; ++j)
      {
        const double approxDerivative = (plusPoint[j] - minusPoint[j]) / (2.0 * delta);
        const double computedDerivative = jacobian2[j][k];
        approxJacobian[j][k] = approxDerivative;
        EXPECT_LE(itk::Math::Absolute(approxDerivative - computedDerivative), 1e-4)
          << "Error computing Jacobian [" << j << "][" << k << ']' << std::endl
          << "Result should be: " << approxDerivative << std::endl
          << "Reported result is: " << computedDerivative << std::endl
          << " [ FAILED ] ";
      } // for j

    } // for k

    std::cout << " [ PASSED ] " << std::endl;
  }

  {
    // Test Set/Get Matrix and Set/Get Offset
    using TransformType = EulerTransformType;
    auto t1 = TransformType::New();
    auto t23 = TransformType::New();

    TransformType::InputPointType center;
    center[0] = 9.0;
    center[1] = 10.0;

    TransformType::ParametersType parameters3(t1->GetNumberOfParameters());
    for (unsigned int j = 0; j < t1->GetNumberOfParameters(); ++j)
    {
      parameters3[j] = static_cast<double>(j) + 1.0;
    }
    parameters3[0] *= itk::Math::pi / 180.0;

    t1->SetCenter(center);
    t1->SetParameters(parameters3);

    t23->SetCenter(center);
    t23->SetMatrix(t1->GetMatrix());
    t23->SetOffset(t1->GetOffset());

    // check the transformed points are the same
    TransformType::InputPointType ip;
    ip[0] = 8.0;
    ip[1] = 9.0;

    const TransformType::OutputPointType op1 = t1->TransformPoint(ip);
    const TransformType::OutputPointType op2 = t23->TransformPoint(ip);

    std::cout << "Test Set/GetMatrix() and Set/GetOffset(): ";
    EXPECT_TRUE(CheckEqual(op1, op2));

    // check that parameters are the same
    TransformType::ParametersType pdash = t23->GetParameters();

    std::cout << "Test Set/GetMatrix() and Set/GetOffset(): ";
    for (unsigned int j = 0; j < t1->GetNumberOfParameters(); ++j)
    {
      EXPECT_LE(itk::Math::Absolute(parameters3[j] - pdash[j]), epsilon)
        << std::setprecision(static_cast<int>(itk::Math::Absolute(std::log10(epsilon)))) << "Test failed!" << std::endl
        << "Error in parameters at index [" << j << "]" << std::endl
        << "Expected value " << parameters3 << std::endl
        << " differs from " << pdash << " by more than " << epsilon;
    }
    std::cout << " [ PASSED ] " << std::endl;
  }
}
