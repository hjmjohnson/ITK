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

#include "itkMahalanobisDistanceMetric.h"
#include "itkGTest.h"

TEST(MahalanobisDistanceMetric, ConvertedLegacyTest)
{
  constexpr unsigned int MeasurementVectorSize{ 3 };

  using MeasurementVectorType = itk::Array<float>;

  using DistanceMetricType = itk::Statistics::MahalanobisDistanceMetric<MeasurementVectorType>;

  auto distance = DistanceMetricType::New();

  std::cout << distance->GetNameOfClass() << std::endl;

  distance->Print(std::cout);

  distance->SetMeasurementVectorSize(MeasurementVectorSize);

  EXPECT_EQ(distance->GetMeasurementVectorSize(), MeasurementVectorSize) << "GetMeasurementVectorSize() Failed !";

  // Test if the distance computed is correct
  DistanceMetricType::OriginType origin;
  itk::NumericTraits<DistanceMetricType::OriginType>::SetLength(origin, 3);
  origin[0] = 1.5;
  origin[1] = 2.3;
  origin[2] = 1.0;
  distance->SetMean(origin);

  // double value comparison tolerance
  constexpr double tolerance{ 0.001 };
  EXPECT_NEAR(distance->GetMean()[0], origin[0], tolerance) << "Set/Get Origin error";
  EXPECT_NEAR(distance->GetMean()[1], origin[1], tolerance) << "Set/Get Origin error";
  EXPECT_NEAR(distance->GetMean()[2], origin[2], tolerance) << "Set/Get Origin error";

  MeasurementVectorType measurement;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurement, 3);
  measurement[0] = 2.5;
  measurement[1] = 3.3;
  measurement[2] = 4.0;

  double trueValue = 3.31662;
  double distanceComputed = distance->Evaluate(measurement);

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";

  // Test if we get the same result with identity covariance matrix set
  DistanceMetricType::CovarianceMatrixType covarianceMatrix;
  covarianceMatrix.set_size(MeasurementVectorSize, MeasurementVectorSize);
  covarianceMatrix.set_identity();
  distance->SetCovariance(covarianceMatrix);

  EXPECT_EQ(distance->GetCovariance(), covarianceMatrix) << "Get/SetCovariance method error";

  constexpr double epsilon{ 1e-200 };
  constexpr double doubleMax{ 1e+25 };

  distance->SetEpsilon(epsilon);
  distance->SetDoubleMax(doubleMax);

  // Test Set/Get Epsilon method
  EXPECT_NEAR(distance->GetEpsilon(), epsilon, tolerance) << "Get/SetEpsilon method error";

  // Test Set/Get DoubleMax method
  EXPECT_NEAR(distance->GetDoubleMax(), doubleMax, tolerance) << "Get/SetDoubleMax method error";

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";


  // Test if an exception is thrown if a covariance matrix is set with different
  // size
  DistanceMetricType::CovarianceMatrixType                covarianceMatrix2;
  constexpr DistanceMetricType::MeasurementVectorSizeType measurementSize2{ 4 };
  covarianceMatrix2.set_size(measurementSize2, measurementSize2);

  EXPECT_THROW(distance->SetCovariance(covarianceMatrix2), itk::ExceptionObject) << "Exception should have been thrown";

  // Set a covariance matrix and check if the computed inverse matrix is
  // correct
  //
  DistanceMetricType::CovarianceMatrixType covarianceMatrix3;
  covarianceMatrix3.set_size(MeasurementVectorSize, MeasurementVectorSize);
  covarianceMatrix3[0][0] = 2.0;
  covarianceMatrix3[0][1] = 1.4;
  covarianceMatrix3[0][2] = 5.0;

  covarianceMatrix3[1][0] = 3.0;
  covarianceMatrix3[1][1] = 2.0;
  covarianceMatrix3[1][2] = 5.4;

  covarianceMatrix3[2][0] = 3.2;
  covarianceMatrix3[2][1] = 1.4;
  covarianceMatrix3[2][2] = 7.4;

  distance->SetCovariance(covarianceMatrix3);

  // establish the true inverse covariance matrix
  DistanceMetricType::CovarianceMatrixType trueInverseCovarianceMatrix;
  trueInverseCovarianceMatrix.set_size(MeasurementVectorSize, MeasurementVectorSize);

  trueInverseCovarianceMatrix[0][0] = -2.124;
  trueInverseCovarianceMatrix[0][1] = 0.986;
  trueInverseCovarianceMatrix[0][2] = 0.716;

  trueInverseCovarianceMatrix[1][0] = 1.444;
  trueInverseCovarianceMatrix[1][1] = 0.352;
  trueInverseCovarianceMatrix[1][2] = -1.232;

  trueInverseCovarianceMatrix[2][0] = 0.646;
  trueInverseCovarianceMatrix[2][1] = -0.493;
  trueInverseCovarianceMatrix[2][2] = 0.059;

  // Get the computed inverse covariance matrix
  DistanceMetricType::CovarianceMatrixType computedInverseCovarianceMatrix = distance->GetInverseCovariance();

  EXPECT_NEAR(trueInverseCovarianceMatrix[0][0], computedInverseCovarianceMatrix[0][0], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[0][1], computedInverseCovarianceMatrix[0][1], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[0][2], computedInverseCovarianceMatrix[0][2], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[1][0], computedInverseCovarianceMatrix[1][0], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[1][1], computedInverseCovarianceMatrix[1][1], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[1][2], computedInverseCovarianceMatrix[1][2], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[2][0], computedInverseCovarianceMatrix[2][0], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[2][1], computedInverseCovarianceMatrix[2][1], tolerance)
    << "Inverse computation error";
  EXPECT_NEAR(trueInverseCovarianceMatrix[2][2], computedInverseCovarianceMatrix[2][2], tolerance)
    << "Inverse computation error";

  // Run the distance metric with a single component measurement vector size
  constexpr DistanceMetricType::MeasurementVectorSizeType singleComponentMeasurementVectorSize{ 1 };

  distance->SetMeasurementVectorSize(singleComponentMeasurementVectorSize);

  itk::NumericTraits<DistanceMetricType::OriginType>::SetLength(origin, 1);
  origin[0] = 1.5;
  distance->SetMean(origin);

  EXPECT_NEAR(distance->GetMean()[0], origin[0], tolerance) << "Set/Get Origin error";
  covarianceMatrix.set_size(singleComponentMeasurementVectorSize, singleComponentMeasurementVectorSize);
  covarianceMatrix[0][0] = 1.0;
  distance->SetCovariance(covarianceMatrix);

  MeasurementVectorType measurementSingleComponent;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurementSingleComponent, 1);
  measurementSingleComponent[0] = 2.5;

  trueValue = 1.0;
  distanceComputed = distance->Evaluate(measurementSingleComponent);

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";

  // Compute distance between two measurement vectors
  MeasurementVectorType measurementSingleComponent2;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurementSingleComponent2, 1);
  measurementSingleComponent2[0] = 1.5;

  trueValue = 1.0;
  distanceComputed = distance->Evaluate(measurementSingleComponent, measurementSingleComponent2);

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";

  // Attempt to compute distance between two unequal size measurement vectors
  MeasurementVectorType measurementSingleComponent3;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurementSingleComponent3, 2);
  measurementSingleComponent3[0] = 1.5;
  measurementSingleComponent3[1] = 2.5;

  distance->Evaluate(measurementSingleComponent, measurementSingleComponent2);

  EXPECT_THROW(distance->Evaluate(measurementSingleComponent, measurementSingleComponent3), itk::ExceptionObject)
    << "Attempting to compute distance between unequal size measurement vectors. Exception should have been thrown";
}
