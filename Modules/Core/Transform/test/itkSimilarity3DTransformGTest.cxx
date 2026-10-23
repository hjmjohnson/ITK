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

/**
 *
 *  This program illustrates the use of Similarity3DTransform
 *
 *  This transform performs: translation, rotation and uniform scaling.
 *
 */

#include "itkSimilarity3DTransform.h"
#include "itkGTest.h"
// -------------------------
//
//   Main code
//
// -------------------------
TEST(Similarity3DTransform, ConvertedLegacyTest)
{

  using ValueType = double;

  constexpr ValueType epsilon{ 1e-12 };

  //  Versor Transform type
  using TransformType = itk::Similarity3DTransform<ValueType>;

  //  Versor type
  using VersorType = TransformType::VersorType;

  //  Vector type
  using VectorType = TransformType::InputVectorType;

  //  Parameters type
  using ParametersType = TransformType::ParametersType;

  //  Jacobian type
  using JacobianType = TransformType::JacobianType;

  //  Rotation Matrix type
  using MatrixType = TransformType::MatrixType;

  {
    std::cout << "Test default constructor... ";

    auto transform = TransformType::New();
    EXPECT_LE(itk::Math::Absolute(transform->GetScale() - 1.0), itk::NumericTraits<TransformType::ScaleType>::min())
      << "Error: Scale: Expected 1.0, got " << transform->GetScale() << " ! ";
    // SetIdentity supposed to reset scale as well.
    transform->SetScale(2.0);
    transform->SetIdentity();
    EXPECT_LE(itk::Math::Absolute(transform->GetScale() - 1.0), itk::NumericTraits<TransformType::ScaleType>::min())
      << "Error: Scale: Expected 1.0 after SetIdentity, got " << transform->GetScale() << " ! ";

    auto axis = itk::MakeFilled<VectorType>(1.5);

    const ValueType angle = 120.0 * std::atan(1.0) / 45.0;

    VersorType versor;
    versor.Set(axis, angle);

    ParametersType parameters(transform->GetNumberOfParameters()); // Number of parameters

    parameters[0] = versor.GetX();
    parameters[1] = versor.GetY();
    parameters[2] = versor.GetZ();
    parameters[3] = 0.0; // Translation
    parameters[4] = 0.0;
    parameters[5] = 0.0;
    parameters[6] = 1.0;

    transform->SetParameters(parameters);

    std::cout << " PASSED !" << std::endl;
  }
  {
    std::cout << "Test initial rotation matrix " << std::endl;
    auto             transform = TransformType::New();
    const MatrixType matrix = transform->GetMatrix();
    std::cout << "Matrix = " << std::endl;
    std::cout << matrix << std::endl;
  }
  /* Create a Rigid 3D transform with rotation */

  {
    bool Ok = true;

    auto rotation = TransformType::New();

    auto axis = itk::MakeFilled<itk::Vector<double, 3>>(1);

    const double angle = (std::atan(1.0) / 45.0) * 120.0; // turn 120 degrees

    // this rotation will permute the axis x->y, y->z, z->x
    rotation->SetRotation(axis, angle);

    TransformType::OffsetType offset = rotation->GetOffset();
    std::cout << "pure Rotation test:  ";
    std::cout << offset << std::endl;
    for (unsigned int i = 0; i < 3; ++i)
    {
      if (itk::Math::Absolute(offset[i] - 0.0) > epsilon)
      {
        Ok = false;
        break;
      }
    }

    EXPECT_TRUE(Ok) << "Get Offset  differs from null in rotation ";

    VersorType versor;
    versor.Set(axis, angle);

    {
      // Rotate an itk::Point
      constexpr TransformType::InputPointType::ValueType pInit[3]{ 1, 4, 9 };
      const TransformType::InputPointType                p = pInit;
      const TransformType::OutputPointType               q = versor.Transform(p);

      const TransformType::OutputPointType r = rotation->TransformPoint(p);
      for (unsigned int i = 0; i < 3; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error rotating point : " << p << std::endl
                      << "Result should be     : " << q << std::endl
                      << "Reported Result is   : " << r;

      std::cout << "Ok rotating an itk::Point " << std::endl;
    }

    {
      // Translate an itk::Vector
      TransformType::InputVectorType::ValueType pInit[3] = { 1, 4, 9 };
      const TransformType::InputVectorType      p = pInit;
      const TransformType::OutputVectorType     q = versor.Transform(p);

      const TransformType::OutputVectorType r = rotation->TransformVector(p);
      for (unsigned int i = 0; i < 3; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error rotating vector : " << p << std::endl
                      << "Result should be      : " << q << std::endl
                      << "Reported Result is    : " << r;

      std::cout << "Ok rotating an itk::Vector " << std::endl;
    }
    {
      // Translate an itk::CovariantVector
      TransformType::InputCovariantVectorType::ValueType pInit[3] = { 1, 4, 9 };
      const TransformType::InputCovariantVectorType      p = pInit;
      const TransformType::OutputCovariantVectorType     q = versor.Transform(p);

      const TransformType::OutputCovariantVectorType r = rotation->TransformCovariantVector(p);
      for (unsigned int i = 0; i < 3; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error rotating covariant vector : " << p << std::endl
                      << "Result should be                : " << q << std::endl
                      << "Reported Result is              : " << r;

      std::cout << "Ok rotating an itk::CovariantVector " << std::endl;
    }

    {
      // Translate a vnl_vector
      TransformType::InputVnlVectorType p;
      p[0] = 1;
      p[1] = 4;
      p[2] = 9;

      const TransformType::OutputVnlVectorType q = versor.Transform(p);

      const TransformType::OutputVnlVectorType r = rotation->TransformVector(p);
      for (unsigned int i = 0; i < 3; ++i)
      {
        if (itk::Math::Absolute(q[i] - r[i]) > epsilon)
        {
          Ok = false;
          break;
        }
      }
      EXPECT_TRUE(Ok) << "Error rotating vnl_vector : " << p << std::endl
                      << "Result should be          : " << q << std::endl
                      << "Reported Result is        : " << r;

      std::cout << "Ok rotating an vnl_Vector " << std::endl;
    }
  }
  /**  Exercise the SetCenter method  */
  {
    bool Ok = true;

    auto transform = TransformType::New();

    auto axis = itk::MakeFilled<itk::Vector<double, 3>>(1);

    const double angle = (std::atan(1.0) / 45.0) * 30.0; // turn 30 degrees

    transform->SetRotation(axis, angle);

    TransformType::InputPointType center;
    center[0] = 31;
    center[1] = 62;
    center[2] = 93;

    transform->SetCenter(center);

    const TransformType::OutputPointType transformedPoint = transform->TransformPoint(center);
    for (unsigned int i = 0; i < 3; ++i)
    {
      if (itk::Math::Absolute(center[i] - transformedPoint[i]) > epsilon)
      {
        Ok = false;
        break;
      }
    }

    EXPECT_TRUE(Ok) << "The center point was not invariant to rotation ";

    std::cout << "Ok center is invariant to rotation." << std::endl;


    const unsigned int np = transform->GetNumberOfParameters();

    ParametersType parameters(np); // Number of parameters

    constexpr VersorType versor;

    parameters[0] = versor.GetX(); // Rotation axis * sin(t/2)
    parameters[1] = versor.GetY();
    parameters[2] = versor.GetZ();
    parameters[3] = 8.0; // Translation
    parameters[4] = 7.0;
    parameters[5] = 6.0;
    parameters[6] = 10.0; // Scale

    transform->SetParameters(parameters);

    ParametersType parameters2 = transform->GetParameters();

    constexpr double tolerance{ 1e-8 };
    for (unsigned int p = 0; p < np; ++p)
    {
      EXPECT_LE(itk::Math::Absolute(parameters[p] - parameters2[p]), tolerance)
        << "Output parameter does not match input ";
    }
    std::cout << "Input/Output parameter check Passed !" << std::endl;

    // Try the ComputeJacobianWithRespectToParameters method
    TransformType::InputPointType aPoint;
    aPoint[0] = 10.0;
    aPoint[1] = 20.0;
    aPoint[2] = -10.0;
    JacobianType jacobian;
    transform->ComputeJacobianWithRespectToParameters(aPoint, jacobian);
    std::cout << "Jacobian: " << std::endl;
    std::cout << jacobian << std::endl;

    // copy the read one just for getting the right matrix size
    JacobianType TheoreticalJacobian = jacobian;

    TheoreticalJacobian[0][0] = 0.0;
    TheoreticalJacobian[1][0] = 2060.0;
    TheoreticalJacobian[2][0] = -840.0;

    TheoreticalJacobian[0][1] = -2060.0;
    TheoreticalJacobian[1][1] = 0.0;
    TheoreticalJacobian[2][1] = 420.0;

    TheoreticalJacobian[0][2] = 840.0;
    TheoreticalJacobian[1][2] = -420.0;
    TheoreticalJacobian[2][2] = 0.0;

    TheoreticalJacobian[0][3] = 1.0;
    TheoreticalJacobian[1][3] = 0.0;
    TheoreticalJacobian[2][3] = 0.0;

    TheoreticalJacobian[0][4] = 0.0;
    TheoreticalJacobian[1][4] = 1.0;
    TheoreticalJacobian[2][4] = 0.0;

    TheoreticalJacobian[0][5] = 0.0;
    TheoreticalJacobian[1][5] = 0.0;
    TheoreticalJacobian[2][5] = 1.0;

    TheoreticalJacobian[0][6] = -21.0;
    TheoreticalJacobian[1][6] = -42.0;
    TheoreticalJacobian[2][6] = -103.0;
    for (unsigned int ii = 0; ii < 3; ++ii)
    {
      for (unsigned int jj = 0; jj < 7; ++jj)
      {
        EXPECT_LE(itk::Math::Absolute(TheoreticalJacobian[ii][jj] - jacobian[ii][jj]), 1e-5)
          << "Jacobian components differ from expected values " << std::endl
          << std::endl
          << "Expected Jacobian = " << std::endl
          << TheoreticalJacobian << std::endl
          << std::endl
          << "Computed Jacobian = " << std::endl
          << jacobian << std::endl
          << std::endl
          << std::endl
          << "Test FAILED ! ";
      }
    }
  }

  {
    std::cout << " Exercise the SetIdentity() method " << std::endl;
    auto transform = TransformType::New();

    auto axis = itk::MakeFilled<itk::Vector<double, 3>>(1);

    const double angle = (std::atan(1.0) / 45.0) * 30.0; // turn 30 degrees

    transform->SetRotation(axis, angle);

    TransformType::InputPointType center;
    center[0] = 31;
    center[1] = 62;
    center[2] = 93;

    transform->SetCenter(center);

    transform->SetIdentity();

    const unsigned int np = transform->GetNumberOfParameters();

    ParametersType parameters(np); // Number of parameters

    constexpr VersorType versor;

    parameters[0] = versor.GetX(); // Rotation axis * sin(t/2)
    parameters[1] = versor.GetY();
    parameters[2] = versor.GetZ();
    parameters[3] = 0.0; // Translation
    parameters[4] = 0.0;
    parameters[5] = 0.0;
    parameters[6] = 1.0;

    ParametersType parameters2 = transform->GetParameters();

    constexpr double tolerance{ 1e-8 };
    for (unsigned int p = 0; p < np; ++p)
    {
      EXPECT_LE(itk::Math::Absolute(parameters[p] - parameters2[p]), tolerance)
        << "Output parameter does not match input ";
    }
    std::cout << "Input/Output parameter check Passed !" << std::endl;
  }

  {
    std::cout << " Exercise the Scaling methods " << std::endl;
    auto transform = TransformType::New();

    auto axis = itk::MakeFilled<itk::Vector<double, 3>>(1);

    const double angle = (std::atan(1.0) / 45.0) * 30.0; // turn 30 degrees

    transform->SetRotation(axis, angle);

    TransformType::InputPointType center;
    center[0] = 31;
    center[1] = 62;
    center[2] = 93;

    transform->SetCenter(center);

    TransformType::OutputVectorType translation;
    translation[0] = 17;
    translation[1] = 19;
    translation[2] = 23;

    transform->SetTranslation(translation);

    constexpr double scale{ 2.5 };

    transform->SetScale(scale);

    const double rscale = transform->GetScale();

    constexpr double tolerance{ 1e-8 };

    EXPECT_LE(itk::Math::Absolute(rscale - scale), tolerance) << "Error in Set/Get Scale() ";

    const unsigned int np = transform->GetNumberOfParameters();

    ParametersType parameters(np); // Number of parameters

    VersorType versor;
    versor.Set(axis, angle);

    parameters[0] = versor.GetX(); // Rotation axis * sin(t/2)
    parameters[1] = versor.GetY();
    parameters[2] = versor.GetZ();
    parameters[3] = translation[0];
    parameters[4] = translation[1];
    parameters[5] = translation[2];
    parameters[6] = scale;

    ParametersType parameters2 = transform->GetParameters();
    for (unsigned int p = 0; p < np; ++p)
    {
      EXPECT_LE(itk::Math::Absolute(parameters[p] - parameters2[p]), tolerance)
        << "Output parameter does not match input ";
    }
    std::cout << "Input/Output parameter check Passed !" << std::endl;
  }
  {
    // Testing SetMatrix()
    std::cout << "Testing SetMatrix() ... ";
    MatrixType matrix;

    auto t = TransformType::New();

    // attempt to set an non-orthogonal matrix
    unsigned int par = 0;
    for (unsigned int row = 0; row < 3; ++row)
    {
      for (unsigned int col = 0; col < 3; ++col)
      {
        matrix[row][col] = static_cast<double>(par + 1);
        ++par;
      }
    }

    std::cout << "Setting non-orthogonal matrix = " << std::endl;
    std::cout << matrix << std::endl;

    EXPECT_THROW(t->SetMatrix(matrix), itk::ExceptionObject);

    t = TransformType::New();

    // attempt to set an (orthogonal + scale) matrix
    matrix.GetVnlMatrix().set_identity();

    constexpr double a{ 1.0 / 180.0 * itk::Math::pi };
    constexpr double s{ 0.5 };
    matrix[0][0] = std::cos(a) * s;
    matrix[0][1] = -1.0 * std::sin(a) * s;
    matrix[1][0] = std::sin(a) * s;
    matrix[1][1] = std::cos(a) * s;
    matrix[2][2] = s;

    EXPECT_NO_THROW(t->SetMatrix(matrix)) << "Error: caught unexpected exception";

    // Check the computed parameters
    TransformType::InputPointType center;
    center[0] = 15.0;
    center[1] = 16.0;
    center[2] = 17.0;

    ParametersType e(t->GetNumberOfParameters(), 0.0);
    e[2] = std::sin(0.5 * a);
    e[6] = 0.5;

    t = TransformType::New();
    t->SetCenter(center);
    t->SetParameters(e);

    auto t2 = TransformType::New();
    t2->SetCenter(center);
    t2->SetMatrix(t->GetMatrix());

    ParametersType p = t2->GetParameters();
    for (unsigned int k = 0; k < e.GetSize(); ++k)
    {
      EXPECT_LE(itk::Math::Absolute(e[k] - p[k]), epsilon) << " [ FAILED ] " << std::endl
                                                           << "Expected parameters: " << e << std::endl
                                                           << "but got: " << p;
    }

    std::cout << "[ PASSED ]" << std::endl;
  }

  std::cout << std::endl << "Test PASSED ! " << std::endl;
}
