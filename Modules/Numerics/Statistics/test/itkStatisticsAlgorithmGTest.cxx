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

#include "itkListSample.h"
#include "itkStatisticsAlgorithm.h"
#include "itkGTest.h"

TEST(StatisticsAlgorithm, ConvertedLegacyTest)
{
  std::cout << "StatisticsAlgorithm Test \n \n";

  constexpr unsigned int measurementVectorSize{ 2 };

  using MeasurementVectorType = itk::Array<float>;
  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  auto sample = SampleType::New();

  SampleType::MeasurementVectorType lower(measurementVectorSize);
  SampleType::MeasurementVectorType upper(measurementVectorSize);

  const SampleType * constSample = sample.GetPointer();

  // Testing the exception throwing for samples of measurement size = 0
  sample->SetMeasurementVectorSize(0);

  EXPECT_THROW(
    itk::Statistics::Algorithm::FindSampleBound(constSample, constSample->Begin(), constSample->End(), lower, upper),
    itk::ExceptionObject);

  // Now set the correct measurement vector size
  sample->SetMeasurementVectorSize(measurementVectorSize);

  // Testing the equivalent of an empty sample by passing
  // the Begin() iterator in lieu of the End() iterator.

  EXPECT_THROW(
    itk::Statistics::Algorithm::FindSampleBound(constSample, constSample->Begin(), constSample->Begin(), lower, upper),
    itk::ExceptionObject);

  MeasurementVectorType measure(measurementVectorSize);
  MeasurementVectorType realUpper(measurementVectorSize);
  MeasurementVectorType realLower(measurementVectorSize);

  constexpr unsigned int numberOfSamples{ 25 };

  realLower.Fill(1000);
  realUpper.Fill(0);

  // Force the first value not to be the min or max.
  measure[0] = 13;
  measure[1] = 39;
  sample->PushBack(measure);

  for (unsigned int i = 1; i < numberOfSamples; ++i)
  {
    const float value = i + 3;
    measure[0] = value;
    measure[1] = value * value;
    sample->PushBack(measure);

    for (unsigned int j = 0; j < measurementVectorSize; ++j)
    {
      if (measure[j] < realLower[j])
      {
        realLower[j] = measure[j];
      }
      if (measure[j] > realUpper[j])
      {
        realUpper[j] = measure[j];
      }
    }
  }

  constSample = sample;
  // Now testing the real algorithm
  ASSERT_NO_THROW(
    itk::Statistics::Algorithm::FindSampleBound(constSample, constSample->Begin(), constSample->End(), lower, upper));

  constexpr float epsilon{ 1e-5 };

  for (unsigned int j = 0; j < measurementVectorSize; ++j)
  {
    EXPECT_NEAR(lower[j], realLower[j], epsilon) << "FindSampleBound() failed";
    EXPECT_NEAR(upper[j], realUpper[j], epsilon) << "FindSampleBound() failed";
  }
}
