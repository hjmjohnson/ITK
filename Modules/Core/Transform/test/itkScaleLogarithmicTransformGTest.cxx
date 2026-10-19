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

#include "itkScaleLogarithmicTransform.h"
#include "itkGTest.h"

#include <cmath>
#include <iostream>

TEST(ScaleLogarithmicTransform, ConvertedLegacyTest)
{
  using TransformType = itk::ScaleLogarithmicTransform<double>;

  constexpr double       epsilon{ 1e-10 };
  constexpr unsigned int N{ 3 };

  bool testStatus = true;


  auto scaleLogTransform = TransformType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(scaleLogTransform, ScaleLogarithmicTransform, ScaleTransform);


  /* Create a 3D identity transformation and show its parameters */
  {
    auto                     identityTransform = TransformType::New();
    TransformType::ScaleType scale = identityTransform->GetScale();
    std::cout << "Scale from instantiating an identity transform:  ";
    for (unsigned int j = 0; j < N; ++j)
    {
      std::cout << scale[j] << ' ';
    }
    std::cout << std::endl;
    for (unsigned int i = 0; i < N; ++i)
    {
      if (itk::Math::Absolute(scale[i] - 1.0) > epsilon)
      {
        testStatus = false;
        break;
      }
    }
    EXPECT_TRUE(testStatus) << "Identity doesn't have a unit scale ";
  }

  /* Create a Scale transform */
  {
    auto scaleTransform = TransformType::New();

    TransformType::ScaleType::ValueType iscaleInit[3] = { 1, 4, 9 };
    TransformType::ScaleType            iscale = iscaleInit;

    scaleTransform->SetScale(iscale);

    TransformType::ScaleType scale = scaleTransform->GetScale();
    std::cout << "scale initialization  test:  ";
    for (unsigned int j = 0; j < N; ++j)
    {
      std::cout << scale[j] << ' ';
    }
    std::cout << std::endl;

    for (unsigned int i = 0; i < N; ++i)
    {
      if (itk::Math::Absolute(scale[i] - iscale[i]) > epsilon)
      {
        testStatus = false;
        break;
      }
    }
    EXPECT_TRUE(testStatus) << "GetScale  differs from SetScale value ";

    {
      // scale an itk::Point
      constexpr TransformType::InputPointType::ValueType pInit[3]{ 10, 10, 10 };
      TransformType::InputPointType                      p = pInit;
      TransformType::InputPointType                      q;
      for (unsigned int j = 0; j < N; ++j)
      {
        q[j] = p[j] * iscale[j];
      }
      TransformType::OutputPointType r = scaleTransform->TransformPoint(p);
      for (unsigned int i = 0; i < N; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          testStatus = false;
          break;
        }
      }
      EXPECT_TRUE(testStatus) << "Error scaling point : " << p << std::endl
                              << "Result should be    : " << q << std::endl
                              << "Reported Result is  : " << r;

      std::cout << "Successful scaling an itk::Point " << std::endl;
    }

    {
      // Scale an itk::Vector
      TransformType::InputVectorType::ValueType pInit[3] = { 10, 10, 10 };
      TransformType::InputVectorType            p = pInit;
      TransformType::OutputVectorType           q;
      for (unsigned int j = 0; j < N; ++j)
      {
        q[j] = p[j] * iscale[j];
      }
      TransformType::OutputVectorType r = scaleTransform->TransformVector(p);
      for (unsigned int i = 0; i < N; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          testStatus = false;
          break;
        }
      }
      EXPECT_TRUE(testStatus) << "Error scaling vector: " << p << std::endl << "Reported Result is      : " << q;

      std::cout << "Successful scaling an itk::Vector " << std::endl;
    }

    {
      // Scale an itk::CovariantVector
      TransformType::InputCovariantVectorType::ValueType pInit[3] = { 10, 10, 10 };
      TransformType::InputCovariantVectorType            p = pInit;
      TransformType::OutputCovariantVectorType           q;
      for (unsigned int j = 0; j < N; ++j)
      {
        q[j] = p[j] / iscale[j];
      }
      TransformType::OutputCovariantVectorType r = scaleTransform->TransformCovariantVector(p);
      for (unsigned int i = 0; i < N; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          testStatus = false;
          break;
        }
      }
      EXPECT_TRUE(testStatus) << "Error scaling covariant vector: " << p << std::endl
                              << "Reported Result is      : " << q;

      std::cout << "Successful scaling an itk::CovariantVector " << std::endl;
    }

    {
      // Scale a vnl_vector
      TransformType::InputVnlVectorType p;
      p[0] = 11;
      p[1] = 7;
      p[2] = 15;
      TransformType::OutputVnlVectorType q;
      for (unsigned int j = 0; j < N; ++j)
      {
        q[j] = p[j] * iscale[j];
      }
      TransformType::OutputVnlVectorType r = scaleTransform->TransformVector(p);
      for (unsigned int i = 0; i < N; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          testStatus = false;
          break;
        }
      }
      EXPECT_TRUE(testStatus) << "Error scaling vnl_vector: " << p << std::endl << "Reported Result is      : " << q;

      std::cout << "Successful scaling an vnl_Vector " << std::endl;
    }


    // Exercise Set/Get Center methods
    {
      using CenterType = TransformType::InputPointType;
      CenterType center;
      center[0] = 5;
      center[1] = 6;
      center[2] = 7;

      scaleTransform->SetCenter(center);

      const CenterType c2 = scaleTransform->GetCenter();
      EXPECT_LE(c2.EuclideanDistanceTo(center), 1e-5) << "Error in Set/Get center." << std::endl
                                                      << "It was SetCenter() to    : " << center << std::endl
                                                      << "but GetCenter() returned : " << c2;

      std::cout << "Successful SetCenter() / GetCenter() " << std::endl;
    }


    // Exercise Set/Get parameters
    {
      using ParametersType = TransformType::ParametersType;

      ParametersType parameters = scaleTransform->GetParameters();
      parameters[0] = 0.0; // log(1);
      parameters[1] = 0.0; // log(1);
      parameters[2] = 0.0; // log(1);
      scaleTransform->SetParameters(parameters);

      ParametersType p2 = scaleTransform->GetParameters();

      testStatus = true;
      for (unsigned int i = 0; i < N; ++i)
      {
        if (itk::Math::Absolute(p2[i] - parameters[i]) > 1e-5)
        {
          testStatus = false;
          break;
        }
      }
      EXPECT_TRUE(testStatus) << "Error in Set/Get parameters." << std::endl
                              << "It was SetParameters() to    : " << parameters << std::endl
                              << "but GetParameters() returned : " << p2;

      std::cout << "Successful SetParameters() / GetParameters() " << std::endl;
    }
  }


  // Exercise the Jacobian about a non-zero center
  {
    auto centeredTransform = TransformType::New();

    TransformType::InputPointType center;
    center[0] = 5;
    center[1] = 6;
    center[2] = 7;
    centeredTransform->SetCenter(center);

    TransformType::ParametersType parameters = centeredTransform->GetParameters();
    parameters[0] = std::log(2.0);
    parameters[1] = std::log(3.0);
    parameters[2] = std::log(4.0);
    centeredTransform->SetParameters(parameters);

    constexpr TransformType::InputPointType::ValueType pInit[3]{ 10, 10, 10 };
    const TransformType::InputPointType                p = pInit;

    TransformType::JacobianType jacobian;
    centeredTransform->ComputeJacobianWithRespectToParameters(p, jacobian);

    const TransformType::ScaleType & scales = centeredTransform->GetScale();

    testStatus = true;
    for (unsigned int i = 0; i < N; ++i)
    {
      // d/dLog(scale[i]) of scale[i] * (p[i] - center[i]) + center[i]
      const double expected = scales[i] * (p[i] - center[i]);
      if (itk::Math::Absolute(jacobian(i, i) - expected) > epsilon)
      {
        testStatus = false;
        break;
      }
    }
    EXPECT_TRUE(testStatus) << "Error in ComputeJacobianWithRespectToParameters()." << std::endl
                            << "The center of the transformation was ignored." << std::endl
                            << "Jacobian: " << jacobian;

    std::cout << "Successful ComputeJacobianWithRespectToParameters() " << std::endl;
  }


  std::cout << "Test finished" << std::endl;
}
