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
#include "itkHistogram.h"
#include "itkSampleToHistogramFilter.h"
#include "itkIntTypes.h"
#include "itkMath.h"
#include "itkGTest.h"


TEST(SampleToHistogramFilter, ConvertedLegacyTest)
{

  constexpr unsigned int numberOfComponents{ 3 };
  using MeasurementType = float;

  using MeasurementVectorType = itk::Array<MeasurementType>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using HistogramType = itk::Statistics::Histogram<MeasurementType, itk::Statistics::DenseFrequencyContainer2>;

  using FilterType = itk::Statistics::SampleToHistogramFilter<SampleType, HistogramType>;

  using InputHistogramSizeObjectType = FilterType::InputHistogramSizeObjectType;
  using HistogramSizeType = FilterType::HistogramSizeType;
  using HistogramMeasurementType = FilterType::HistogramMeasurementType;
  using HistogramMeasurementVectorType = FilterType::HistogramMeasurementVectorType;
  using InputHistogramMeasurementObjectType = FilterType::InputHistogramMeasurementObjectType;
  using InputHistogramMeasurementVectorObjectType = FilterType::InputHistogramMeasurementVectorObjectType;

  auto filter = FilterType::New();

  auto sample = SampleType::New();

  // Test GetInput() before setting the input
  EXPECT_EQ(filter->GetInput(), nullptr) << "GetInput() should have returned nullptr";

  // Test GetOutput() before creating the output
  EXPECT_NE(filter->GetOutput(), nullptr) << "GetOutput() should have returned NON-nullptr";

  filter->SetInput(sample);

  EXPECT_EQ(filter->GetInput(), sample.GetPointer()) << "GetInput() didn't matched SetInput()";

  // Exercise the Print method.
  filter->Print(std::cout);


  // Test exception when calling Update() without having
  // defined the size of the histogram in the filter.
  EXPECT_THROW(filter->Update(), itk::MissingHistogramSizeInput)
    << "Failure to throw expected exception due to lack" << " of calling SetHistogramSize() in the filter ";

  HistogramSizeType histogramSize0(numberOfComponents, 1);
  filter->SetHistogramSize(histogramSize0);

  // Test exception when calling Update() without having
  // defined the number of components in the sample
  EXPECT_THROW(filter->Update(), itk::NullSizeHistogramInputMeasurementVectorSize)
    << "Failure to throw expected exception due to lack" << " of calling SetMeasurementVectorSize() in the sample";

  sample->SetMeasurementVectorSize(numberOfComponents);

  EXPECT_NO_THROW(filter->Update());

  HistogramSizeType histogramSize1(numberOfComponents);
  histogramSize1[0] = 256;
  histogramSize1[1] = 256;
  histogramSize1[2] = 256;

  HistogramSizeType histogramSize2(numberOfComponents);
  histogramSize2[0] = 128;
  histogramSize2[1] = 128;
  histogramSize2[2] = 128;


  filter->SetHistogramSize(histogramSize1);

  const InputHistogramSizeObjectType * returnedHistogramSizeObject = filter->GetHistogramSizeInput();

  ASSERT_NE(returnedHistogramSizeObject, nullptr) << "SetHistogramSize() failed pointer consistency test";

  HistogramSizeType returnedHistogramSize = returnedHistogramSizeObject->Get();

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(returnedHistogramSize[k1], histogramSize1[k1]) << "Get/Set HistogramSize() failed value consistency test";
  }

  filter->SetHistogramSize(histogramSize2);

  returnedHistogramSizeObject = filter->GetHistogramSizeInput();

  returnedHistogramSize = returnedHistogramSizeObject->Get();

  for (unsigned int k2 = 0; k2 < numberOfComponents; ++k2)
  {
    EXPECT_EQ(returnedHistogramSize[k2], histogramSize2[k2]) << "Get/Set HistogramSize() failed value consistency test";
  }


  auto histogramSizeObject = InputHistogramSizeObjectType::New();

  histogramSizeObject->Set(histogramSize1);

  filter->SetHistogramSizeInput(histogramSizeObject);

  returnedHistogramSizeObject = filter->GetHistogramSizeInput();

  EXPECT_EQ(returnedHistogramSizeObject, histogramSizeObject)
    << "Get/Set HistogramSizeInput() failed pointer consistency test";

  returnedHistogramSize = returnedHistogramSizeObject->Get();

  for (unsigned int k3 = 0; k3 < numberOfComponents; ++k3)
  {
    EXPECT_EQ(returnedHistogramSize[k3], histogramSize1[k3])
      << "Get/Set HistogramSizeInput() failed value consistency test";
  }

  histogramSizeObject->Set(histogramSize2);

  filter->SetHistogramSizeInput(histogramSizeObject);

  returnedHistogramSizeObject = filter->GetHistogramSizeInput();

  EXPECT_EQ(returnedHistogramSizeObject, histogramSizeObject)
    << "Get/Set HistogramSizeInput() failed pointer consistency test";

  returnedHistogramSize = returnedHistogramSizeObject->Get();

  for (unsigned int k4 = 0; k4 < numberOfComponents; ++k4)
  {
    EXPECT_EQ(returnedHistogramSize[k4], histogramSize2[k4])
      << "Get/Set HistogramSizeInput() failed value consistency test";
  }


  filter->SetHistogramSize(histogramSize1);
  filter->Update();
  itk::ModifiedTimeType modifiedTime = filter->GetMTime();
  filter->SetHistogramSize(histogramSize1);

  EXPECT_EQ(filter->GetMTime(), modifiedTime) << "SetHistogramSize() failed modified Test 1";

  filter->SetHistogramSize(histogramSize2);

  EXPECT_NE(filter->GetMTime(), modifiedTime) << "SetHistogramSize() failed modified Test 2";


  // Testing the settings of the MarginalScale.
  constexpr HistogramMeasurementType marginalScale1{ 237 };
  constexpr HistogramMeasurementType marginalScale2{ 179 };

  filter->SetMarginalScale(marginalScale1);

  const InputHistogramMeasurementObjectType * recoveredMarginalScaleObject = filter->GetMarginalScaleInput();

  ASSERT_NE(recoveredMarginalScaleObject, nullptr) << "GetMarginalScaleInput() returned nullptr object.";

  EXPECT_EQ(recoveredMarginalScaleObject->Get(), marginalScale1)
    << "GetMarginalScaleInput() test for value consistency 1 failed.";

  filter->SetMarginalScale(marginalScale2);

  recoveredMarginalScaleObject = filter->GetMarginalScaleInput();

  ASSERT_NE(recoveredMarginalScaleObject, nullptr) << "GetMarginalScaleInput() returned nullptr object.";

  EXPECT_EQ(recoveredMarginalScaleObject->Get(), marginalScale2)
    << "GetMarginalScaleInput() test for value consistency 2 failed.";


  auto marginalScaleObject1 = InputHistogramMeasurementObjectType::New();

  marginalScaleObject1->Set(marginalScale1);

  filter->SetMarginalScaleInput(marginalScaleObject1);

  recoveredMarginalScaleObject = filter->GetMarginalScaleInput();

  EXPECT_EQ(recoveredMarginalScaleObject, marginalScaleObject1)
    << "GetMarginalScaleInput() test for pointer consistency 1 failed.";

  EXPECT_EQ(recoveredMarginalScaleObject->Get(), marginalScale1)
    << "GetMarginalScaleInput() test for value consistency 3 failed.";

  auto marginalScaleObject2 = InputHistogramMeasurementObjectType::New();

  marginalScaleObject2->Set(marginalScale2);

  filter->SetMarginalScaleInput(marginalScaleObject2);

  recoveredMarginalScaleObject = filter->GetMarginalScaleInput();

  EXPECT_EQ(recoveredMarginalScaleObject, marginalScaleObject2)
    << "GetMarginalScaleInput() test for pointer consistency 2 failed.";

  EXPECT_EQ(recoveredMarginalScaleObject->Get(), marginalScale2)
    << "GetMarginalScaleInput() test for value consistency 4 failed.";

  filter->SetMarginalScaleInput(marginalScaleObject1);

  recoveredMarginalScaleObject = filter->GetMarginalScaleInput();

  EXPECT_EQ(recoveredMarginalScaleObject, marginalScaleObject1)
    << "GetMarginalScaleInput() test for pointer consistency 3 failed.";

  EXPECT_EQ(recoveredMarginalScaleObject->Get(), marginalScale1)
    << "GetMarginalScaleInput() test for value consistency 5 failed.";


  // Testing the settings of the BinMaximum and BinMinimum methods.
  HistogramMeasurementVectorType histogramBinMinimum1(numberOfComponents);
  histogramBinMinimum1[0] = 0;
  histogramBinMinimum1[1] = 0;
  histogramBinMinimum1[2] = 0;

  HistogramMeasurementVectorType histogramBinMinimum2(numberOfComponents);
  histogramBinMinimum2[0] = 17;
  histogramBinMinimum2[1] = 17;
  histogramBinMinimum2[2] = 17;


  filter->SetHistogramBinMinimum(histogramBinMinimum1);

  const InputHistogramMeasurementVectorObjectType * returnedHistogramBinMinimumObject =
    filter->GetHistogramBinMinimumInput();

  ASSERT_NE(returnedHistogramBinMinimumObject, nullptr) << "SetHistogramSize() failed pointer consistency test";

  HistogramMeasurementVectorType returnedHistogramBinMinimum = returnedHistogramBinMinimumObject->Get();

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(returnedHistogramBinMinimum[k1], histogramBinMinimum1[k1])
      << "Get/Set HistogramBinMinimum() failed value consistency test";
  }


  filter->SetHistogramBinMinimum(histogramBinMinimum2);

  returnedHistogramBinMinimumObject = filter->GetHistogramBinMinimumInput();

  returnedHistogramBinMinimum = returnedHistogramBinMinimumObject->Get();

  for (unsigned int k2 = 0; k2 < numberOfComponents; ++k2)
  {
    EXPECT_EQ(returnedHistogramBinMinimum[k2], histogramBinMinimum2[k2])
      << "Get/Set HistogramSize() failed value consistency test";
  }


  const InputHistogramMeasurementVectorObjectType::Pointer histogramBinMinimumObject =
    InputHistogramMeasurementVectorObjectType::New();

  histogramBinMinimumObject->Set(histogramBinMinimum1);

  filter->SetHistogramBinMinimumInput(histogramBinMinimumObject);

  returnedHistogramBinMinimumObject = filter->GetHistogramBinMinimumInput();

  EXPECT_EQ(returnedHistogramBinMinimumObject, histogramBinMinimumObject)
    << "Get/Set HistogramBinMinimum() failed pointer consistency test";

  returnedHistogramBinMinimum = returnedHistogramBinMinimumObject->Get();

  for (unsigned int k3 = 0; k3 < numberOfComponents; ++k3)
  {
    EXPECT_EQ(returnedHistogramBinMinimum[k3], histogramBinMinimum1[k3])
      << "Get/Set HistogramBinMinimum() failed value consistency test";
  }

  histogramBinMinimumObject->Set(histogramBinMinimum2);

  filter->SetHistogramBinMinimumInput(histogramBinMinimumObject);

  returnedHistogramBinMinimumObject = filter->GetHistogramBinMinimumInput();

  EXPECT_EQ(returnedHistogramBinMinimumObject, histogramBinMinimumObject)
    << "Get/Set HistogramBinMinimum() failed pointer consistency test";

  returnedHistogramBinMinimum = returnedHistogramBinMinimumObject->Get();

  for (unsigned int k4 = 0; k4 < numberOfComponents; ++k4)
  {
    EXPECT_EQ(returnedHistogramBinMinimum[k4], histogramBinMinimum2[k4])
      << "Get/Set HistogramBinMinimum() failed value consistency test";
  }


  filter->SetHistogramBinMinimum(histogramBinMinimum1);
  filter->Update();
  modifiedTime = filter->GetMTime();
  filter->SetHistogramBinMinimum(histogramBinMinimum1);

  EXPECT_EQ(filter->GetMTime(), modifiedTime) << "SetHistogramBinMinimum() failed modified Test 1";

  filter->SetHistogramBinMinimum(histogramBinMinimum2);

  EXPECT_NE(filter->GetMTime(), modifiedTime) << "SetHistogramBinMinimum() failed modified Test 2";


  HistogramMeasurementVectorType histogramBinMaximum1(numberOfComponents);
  histogramBinMaximum1[0] = 0;
  histogramBinMaximum1[1] = 0;
  histogramBinMaximum1[2] = 0;

  HistogramMeasurementVectorType histogramBinMaximum2(numberOfComponents);
  histogramBinMaximum2[0] = 17;
  histogramBinMaximum2[1] = 17;
  histogramBinMaximum2[2] = 17;


  filter->SetHistogramBinMaximum(histogramBinMaximum1);

  const InputHistogramMeasurementVectorObjectType * returnedHistogramBinMaximumObject =
    filter->GetHistogramBinMaximumInput();

  ASSERT_NE(returnedHistogramBinMaximumObject, nullptr) << "SetHistogramSize() failed pointer consistency test";

  HistogramMeasurementVectorType returnedHistogramBinMaximum = returnedHistogramBinMaximumObject->Get();

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(returnedHistogramBinMaximum[k1], histogramBinMaximum1[k1])
      << "Get/Set HistogramBinMaximum() failed value consistency test";
  }


  filter->SetHistogramBinMaximum(histogramBinMaximum2);

  returnedHistogramBinMaximumObject = filter->GetHistogramBinMaximumInput();

  returnedHistogramBinMaximum = returnedHistogramBinMaximumObject->Get();

  for (unsigned int k2 = 0; k2 < numberOfComponents; ++k2)
  {
    EXPECT_EQ(returnedHistogramBinMaximum[k2], histogramBinMaximum2[k2])
      << "Get/Set HistogramSize() failed value consistency test";
  }


  const InputHistogramMeasurementVectorObjectType::Pointer histogramBinMaximumObject =
    InputHistogramMeasurementVectorObjectType::New();

  histogramBinMaximumObject->Set(histogramBinMaximum1);

  filter->SetHistogramBinMaximumInput(histogramBinMaximumObject);

  returnedHistogramBinMaximumObject = filter->GetHistogramBinMaximumInput();

  EXPECT_EQ(returnedHistogramBinMaximumObject, histogramBinMaximumObject)
    << "Get/Set HistogramBinMaximum() failed pointer consistency test";

  returnedHistogramBinMaximum = returnedHistogramBinMaximumObject->Get();

  for (unsigned int k3 = 0; k3 < numberOfComponents; ++k3)
  {
    EXPECT_EQ(returnedHistogramBinMaximum[k3], histogramBinMaximum1[k3])
      << "Get/Set HistogramBinMaximum() failed value consistency test";
  }

  histogramBinMaximumObject->Set(histogramBinMaximum2);

  filter->SetHistogramBinMinimumInput(histogramBinMaximumObject);

  returnedHistogramBinMaximumObject = filter->GetHistogramBinMinimumInput();

  EXPECT_EQ(returnedHistogramBinMaximumObject, histogramBinMaximumObject)
    << "Get/Set HistogramBinMaximum() failed pointer consistency test";

  returnedHistogramBinMaximum = returnedHistogramBinMaximumObject->Get();

  for (unsigned int k4 = 0; k4 < numberOfComponents; ++k4)
  {
    EXPECT_EQ(returnedHistogramBinMaximum[k4], histogramBinMaximum2[k4])
      << "Get/Set HistogramBinMaximum() failed value consistency test";
  }


  filter->SetHistogramBinMaximum(histogramBinMaximum1);
  filter->Update();
  modifiedTime = filter->GetMTime();
  filter->SetHistogramBinMaximum(histogramBinMaximum1);

  EXPECT_EQ(filter->GetMTime(), modifiedTime) << "SetHistogramBinMaximum() failed modified Test 1";

  filter->SetHistogramBinMaximum(histogramBinMaximum2);

  EXPECT_NE(filter->GetMTime(), modifiedTime) << "SetHistogramBinMaximum() failed modified Test 2";

  // Testing the settings of the AutoMinimumMaximum Flag.
  constexpr bool autoMinimumMaximum1{ true };
  constexpr bool autoMinimumMaximum2{ false };

  filter->SetAutoMinimumMaximum(autoMinimumMaximum1);

  using InputBooleanObjectType = FilterType::InputBooleanObjectType;

  const InputBooleanObjectType * recoveredAutoMinimumMaximumObject = filter->GetAutoMinimumMaximumInput();

  ASSERT_NE(recoveredAutoMinimumMaximumObject, nullptr) << "GetAutoMinimumMaximumInput() returned nullptr object.";

  EXPECT_EQ(recoveredAutoMinimumMaximumObject->Get(), autoMinimumMaximum1)
    << "GetAutoMinimumMaximumInput() test for value consistency 1 failed.";

  filter->SetAutoMinimumMaximum(autoMinimumMaximum2);

  recoveredAutoMinimumMaximumObject = filter->GetAutoMinimumMaximumInput();

  ASSERT_NE(recoveredAutoMinimumMaximumObject, nullptr) << "GetAutoMinimumMaximumInput() returned nullptr object.";

  EXPECT_EQ(recoveredAutoMinimumMaximumObject->Get(), autoMinimumMaximum2)
    << "GetAutoMinimumMaximumInput() test for value consistency 2 failed.";


  auto autoMinimumMaximumObject1 = InputBooleanObjectType::New();

  autoMinimumMaximumObject1->Set(autoMinimumMaximum1);

  filter->SetAutoMinimumMaximumInput(autoMinimumMaximumObject1);

  recoveredAutoMinimumMaximumObject = filter->GetAutoMinimumMaximumInput();

  EXPECT_EQ(recoveredAutoMinimumMaximumObject, autoMinimumMaximumObject1)
    << "GetAutoMinimumMaximumInput() test for pointer consistency 1 failed.";

  EXPECT_EQ(recoveredAutoMinimumMaximumObject->Get(), autoMinimumMaximum1)
    << "GetAutoMinimumMaximumInput() test for value consistency 3 failed.";

  auto autoMinimumMaximumObject2 = InputBooleanObjectType::New();

  autoMinimumMaximumObject2->Set(autoMinimumMaximum2);

  filter->SetAutoMinimumMaximumInput(autoMinimumMaximumObject2);

  recoveredAutoMinimumMaximumObject = filter->GetAutoMinimumMaximumInput();

  EXPECT_EQ(recoveredAutoMinimumMaximumObject, autoMinimumMaximumObject2)
    << "GetAutoMinimumMaximumInput() test for pointer consistency 2 failed.";

  EXPECT_EQ(recoveredAutoMinimumMaximumObject->Get(), autoMinimumMaximum2)
    << "GetAutoMinimumMaximumInput() test for value consistency 4 failed.";

  filter->SetAutoMinimumMaximumInput(autoMinimumMaximumObject1);

  recoveredAutoMinimumMaximumObject = filter->GetAutoMinimumMaximumInput();

  EXPECT_EQ(recoveredAutoMinimumMaximumObject, autoMinimumMaximumObject1)
    << "GetAutoMinimumMaximumInput() test for pointer consistency 3 failed.";

  EXPECT_EQ(recoveredAutoMinimumMaximumObject->Get(), autoMinimumMaximum1)
    << "GetAutoMinimumMaximumInput() test for value consistency 5 failed.";


  //
  // Testing exception cases in the GenerateData() method.
  //
  filter->SetHistogramSizeInput(nullptr);

  std::cout << "GetHistogramSizeInput() =  " << filter->GetHistogramSizeInput() << std::endl;

  EXPECT_THROW(filter->Update(), itk::MissingHistogramSizeInput)
    << "Failure to throw expected exception " << " due to nullptr SetHistogramSizeInput()";

  filter->SetHistogramSizeInput(histogramSizeObject);

  //
  // Testing exception cases in the GenerateData() method.
  //
  filter->SetMarginalScaleInput(nullptr);

  std::cout << "GetMarginalScaleInput() =  " << filter->GetMarginalScaleInput() << std::endl;

  EXPECT_THROW(filter->Update(), itk::MissingHistogramMarginalScaleInput)
    << "Failure to throw expected exception " << " due to nullptr SetMarginalScaleInput()";

  marginalScaleObject1->Set(100);
  filter->SetMarginalScaleInput(marginalScaleObject1);


  //
  // Testing exception cases in the GenerateData() method.
  //

  // First, force to use the minimum and maximum provided by the user.
  filter->SetAutoMinimumMaximum(false);

  filter->SetHistogramBinMinimumInput(nullptr);

  std::cout << "GetHistogramBinMinimumInput() =  " << filter->GetHistogramBinMinimumInput() << std::endl;

  EXPECT_THROW(filter->Update(), itk::MissingHistogramBinMinimumInput)
    << "Failure to throw expected exception " << " due to nullptr SetHistogramBinMinimumInput()";

  histogramBinMinimumObject->Set(histogramBinMinimum1);
  filter->SetHistogramBinMinimumInput(histogramBinMinimumObject);

  //
  // Testing exception cases in the GenerateData() method.
  //
  filter->SetHistogramBinMaximumInput(nullptr);

  std::cout << "GetHistogramBinMaximumInput() =  " << filter->GetHistogramBinMaximumInput() << std::endl;

  EXPECT_THROW(filter->Update(), itk::MissingHistogramBinMaximumInput)
    << "Failure to throw expected exception " << " due to nullptr SetHistogramBinMaximumInput()";

  histogramBinMaximumObject->Set(histogramBinMaximum1);
  filter->SetHistogramBinMaximumInput(histogramBinMaximumObject);


  EXPECT_NO_THROW(filter->Update());


  // Test GetOutput() after creating the output
  EXPECT_NE(filter->GetOutput(), nullptr) << "GetOutput() should have returned NON-nullptr";
}
