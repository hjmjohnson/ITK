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
#include "itkListSample.h"
#include "itkNeighborhoodSampler.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(NeighborhoodSampler, ConvertedLegacyTest1)
{

  constexpr unsigned int MeasurementVectorSize{ 17 };

  using MeasurementVectorType = itk::FixedArray<float, MeasurementVectorSize>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using FilterType = itk::Statistics::NeighborhoodSampler<SampleType>;

  using RadiusType = FilterType::RadiusType;
  using InputRadiusObjectType = FilterType::InputRadiusObjectType;

  auto sample = SampleType::New();

  auto filter = FilterType::New();

  // Test GetInput() before setting the input
  EXPECT_EQ(filter->GetInput(), nullptr) << "GetInput() should have returned nullptr";

  // Test GetOutput() before creating the output
  EXPECT_NE(filter->GetOutput(), nullptr) << "GetOutput() should have returned NON-nullptr";

  filter->SetInput(sample);

  EXPECT_EQ(filter->GetInput(), sample.GetPointer()) << "GetInput() didn't matched SetInput()";


  // Testing the settings of the Radius.
  constexpr RadiusType radius1{ 237 };
  constexpr RadiusType radius2{ 179 };

  filter->SetRadius(radius1);

  const InputRadiusObjectType * recoveredRadiusObject = filter->GetRadiusInput();

  ASSERT_NE(recoveredRadiusObject, nullptr) << "GetRadiusInput() returned nullptr object.";

  EXPECT_EQ(recoveredRadiusObject->Get(), radius1) << "GetRadiusInput() test for value consistency 1 failed.";

  filter->SetRadius(radius2);

  recoveredRadiusObject = filter->GetRadiusInput();

  ASSERT_NE(recoveredRadiusObject, nullptr) << "GetRadiusInput() returned nullptr object.";

  EXPECT_EQ(recoveredRadiusObject->Get(), radius2) << "GetRadiusInput() test for value consistency 2 failed.";


  auto radiusObject1 = InputRadiusObjectType::New();

  radiusObject1->Set(radius1);

  filter->SetRadiusInput(radiusObject1);

  recoveredRadiusObject = filter->GetRadiusInput();

  EXPECT_EQ(recoveredRadiusObject, radiusObject1) << "GetRadiusInput() test for pointer consistency 1 failed.";

  EXPECT_EQ(recoveredRadiusObject->Get(), radius1) << "GetRadiusInput() test for value consistency 3 failed.";

  auto radiusObject2 = InputRadiusObjectType::New();

  radiusObject2->Set(radius2);

  filter->SetRadiusInput(radiusObject2);

  recoveredRadiusObject = filter->GetRadiusInput();

  EXPECT_EQ(recoveredRadiusObject, radiusObject2) << "GetRadiusInput() test for pointer consistency 2 failed.";

  EXPECT_EQ(recoveredRadiusObject->Get(), radius2) << "GetRadiusInput() test for value consistency 4 failed.";

  //
  // Testing exception cases in the GenerateData() method.
  //
  filter->SetRadiusInput(nullptr);

  std::cout << "GetRadiusInput() =  " << filter->GetRadiusInput() << std::endl;

  EXPECT_THROW(filter->Update(), itk::ExceptionObject) << "Failure to throw expected exception "
                                                       << " due to nullptr SetRadiusInput()";

  radiusObject1->Set(100);
  filter->SetRadiusInput(radiusObject1);


  //
  // Exercise the Print() method
  //
  filter->Print(std::cout);


  filter->Update();

  std::cout << "Classname " << filter->GetNameOfClass() << std::endl;
}
