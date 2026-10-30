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
#include "itkDataObject.h"
#include "itkProcessObject.h"
#include "itkGTest.h"
#include "itkNumericTraits.h"
#include "itkIntTypes.h"
#include "itkMultiThreaderBase.h"

namespace itk
{

class TestDataObject : public DataObject
{
public:
  /** Standard class type aliases. */
  using Self = TestDataObject;
  using Superclass = DataObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
};

class TestProcessObject : public ProcessObject
{
public:
  TestProcessObject() = default;
  /** Standard class type aliases. */
  using Self = TestProcessObject;
  using Superclass = ProcessObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  // expose the protected method so we can test them
  using Superclass::GetInput;
  using Superclass::SetInput;
  using Superclass::GetPrimaryInput;
  using Superclass::SetPrimaryInput;
  using Superclass::GetOutput;
  using Superclass::SetOutput;
  using Superclass::GetPrimaryOutput;
  using Superclass::SetPrimaryOutput;
  using Superclass::SetPrimaryInputName;
  using Superclass::SetPrimaryOutputName;
  using Superclass::GetPrimaryInputName;
  using Superclass::GetPrimaryOutputName;
  using Superclass::MakeNameFromIndex;
  using Superclass::MakeIndexFromName;
  using Superclass::SetNthInput;
  using Superclass::AddInput;
  using Superclass::RemoveInput;
  using Superclass::SetNumberOfRequiredInputs;
  using Superclass::GetNumberOfRequiredInputs;
  using Superclass::PushBackInput;
  using Superclass::PopBackInput;
  using Superclass::PushFrontInput;
  using Superclass::PopFrontInput;
  using Superclass::SetNumberOfIndexedInputs;
  using Superclass::SetNthOutput;
  using Superclass::AddOutput;
  using Superclass::RemoveOutput;
  using Superclass::SetNumberOfRequiredOutputs;
  using Superclass::GetNumberOfRequiredOutputs;
  using Superclass::SetNumberOfIndexedOutputs;
  using Superclass::GenerateInputRequestedRegion;
  using Superclass::GenerateOutputRequestedRegion;
  using Superclass::GenerateOutputInformation;
  using Superclass::GenerateData;
  using Superclass::PropagateResetPipeline;
  using Superclass::ReleaseInputs;
  using Superclass::CacheInputReleaseDataFlags;
  using Superclass::RestoreInputReleaseDataFlags;
  using Superclass::GetRequiredInputNames;
  using Superclass::AddRequiredInputName;
  using Superclass::AddOptionalInputName;
  using Superclass::RemoveRequiredInputName;
  using Superclass::IsRequiredInputName;
  using Superclass::SetRequiredInputNames;
  using Superclass::VerifyPreconditions;


  void
  test_components_02(const itk::TestDataObject::Pointer input0,
                     const itk::TestDataObject::Pointer input1,
                     const itk::TestDataObject::Pointer output1)
  {
    {
      // Test AddOptionalInputName
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::AddOptionalInputName("OptImage");
      EXPECT_EQ(0u, process->GetRequiredInputNames().size());
      EXPECT_EQ(1u, process->GetInputNames().size());
      EXPECT_EQ("OptImage", process->GetInputNames().front());
      EXPECT_FALSE(process->ProcessObject::IsRequiredInputName("OptImage"));

      process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfRequiredInputs(1);
      process->ProcessObject::AddOptionalInputName("OptImage", 1);
      EXPECT_EQ(1u, process->GetRequiredInputNames().size());
      EXPECT_EQ(2u, process->GetInputNames().size());
      EXPECT_FALSE(process->ProcessObject::IsRequiredInputName("OptImage"));
      process->ProcessObject::SetInput("OptImage", input0);
      EXPECT_EQ(input0, process->GetInput("OptImage"));

      process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfRequiredInputs(1);
      process->ProcessObject::AddOptionalInputName("OptImage", 1);
      EXPECT_EQ(1u, process->GetRequiredInputNames().size());
      EXPECT_EQ(2u, process->GetInputNames().size());
      EXPECT_FALSE(process->ProcessObject::IsRequiredInputName("OptImage"));

      process->ProcessObject::SetInput("OptImage", input0);
      EXPECT_EQ(input0, process->GetInput("OptImage"));
      EXPECT_EQ(input0, process->GetInput(1));
      EXPECT_EQ(0u, process->GetNumberOfValidRequiredInputs());
      EXPECT_THROW(process->ProcessObject::VerifyPreconditions(), itk::ExceptionObject);

      process->ProcessObject::SetPrimaryInput(input0);
      EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
      ASSERT_NO_THROW(process->ProcessObject::VerifyPreconditions());

      process->ProcessObject::SetInput("OptImage", nullptr);
      EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
      ASSERT_NO_THROW(process->ProcessObject::VerifyPreconditions());

      process = itk::TestProcessObject::New();
      process->ProcessObject::SetNthInput(1, input0);
      process->ProcessObject::AddOptionalInputName("OptImage", 1);
      EXPECT_EQ(input0, process->GetInput("OptImage"));
      EXPECT_EQ(input0, process->GetInput(1));

      process = itk::TestProcessObject::New();
      process->ProcessObject::SetInput("OptImage", input0);
      process->ProcessObject::SetNthInput(1, input1);
      process->ProcessObject::AddOptionalInputName("OptImage", 1);
      EXPECT_EQ(input0, process->GetInput("OptImage"));
      EXPECT_EQ(input0, process->GetInput(1));
    }
    {
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfRequiredInputs(2);
      process->ProcessObject::SetPrimaryInputName("Image1");
      process->ProcessObject::AddRequiredInputName("Image2");
      EXPECT_EQ(2u, process->GetNumberOfRequiredInputs());
      EXPECT_EQ(0u, process->GetNumberOfValidRequiredInputs());
      process->ProcessObject::SetInput("Image1", input0);
      EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
      process->ProcessObject::SetInput("Image2", input0);
      process->ProcessObject::RemoveRequiredInputName("Image2");

      EXPECT_THROW(process->ProcessObject::AddRequiredInputName("", 1), itk::ExceptionObject);
      process->ProcessObject::AddRequiredInputName("Image2", 1);
      process->Print(std::cout);
      EXPECT_EQ(2u, process->GetNumberOfRequiredInputs());
      EXPECT_EQ(2u, process->GetNumberOfValidRequiredInputs());
      ASSERT_NO_THROW(process->ProcessObject::VerifyPreconditions());
    }
    {
      // testing SetNumberOfIndexedInputs
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfIndexedInputs(1);
      EXPECT_EQ(0u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(process->GetPrimaryInput(), nullptr);

      process->ProcessObject::SetPrimaryInput(input0);
      EXPECT_EQ(1u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(input0, process->GetPrimaryInput());

      process->ProcessObject::SetNumberOfIndexedInputs(0);
      EXPECT_EQ(0u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(process->GetPrimaryInput(), nullptr);

      process->ProcessObject::SetNumberOfIndexedInputs(3);
      EXPECT_EQ(3u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(process->GetPrimaryInput(), nullptr);
      process->ProcessObject::SetNthInput(1, input1);
      EXPECT_EQ(input1, process->GetInput(1));
      process->ProcessObject::SetNthInput(2, input1);
      EXPECT_EQ(input1, process->GetInput(2));
      process->ProcessObject::SetNumberOfIndexedInputs(1);
      EXPECT_EQ(0u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(process->GetPrimaryInput(), nullptr);
    }
    {
      // testing RemoveInput
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfIndexedInputs(2);
      process->ProcessObject::SetPrimaryInput(input0);
      EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());
      process->ProcessObject::RemoveInput("Primary");
      EXPECT_EQ(process->GetPrimaryInput(), nullptr);
      EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());
      EXPECT_EQ(1u, process->GetNumberOfInputs());

      process->ProcessObject::AddRequiredInputName("Req");
      process->ProcessObject::SetInput("Req", input0);
      EXPECT_EQ(input0, process->GetInput("Req"));
      process->ProcessObject::RemoveInput("Req");
      EXPECT_EQ(process->GetInput("Req"), nullptr);
      EXPECT_TRUE(process->ProcessObject::IsRequiredInputName("Req"));

      process->ProcessObject::SetInput("name", input0);
      EXPECT_EQ(input0, process->GetInput("name"));
      process->ProcessObject::RemoveInput("name");
      EXPECT_EQ(process->GetInput("name"), nullptr);
      EXPECT_EQ(2u, process->GetNumberOfInputs());

      process->ProcessObject::RemoveInput(99);
      EXPECT_EQ(process->GetInput("Req"), nullptr);
      EXPECT_TRUE(process->ProcessObject::IsRequiredInputName("Req"));
      EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());

      process->ProcessObject::RemoveInput(1);
      EXPECT_EQ(0u, process->GetNumberOfIndexedInputs());
    }
    {
      // testing SetNumberOfIndexedOutputs
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::SetNumberOfIndexedOutputs(1);
      EXPECT_EQ(0u, process->GetNumberOfIndexedOutputs());
      EXPECT_EQ(process->GetPrimaryOutput(), nullptr);

      process->ProcessObject::SetPrimaryOutput(input0);
      EXPECT_EQ(1u, process->GetNumberOfIndexedOutputs());
      EXPECT_EQ(input0, process->GetPrimaryOutput());

      process->ProcessObject::SetNumberOfIndexedOutputs(0);
      EXPECT_EQ(0u, process->GetNumberOfIndexedOutputs());
      EXPECT_EQ(process->GetPrimaryOutput(), nullptr);

      process->ProcessObject::SetNumberOfIndexedOutputs(3);
      EXPECT_EQ(3u, process->GetNumberOfIndexedOutputs());
      EXPECT_EQ(process->GetPrimaryOutput(), nullptr);
      process->ProcessObject::SetNthOutput(1, input1);
      EXPECT_EQ(input1, process->GetOutput(1));
      process->ProcessObject::SetNthOutput(2, input1);
      EXPECT_EQ(input1, process->GetOutput(2));
      process->ProcessObject::SetNumberOfIndexedOutputs(1);
      EXPECT_EQ(0u, process->GetNumberOfIndexedOutputs());
      EXPECT_EQ(process->GetPrimaryOutput(), nullptr);

      process->ProcessObject::SetNumberOfRequiredOutputs(1);
      std::cout << process;
      process->ProcessObject::SetPrimaryOutput(input0);
      std::cout << process;
    }
    {
      // test default state where null  is primary output
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      EXPECT_EQ(0u, process->GetNumberOfOutputs());
      EXPECT_EQ(process->GetPrimaryOutput(), nullptr);
      process->ProcessObject::SetOutput("Out", output1);
      process->ProcessObject::SetPrimaryOutputName("Out");
      EXPECT_EQ(output1, process->GetPrimaryOutput());
      EXPECT_EQ(process->GetOutput("Primary"), nullptr);
      process->ProcessObject::RemoveOutput("Primary");
    }
    {
      itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
      process->ProcessObject::SetOutput("New", nullptr);
    }
  }


  void
  test_componets_00(const itk::TestDataObject::Pointer input0, const itk::TestDataObject::Pointer input1)
  {
    // create a TestProcessObject
    itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();

    // and exercise various methods
    itk::TestProcessObject::NameArray names = process->GetInputNames();
    EXPECT_EQ(0u, names.size());
    itk::TestProcessObject::DataObjectPointerArray dataObjects = process->GetInputs();
    EXPECT_EQ(0u, dataObjects.size());
    //   constDataObjects = process->GetInputs();
    //   ITK_TEST_SET_GET_VALUE( 0, constDataObjects.size() );
    EXPECT_FALSE(process->HasInput("toto"));
    EXPECT_EQ(0u, process->GetNumberOfInputs());

    names = process->GetOutputNames();
    EXPECT_EQ(0u, names.size());
    dataObjects = process->GetOutputs();
    EXPECT_EQ(0u, dataObjects.size());
    //   constDataObjects = process->GetOutputs();
    //   ITK_TEST_SET_GET_VALUE( 0, constDataObjects.size() );
    EXPECT_FALSE(process->HasOutput("toto"));
    EXPECT_EQ(0u, process->GetNumberOfOutputs());

    dataObjects = process->GetIndexedInputs();
    EXPECT_EQ(0u, dataObjects.size());
    EXPECT_EQ(0u, process->GetNumberOfIndexedInputs());
    EXPECT_EQ(0u, process->GetNumberOfValidRequiredInputs());

    dataObjects = process->GetIndexedOutputs();
    EXPECT_EQ(0u, dataObjects.size());
    EXPECT_EQ(0u, process->GetNumberOfIndexedOutputs());
    //   ITK_TEST_SET_GET_VALUE( 0, process->GetNumberOfValidRequiredOutputs() );

    itk::DataObject::Pointer dataObject = process->MakeOutput(0);
    EXPECT_TRUE(dataObject.IsNotNull());
    dataObject = process->MakeOutput(1);
    EXPECT_TRUE(dataObject.IsNotNull());
    dataObject = process->MakeOutput(2);
    EXPECT_TRUE(dataObject.IsNotNull());
    dataObject = process->MakeOutput("Not an Index");
    EXPECT_TRUE(dataObject.IsNotNull());

    EXPECT_FALSE(process->GetAbortGenerateData());
    process->SetAbortGenerateData(true);
    EXPECT_TRUE(process->GetAbortGenerateData());
    process->AbortGenerateDataOff();
    EXPECT_FALSE(process->GetAbortGenerateData());
    process->AbortGenerateDataOn();
    EXPECT_TRUE(process->GetAbortGenerateData());
    process->AbortGenerateDataOff();
    EXPECT_FALSE(process->GetAbortGenerateData());

    EXPECT_EQ(0.0, process->GetProgress());
    process->UpdateProgress(1.0);
    EXPECT_EQ(1.0, process->GetProgress());
    process->UpdateProgress(10000.0);
    EXPECT_EQ(1.0, process->GetProgress());
    process->UpdateProgress(-1.0);
    EXPECT_EQ(0.0, process->GetProgress());
    process->UpdateProgress(0.0);
    EXPECT_EQ(0.0, process->GetProgress());

    // verify no progress overflow
    for (size_t i = 0; i < 10; ++i)
    {
      process->IncrementProgress(0.1);
    }
    EXPECT_FLOAT_EQ(process->GetProgress(), 1.0f) << "Progress is not reported correctly!";

    // shouldn't do anything: there is no output at this point
    itk::ModifiedTimeType mtime = process->GetMTime();
    process->Update();
    EXPECT_EQ(mtime, process->GetMTime());

    // shouldn't do anything: there is no output at this point
    mtime = process->GetMTime();
    process->UpdateLargestPossibleRegion();
    EXPECT_EQ(mtime, process->GetMTime());

    // shouldn't do anything: there is no output at this point
    mtime = process->GetMTime();
    process->UpdateOutputInformation();
    EXPECT_EQ(mtime, process->GetMTime());

    // TODO: how to test those ones?
    // PropagateRequestedRegion(DataObject *output);
    // UpdateOutputData(DataObject *output);
    // EnlargeOutputRequestedRegion( DataObject *itkNotUsed(output) ){}

    // TODO: doesn't do anything for now, but should probably do something even without
    // input nor output
    mtime = process->GetMTime();
    process->ResetPipeline();
    EXPECT_EQ(mtime, process->GetMTime());

    // nothing should change: there is no output
    EXPECT_FALSE(process->GetReleaseDataFlag());
    process->SetReleaseDataFlag(true);
    EXPECT_FALSE(process->GetReleaseDataFlag());
    process->ReleaseDataFlagOff();
    EXPECT_FALSE(process->GetReleaseDataFlag());
    process->ReleaseDataFlagOn();
    EXPECT_FALSE(process->GetReleaseDataFlag());

    EXPECT_TRUE(process->GetReleaseDataBeforeUpdateFlag());
    process->SetReleaseDataBeforeUpdateFlag(false);
    EXPECT_FALSE(process->GetReleaseDataBeforeUpdateFlag());
    process->ReleaseDataBeforeUpdateFlagOn();
    EXPECT_TRUE(process->GetReleaseDataBeforeUpdateFlag());
    process->ReleaseDataBeforeUpdateFlagOff();
    EXPECT_FALSE(process->GetReleaseDataBeforeUpdateFlag());
    process->ReleaseDataBeforeUpdateFlagOn();
    EXPECT_TRUE(process->GetReleaseDataBeforeUpdateFlag());

    EXPECT_LE(itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads(), process->GetNumberOfWorkUnits());
    process->SetNumberOfWorkUnits(itk::ITK_MAX_THREADS - 1);
    EXPECT_EQ(itk::ITK_MAX_THREADS - 1, process->GetNumberOfWorkUnits());
    process->SetNumberOfWorkUnits(0);
    EXPECT_EQ(1u, process->GetNumberOfWorkUnits());
    process->SetNumberOfWorkUnits(itk::NumericTraits<itk::ThreadIdType>::max());
    EXPECT_LE(itk::MultiThreaderBase::GetGlobalMaximumNumberOfThreads(), process->GetNumberOfWorkUnits());
    process->SetNumberOfWorkUnits(itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads());
    EXPECT_EQ(itk::MultiThreaderBase::GetGlobalDefaultNumberOfThreads(), process->GetNumberOfWorkUnits());

    // not sure what to test with that method - at least test that it exist
    const itk::MultiThreaderBase::Pointer multiThreader = process->GetMultiThreader();
    EXPECT_TRUE(multiThreader.IsNotNull());

    // default input values
    EXPECT_EQ(process->GetPrimaryInput(), nullptr);
    EXPECT_EQ(process->GetInput("Primary"), nullptr);
    EXPECT_EQ(process->GetInput("toto"), nullptr);
    EXPECT_EQ(process->GetInput(0), nullptr);
    EXPECT_EQ(process->GetInput(1), nullptr);

    process->Print(std::cout);
    process->ProcessObject::SetInput("Primary", input0);
    names = process->GetInputNames();
    EXPECT_EQ(1u, names.size());

    EXPECT_EQ(input0, process->GetPrimaryInput());
    EXPECT_EQ(input0, process->GetInput(0));
    EXPECT_EQ(input0, process->GetInput("Primary"));
    EXPECT_EQ(1u, process->GetNumberOfIndexedInputs());
    process->ProcessObject::SetPrimaryInput(nullptr);

    EXPECT_EQ(process->GetPrimaryInput(), nullptr);
    EXPECT_EQ(process->GetInput(0), nullptr);
    EXPECT_EQ(process->GetInput("Primary"), nullptr);
    process->ProcessObject::SetNthInput(0, input0);

    EXPECT_EQ(input0, process->GetPrimaryInput());
    EXPECT_EQ(input0, process->GetInput(0));
    EXPECT_EQ(input0, process->GetInput("Primary"));
    process->ProcessObject::SetPrimaryInputName("First");

    EXPECT_EQ(input0, process->GetPrimaryInput());
    EXPECT_EQ(input0, process->GetInput(0));
    EXPECT_EQ(input0, process->GetInput("First"));

    process->ProcessObject::SetNthInput(1, input1);
    EXPECT_EQ(input1, process->GetInput(1));
    EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());
    process->ProcessObject::SetNthInput(1, nullptr);
    EXPECT_EQ(process->GetInput(1), nullptr);
    process->ProcessObject::SetNthInput(1, input1);

    process->Print(std::cout);
    process->ProcessObject::RemoveInput(1);
    EXPECT_EQ(1u, process->GetNumberOfIndexedInputs());
    process->ProcessObject::SetNthInput(1, input1);
    EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());
    EXPECT_EQ(input1, process->GetInput(1));
    process->ProcessObject::RemoveInput(10);
    EXPECT_EQ(2u, process->GetNumberOfIndexedInputs());
    process->ProcessObject::PopBackInput();
    EXPECT_EQ(1u, process->GetNumberOfIndexedInputs());

    const itk::TestDataObject::Pointer output = itk::TestDataObject::New();
    process->ProcessObject::SetNthOutput(0, output);

    process->ProcessObject::SetNumberOfRequiredInputs(1);
    process->ProcessObject::AddRequiredInputName("Foo");
    process->Print(std::cout);
    EXPECT_THROW(process->Update(), itk::ExceptionObject);
    process->ProcessObject::SetInput("Foo", input1);
    process->Print(std::cout);
    ASSERT_NO_THROW(process->Update());
    process->ProcessObject::AddRequiredInputName("Bar");
    process->ProcessObject::SetInput("Bar", input1);
    process->ProcessObject::SetNumberOfRequiredInputs(0);
    process->Print(std::cout);
    ASSERT_NO_THROW(process->Update());
    EXPECT_THROW(process->ProcessObject::SetInput("", input1), itk::ExceptionObject);

    names = process->ProcessObject::GetRequiredInputNames();
    EXPECT_EQ(2u, names.size());
    process->ProcessObject::RemoveRequiredInputName("Foo");
    process->ProcessObject::RemoveRequiredInputName("Bar");
    EXPECT_EQ(0u, process->GetRequiredInputNames().size());
    process->ProcessObject::SetRequiredInputNames(names);
    process->Print(std::cout);
    EXPECT_EQ(2u, process->GetRequiredInputNames().size());
    process->ProcessObject::SetPrimaryOutputName("Outy");
    const std::string primaryOutputName = process->ProcessObject::GetPrimaryOutputName();
    EXPECT_EQ("Outy", primaryOutputName);
  }
  void
  test_components_01(const itk::TestDataObject::Pointer input0)
  {
    itk::TestProcessObject::Pointer process = itk::TestProcessObject::New();
    process->ProcessObject::SetPrimaryInputName("Image1");
    EXPECT_THROW(process->ProcessObject::AddRequiredInputName(""), itk::ExceptionObject);
    process->Print(std::cout);
    EXPECT_EQ(1u, process->GetNumberOfRequiredInputs());
    process->ProcessObject::AddRequiredInputName("Image2");
    EXPECT_EQ(1u, process->GetNumberOfRequiredInputs());
    EXPECT_EQ(0u, process->GetNumberOfValidRequiredInputs());
    EXPECT_THROW(process->ProcessObject::VerifyPreconditions(), itk::ExceptionObject);
    process->ProcessObject::SetInput("Image1", input0);
    EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
    EXPECT_THROW(process->ProcessObject::VerifyPreconditions(), itk::ExceptionObject);
    process->ProcessObject::SetInput("Image2", input0);
    EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
    ASSERT_NO_THROW(process->ProcessObject::VerifyPreconditions());

    process->ProcessObject::SetNumberOfRequiredInputs(2);
    process->ProcessObject::SetInput("Image2", nullptr);
    process->ProcessObject::SetNthInput(10, input0);
    EXPECT_EQ(1u, process->GetNumberOfValidRequiredInputs());
    EXPECT_THROW(process->ProcessObject::VerifyPreconditions(), itk::ExceptionObject);
    process->ProcessObject::AddInput(input0);
    EXPECT_EQ(2u, process->GetNumberOfValidRequiredInputs());
    EXPECT_THROW(process->ProcessObject::VerifyPreconditions(), itk::ExceptionObject);
    process->ProcessObject::SetInput("Image2", input0);
    EXPECT_EQ(2u, process->GetNumberOfValidRequiredInputs());
    ASSERT_NO_THROW(process->ProcessObject::VerifyPreconditions());
  }

  void
  run_all_tests()
  {
    // create some data object that will be used as input and output
    const itk::TestDataObject::Pointer input0 = itk::TestDataObject::New();
    const itk::TestDataObject::Pointer input1 = itk::TestDataObject::New();
    test_componets_00(input0, input1);
    test_components_01(input0);
    const itk::TestDataObject::Pointer output1 = itk::TestDataObject::New();
    test_components_02(input0, input1, output1);
  }
};

} // namespace itk


TEST(DataObjectAndProcessObject, ConvertedLegacyTest)
{
  itk::TestProcessObject tpo;
  tpo.run_all_tests();
}
