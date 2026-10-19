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
#include "itkGaussianMembershipFunction.h"
#include "itkGTest.h"

TEST(GaussianMembershipFunction, ConvertedLegacyTest)
{
  constexpr unsigned int MeasurementVectorSize{ 1 };

  using MeasurementVectorType = itk::FixedArray<float, MeasurementVectorSize>;

  using MembershipFunctionType = itk::Statistics::GaussianMembershipFunction<MeasurementVectorType>;
  using MeasurementVectorSizeType = MembershipFunctionType::MeasurementVectorSizeType;

  auto function = MembershipFunctionType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(function, GaussianMembershipFunction, MembershipFunctionBase);


  // Test if an exception will be thrown if we try to resize the measurement vector
  // size
  constexpr MeasurementVectorSizeType measurementVector2{ MeasurementVectorSize + 1 };
  EXPECT_THROW(function->SetMeasurementVectorSize(measurementVector2), itk::ExceptionObject);

  // Test non-square covariance matrix exception
  MembershipFunctionType::CovarianceMatrixType covariance;
  covariance.SetSize(MeasurementVectorSize, MeasurementVectorSize + 1);
  covariance.SetIdentity();
  EXPECT_THROW(function->SetCovariance(covariance), itk::ExceptionObject);

  // Test covariance matrix and measurement vector size mismatch exception
  covariance.SetSize(MeasurementVectorSize + 1, MeasurementVectorSize + 1);
  covariance.SetIdentity();
  EXPECT_THROW(function->SetCovariance(covariance), itk::ExceptionObject);

  covariance.SetSize(MeasurementVectorSize, MeasurementVectorSize);
  covariance.SetIdentity();
  function->SetCovariance(covariance);
  EXPECT_EQ(covariance, function->GetCovariance());

  EXPECT_EQ(covariance.GetInverse(), function->GetInverseCovariance().GetVnlMatrix());

  function->SetMeasurementVectorSize(MeasurementVectorSize);
  EXPECT_EQ(MeasurementVectorSize, function->GetMeasurementVectorSize());

  // Test if the membership function value computed is correct
  MembershipFunctionType::MeanVectorType mean;
  itk::NumericTraits<MembershipFunctionType::MeanVectorType>::SetLength(mean, MeasurementVectorSize);
  mean[0] = 1.5;
  function->SetMean(mean);

  constexpr double tolerance{ 0.001 };

  EXPECT_NEAR(function->GetMean()[0], mean[0], tolerance) << "Error in GetMean() method";

  MeasurementVectorType measurement;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurement, MeasurementVectorSize);
  measurement[0] = 1.5;

  constexpr double trueValue{ 0.3989 };
  const double     distanceComputed = function->Evaluate(measurement);

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";

  // -----------------------------------------------------------------
  // Reject non-positive-definite covariance matrices.
  //
  // The previous implementation tested `inv_cov.determinant_magnitude()
  // < 0` which can never trigger because determinant_magnitude() returns
  // the product of singular values (always non-negative).  The fix uses
  // vnl_determinant on the original covariance and rejects det <= 0,
  // which catches both singular and non-positive-definite cases.
  // -----------------------------------------------------------------
  using NPDMVType = itk::FixedArray<float, 2>;
  using NPDMembershipFunctionType = itk::Statistics::GaussianMembershipFunction<NPDMVType>;
  auto npdFunction = NPDMembershipFunctionType::New();
  npdFunction->SetMeasurementVectorSize(2);

  // Singular: rank 1, det = 0
  NPDMembershipFunctionType::CovarianceMatrixType singular;
  singular.SetSize(2, 2);
  singular(0, 0) = 1.0;
  singular(0, 1) = 1.0;
  singular(1, 0) = 1.0;
  singular(1, 1) = 1.0;
  EXPECT_THROW(npdFunction->SetCovariance(singular), itk::ExceptionObject);

  // Indefinite (not symmetric positive-definite): det = -3
  NPDMembershipFunctionType::CovarianceMatrixType nonPosDef;
  nonPosDef.SetSize(2, 2);
  nonPosDef(0, 0) = 1.0;
  nonPosDef(0, 1) = 2.0;
  nonPosDef(1, 0) = 2.0;
  nonPosDef(1, 1) = 1.0;
  EXPECT_THROW(npdFunction->SetCovariance(nonPosDef), itk::ExceptionObject);

  // Well-formed: det = 3.75 (positive definite)
  NPDMembershipFunctionType::CovarianceMatrixType posDef;
  posDef.SetSize(2, 2);
  posDef(0, 0) = 2.0;
  posDef(0, 1) = 0.5;
  posDef(1, 0) = 0.5;
  posDef(1, 1) = 2.0;
  EXPECT_NO_THROW(npdFunction->SetCovariance(posDef));
}
