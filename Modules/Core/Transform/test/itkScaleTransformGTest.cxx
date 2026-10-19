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

#include "itkScaleTransform.h"
#include "itkGTest.h"


TEST(ScaleTransform, ConvertedLegacyTest)
{


  using TransformType = itk::ScaleTransform<double>;


  constexpr double       epsilon{ 1e-10 };
  constexpr unsigned int N{ 3 };


  bool Ok = true;


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
        Ok = false;
        break;
      }
    }

    // Set a non-identity value to the transform and then set it to the identity
    scale = 2.0;
    identityTransform->SetScale(scale);
    EXPECT_EQ(scale, identityTransform->GetScale());

    identityTransform->SetIdentity();

    TransformType::ScaleType identityScale{ 1.0 };
    EXPECT_EQ(identityScale, identityTransform->GetScale());

    EXPECT_TRUE(Ok) << "Identity doesn't have a unit scale ";
  }

  /* Create a Scale transform */
  {
    auto scaleTransform = TransformType::New();

    TransformType::ScaleType::ValueType iscaleInit[3] = { 1, 4, 9 };
    TransformType::ScaleType            iscale = iscaleInit;

    scaleTransform->SetScale(iscale);
    EXPECT_EQ(scaleTransform->GetFixedParameters().Size(), 3u)
      << "ScaleTransform has 3 fixed parameters, yet GetFixedParameters.Size() reports: "
      << scaleTransform->GetFixedParameters().Size();
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
        Ok = false;
        break;
      }
    }
    EXPECT_TRUE(Ok) << "GetScale  differs from SetScale value ";

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
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error scaling point : " << p << std::endl
                      << "Result should be    : " << q << std::endl
                      << "Reported Result is  : " << r;

      std::cout << "Ok scaling an itk::Point " << std::endl;
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
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error scaling vector: " << p << std::endl << "Reported Result is      : " << q;

      std::cout << "Ok scaling an itk::Vector " << std::endl;
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
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error scaling covariant vector: " << p << std::endl << "Reported Result is      : " << q;

      std::cout << "Ok scaling an itk::CovariantVector " << std::endl;
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
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error scaling vnl_vector: " << p << std::endl << "Reported Result is      : " << q;

      std::cout << "Ok scaling an vnl_Vector " << std::endl;
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

      std::cout << "Ok SetCenter() / GetCenter() " << std::endl;
    }
  }
}
