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
#include "itkDistanceToCentroidMembershipFunction.h"
#include "itkGTest.h"

TEST(DistanceToCentroidMembershipFunction, ConvertedLegacyTest)
{

  constexpr unsigned int MeasurementVectorSize{ 3 };

  using MeasurementVectorType = itk::FixedArray<float, MeasurementVectorSize>;

  using MembershipFunctionType = itk::Statistics::DistanceToCentroidMembershipFunction<MeasurementVectorType>;

  auto function = MembershipFunctionType::New();

  std::cout << function->GetNameOfClass() << std::endl;


  // set the distance metric type
  using DistanceMetricType = itk::Statistics::EuclideanDistanceMetric<MeasurementVectorType>;
  using MeasurementVectorSizeType = DistanceMetricType::MeasurementVectorSizeType;

  auto distanceMetric = DistanceMetricType::New();
  function->SetDistanceMetric(distanceMetric);

  EXPECT_EQ(function->GetDistanceMetric(), distanceMetric) << "Error in GetDistanceMetric() ";

  function->Print(std::cout);

  function->SetMeasurementVectorSize(MeasurementVectorSize); // for code coverage

  EXPECT_EQ(function->GetMeasurementVectorSize(), MeasurementVectorSize) << "GetMeasurementVectorSize() Failed !";

  // Test if an exception will be thrown if we try to resize the measurement vector
  // size
  {
    constexpr MeasurementVectorSizeType measurementVector2{ MeasurementVectorSize + 1 };
    EXPECT_THROW(function->SetMeasurementVectorSize(measurementVector2), itk::ExceptionObject)
      << "Exception should have been thrown since we are trying to resize non-resizeable measurement vector type ";
  }


  // Test if the distance computed is correct
  MembershipFunctionType::CentroidType origin;
  itk::NumericTraits<MembershipFunctionType::CentroidType>::SetLength(origin, 3);
  origin[0] = 1.5;
  origin[1] = 2.3;
  origin[2] = 1.0;
  function->SetCentroid(origin);

  constexpr double tolerance{ 0.001 };

  EXPECT_NEAR(function->GetCentroid()[0], origin[0], tolerance) << "Error in GetCentroid() method";
  EXPECT_NEAR(function->GetCentroid()[1], origin[1], tolerance) << "Error in GetCentroid() method";
  EXPECT_NEAR(function->GetCentroid()[2], origin[2], tolerance) << "Error in GetCentroid() method";

  MeasurementVectorType measurement;
  itk::NumericTraits<MeasurementVectorType>::SetLength(measurement, 3);
  measurement[0] = 2.5;
  measurement[1] = 3.3;
  measurement[2] = 4.0;

  constexpr double trueValue{ 3.31662 };
  const double     distanceComputed = function->Evaluate(measurement);

  EXPECT_NEAR(distanceComputed, trueValue, tolerance) << "Distance computed not correct";

  // Exercise the Clone method.
  const MembershipFunctionType::Pointer clonedFunction = function->Clone();
  EXPECT_FALSE(clonedFunction.IsNull());
}
