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

#include "itkTemporalProcessObject.h"
#include "itkTemporalDataObject.h"
#include "itkTestingMacros.h"

/** Set up dummy implementations of TemporalProcessObject and
 * TemporalDataObject for testing
 */

namespace itk::TemporalProcessObjectTest
{

using SizeValueType = itk::SizeValueType;
using OffsetValueType = itk::OffsetValueType;

/** \class CallRecordEnums
 * \brief Contains all enum classes for CallRecord class.
 */
class CallRecordEnums
{
public:
  /**
   * \class RecordType
   * Record type used.*/
  enum class RecordType : uint8_t
  {
    START_CALL,
    END_CALL,
    MAX_RECORD_TYPE
  };
  /***
   * \class MethodType
   * Method type used*/
  enum class MethodType : uint8_t
  {
    GENERATE_DATA,
    STREAMING_GENERATE_DATA,
    MAX_METHOD_TYPE
  };
};
// Define how to print enumeration
extern ITKVideoCore_EXPORT std::ostream &
                           operator<<(std::ostream & out, const CallRecordEnums::RecordType value);
extern ITKVideoCore_EXPORT std::ostream &
                           operator<<(std::ostream & out, const CallRecordEnums::MethodType value);

/** Print enum values */
std::ostream &
operator<<(std::ostream & out, const CallRecordEnums::RecordType value)
{
  return out << [value] {
    switch (value)
    {
      case CallRecordEnums::RecordType::START_CALL:
        return "itk::CallRecordEnums::RecordType::START_CALL";
      case CallRecordEnums::RecordType::END_CALL:
        return "itk::CallRecordEnums::RecordType::END_CALL";
      case CallRecordEnums::RecordType::MAX_RECORD_TYPE:
        return "itk::CallRecordEnums::RecordType::MAX_RECORD_TYPE";
      default:
        return "INVALID VALUE FOR itk::CallRecordEnums::RecordType";
    }
  }();
}
std::ostream &
operator<<(std::ostream & out, const CallRecordEnums::MethodType value)
{
  return out << [value] {
    switch (value)
    {
      case CallRecordEnums::MethodType::GENERATE_DATA:
        return "itk::CallRecordEnums::MethodType::GENERATE_DATA";
      case CallRecordEnums::MethodType::STREAMING_GENERATE_DATA:
        return "itk::CallRecordEnums::MethodType::STREAMING_GENERATE_DATA";
      case CallRecordEnums::MethodType::MAX_METHOD_TYPE:
        return "itk::CallRecordEnums::MethodType::MAX_METHOD_TYPE";
      default:
        return "INVALID VALUE FOR itk::CallRecordEnums::MethodType";
    }
  }();
}

/**
 * \class CallRecord
 * Record of a start or end of a GenerateDataCall from a
 * DummyTemporalProcessObject instance
 */
class CallRecord
{
public:
  using RecordTypeEnum = CallRecordEnums::RecordType;
  using MethodTypeEnum = CallRecordEnums::MethodType;
#if !defined(ITK_LEGACY_REMOVE)
  /**Exposes enums values for backwards compatibility*/
  static constexpr RecordTypeEnum START_CALL = RecordTypeEnum::START_CALL;
  static constexpr RecordTypeEnum END_CALL = RecordTypeEnum::END_CALL;
  static constexpr RecordTypeEnum MAX_RECORD_TYPE = RecordTypeEnum::MAX_RECORD_TYPE;

  static constexpr MethodTypeEnum GENERATE_DATA = MethodTypeEnum::GENERATE_DATA;
  static constexpr MethodTypeEnum STREAMING_GENERATE_DATA = MethodTypeEnum::STREAMING_GENERATE_DATA;
  static constexpr MethodTypeEnum MAX_METHOD_TYPE = MethodTypeEnum::MAX_METHOD_TYPE;
#endif

  /** Constructor that takes necessary info */
  CallRecord(SizeValueType callerId, RecordTypeEnum recordType, MethodTypeEnum methodType)
  {
    if (recordType >= RecordTypeEnum::MAX_RECORD_TYPE || methodType >= MethodTypeEnum::MAX_METHOD_TYPE)
    {
      throw;
    }
    m_CallerId = callerId;
    m_RecordType = recordType;
    m_MethodType = methodType;
  }

  /** Access members */
  [[nodiscard]] SizeValueType
  GetCallerId() const
  {
    return m_CallerId;
  }
  [[nodiscard]] RecordTypeEnum
  GetRecordType() const
  {
    return m_RecordType;
  }
  [[nodiscard]] MethodTypeEnum
  GetMethodType() const
  {
    return m_MethodType;
  }

  /** Print out nicely */
  void
  Print()
  {
    std::cout << "ID: " << m_CallerId << " -> ";
    if (m_MethodType == MethodTypeEnum::GENERATE_DATA)
    {
      std::cout << "GenerateData - ";
    }
    else if (m_MethodType == MethodTypeEnum::STREAMING_GENERATE_DATA)
    {
      std::cout << "TemporalStreamingGenerateData - ";
    }

    if (m_RecordType == RecordTypeEnum::START_CALL)
    {
      std::cout << " START";
    }
    else if (m_RecordType == RecordTypeEnum::END_CALL)
    {
      std::cout << " END";
    }
    std::cout << std::endl;
  }

  /** Comparison operators */
  bool
  operator==(const CallRecord & other) const
  {
    return (m_CallerId == other.GetCallerId() && m_RecordType == other.GetRecordType() &&
            m_MethodType == other.GetMethodType());
  }

  ITK_UNEQUAL_OPERATOR_MEMBER_FUNCTION(CallRecord);

protected:
  SizeValueType  m_CallerId;
  RecordTypeEnum m_RecordType;
  MethodTypeEnum m_MethodType;
};

/**
 * Static list of CallRecord items representing the stack trace of
 * calls to GenerateData and TemporalStreamingGenerateData
 */
static std::vector<CallRecord> processCallStackTraceList;

/**
 * \class DummyTemporalDataObject
 * Create TemporalDataObject subclass that does nothing, but overrides some
 * methods to provide debug output
 */
class DummyTemporalDataObject : public TemporalDataObject
{
public:
  /** type alias */
  using Self = DummyTemporalDataObject;
  using Superclass = TemporalDataObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Class macros */
  itkNewMacro(Self);
  itkOverrideGetNameOfClassMacro(DummyTemporalDataObject);

  /** Override update for debug output */
  void
  Update() override
  {
    // std::cout << "Calling Update from temporal data object" << std::endl;
    Superclass::Update();
  }

  /** Override UpdateOutputInformation for debug output */
  void
  UpdateOutputInformation() override
  {
    // std::cout << "Calling UpdateOutputInformation from temporal data object"
    // << std::endl;
    Superclass::UpdateOutputInformation();
  }

  /** Override PropagateRequestedRegion for debug output */
  void
  PropagateRequestedRegion() override
  {
    Superclass::PropagateRequestedRegion();
  }

  /** Override UpdateOutputData for debug output */
  void
  UpdateOutputData() override
  {
    std::cout << "      UpdateOutputData from temporal data object" << std::endl;

    // DEBUG
    std::cout << "Buffered region outside: " << this->RequestedRegionIsOutsideOfTheBufferedRegion() << std::endl;
    Superclass::UpdateOutputData();
  }

  /** Fill buffer with X new frames */
  void
  SetBufferToXNewFrames(SizeValueType x)
  {
    // Set the internal number of buffers
    m_DataObjectBuffer->SetNumberOfBuffers(x);

    for (SizeValueType i = 0; i < x; ++i)
    {
      // Create a new DataObject
      const DataObject::Pointer obj = DataObject::New().GetPointer();

      // Append to the end of the buffer
      m_DataObjectBuffer->MoveHeadForward();
      m_DataObjectBuffer->SetBufferContents(0, obj);
    }

    // Set buffered region info
    m_BufferedTemporalRegion.SetFrameStart(0);
    m_BufferedTemporalRegion.SetFrameDuration(x);
  }

  /** Append the supplied data object */
  void
  SetObjectAtFrame(SizeValueType frameNumber, DataObject * obj)
  {
    m_DataObjectBuffer->SetBufferContents(frameNumber, obj);
  }

  /** Get a buffered frame */
  DataObject::Pointer
  GetFrame(SizeValueType frameNumber)
  {
    // if nothing buffered, just fail
    if (m_BufferedTemporalRegion.GetFrameDuration() == 0)
    {
      return nullptr;
    }

    // make sure we have the desired frame buffered
    const SizeValueType bufStart = m_BufferedTemporalRegion.GetFrameStart();
    const SizeValueType bufEnd = bufStart + m_BufferedTemporalRegion.GetFrameDuration() - 1;
    if (frameNumber < bufStart || frameNumber > bufEnd)
    {
      return nullptr;
    }

    // If we can, fetch the desired frame
    const OffsetValueType frameOffset = frameNumber - bufEnd; // Should be negative
    return m_DataObjectBuffer->GetBufferContents(frameOffset);
  }
};

/**
 * \class DummyTemporalProcessObject
 * Create TemporalProcessObject subclass that does nothing, but implements
 * New() and TemporalStreamingGenerateData()
 */
class DummyTemporalProcessObject : public TemporalProcessObject
{
public:
  /** type alias */
  using Self = DummyTemporalProcessObject;
  using Superclass = TemporalProcessObject;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Class macros */
  itkNewMacro(Self);
  itkOverrideGetNameOfClassMacro(DummyTemporalProcessObject);

  // Required implementations

  /** TemporalStreamingGenerateData */
  void
  TemporalStreamingGenerateData() override
  {
    // Create a START entry in the stack trace
    processCallStackTraceList.emplace_back(
      m_IdNumber, CallRecord::RecordTypeEnum::START_CALL, CallRecord::MethodTypeEnum::STREAMING_GENERATE_DATA);

    // Report
    const SizeValueType outputStart = this->GetOutput()->GetRequestedTemporalRegion().GetFrameStart();
    std::cout << "**(ID = " << m_IdNumber << ") - TemporalStreamingGenerateData" << std::endl;
    std::cout << "  -> output requested from: " << outputStart << " to "
              << this->GetOutput()->GetRequestedTemporalRegion().GetFrameDuration() + outputStart - 1 << std::endl;

    const SizeValueType inputStart = this->GetInput()->GetRequestedTemporalRegion().GetFrameStart();
    const SizeValueType inputEnd = inputStart + this->GetInput()->GetRequestedTemporalRegion().GetFrameDuration() - 1;
    std::cout << "  -> input requested from " << inputStart << " to " << inputEnd << std::endl;
    std::cout << "  -> input buffered from " << this->GetInput()->GetBufferedTemporalRegion().GetFrameStart() << " to "
              << this->GetInput()->GetBufferedTemporalRegion().GetFrameStart() +
                   this->GetInput()->GetBufferedTemporalRegion().GetFrameDuration() - 1
              << std::endl;

    // Get the list of unbuffered frames
    const TemporalRegion unbufferedRegion = this->GetOutput()->GetUnbufferedRequestedTemporalRegion();
    std::cout << unbufferedRegion << std::endl;

    // Make sure that the requested output duration matches the unit output
    // duration
    const SizeValueType numFramesOut = this->GetOutput()->GetRequestedTemporalRegion().GetFrameDuration();
    if (numFramesOut != m_UnitOutputNumberOfFrames)
    {
      itkExceptionMacro("Requested non-unit number of output frames");
    }

    // Just pass frames from the input through to the output and add debug info
    for (SizeValueType i = outputStart; i < outputStart + numFramesOut; ++i)
    {
      const DataObject::Pointer newObj = DataObject::New().GetPointer();

      // Set the output
      this->GetOutput()->SetObjectAtFrame(i, newObj);
    }

    // Set the buffered region to match the requested region
    // this->GetOutput()->SetBufferedTemporalRegion(this->GetOutput()->GetRequestedTemporalRegion());

    // Create an END entry in the stack trace
    processCallStackTraceList.emplace_back(
      m_IdNumber, CallRecord::RecordTypeEnum::END_CALL, CallRecord::MethodTypeEnum::STREAMING_GENERATE_DATA);
  }

  /** Allow the UnitInputNumberOfFrames to be set */
  void
  SetUnitInputNumberOfFrames(const SizeValueType numberOfFrames) override
  {
    itkDebugMacro("setting UnitInputNumberOfFrames to " << numberOfFrames);
    if (this->m_UnitInputNumberOfFrames != numberOfFrames)
    {
      this->m_UnitInputNumberOfFrames = numberOfFrames;
      this->Modified();
    }
  }

  /** Allow the UnitOutputNumberOfFrames to be set */
  void
  SetUnitOutputNumberOfFrames(const SizeValueType numberOfFrames) override
  {
    itkDebugMacro("setting UnitOutputNumberOfFrames to " << numberOfFrames);
    if (this->m_UnitOutputNumberOfFrames != numberOfFrames)
    {
      this->m_UnitOutputNumberOfFrames = numberOfFrames;
      this->Modified();
    }
  }

  /** GetOutput will return the output on port 0 */
  DummyTemporalDataObject::Pointer
  GetOutput()
  {
    return dynamic_cast<DummyTemporalDataObject *>(this->TemporalProcessObject::GetOutput(0));
  }

  /** SetInput will set the 0th input */
  using Superclass::SetInput;
  void
  SetInput(TemporalDataObject * tdo)
  {
    this->ProcessObject::SetNthInput(0, tdo);
  }

  /** GetInput gets the 0th input as a DummyTemporalDataObject */
  DummyTemporalDataObject::Pointer
  GetInput()
  {
    return dynamic_cast<DummyTemporalDataObject *>(this->TemporalProcessObject::GetInput(0));
  }

  /** Get/Set IdNumber */
  itkSetMacro(IdNumber, SizeValueType);
  itkGetMacro(IdNumber, SizeValueType);

  /** Provide access to m_FrameSkipPerOutput */
  void
  SetFrameSkipPerOutput(const OffsetValueType frameSkip) override
  {
    itkDebugMacro("setting FrameSkipPerOutput to " << frameSkip);
    if (this->m_FrameSkipPerOutput != frameSkip)
    {
      this->m_FrameSkipPerOutput = frameSkip;
      this->Modified();
    }
  }

  itkGetMacro(FrameSkipPerOutput, OffsetValueType);

  /** Provide access to m_InputStencilCurrentFrameIndex */
  void
  SetInputStencilCurrentFrameIndex(const SizeValueType inputStencil) override
  {
    itkDebugMacro("setting InputStencilCurrentFrameIndex to " << inputStencil);
    if (this->m_InputStencilCurrentFrameIndex != inputStencil)
    {
      this->m_InputStencilCurrentFrameIndex = inputStencil;
      this->Modified();
    }
  }
  SizeValueType
  GetInputStencilCurrentFrameIndex() override
  {
    return this->m_InputStencilCurrentFrameIndex;
  }

  // Debug overrides

  /** Override Update for debug output */
  void
  Update() override
  {
    std::cout << "(ID = " << m_IdNumber << ") - Update" << std::endl;
    Superclass::Update();
  }

  /** Override UpdateOutputData for debug output */
  void
  UpdateOutputData(DataObject * dataObj) override
  {
    std::cout << "(ID = " << m_IdNumber << ") - UpdateOutputData" << std::endl;
    Superclass::UpdateOutputData(dataObj);
  }

  /** Override GenerateData for debug output */
  void
  GenerateData() override
  {
    // Create a START entry in the stack trace
    processCallStackTraceList.emplace_back(
      m_IdNumber, CallRecord::RecordTypeEnum::START_CALL, CallRecord::MethodTypeEnum::GENERATE_DATA);

    std::cout << "*(ID = " << m_IdNumber << ") - GenerateData" << std::endl;
    Superclass::GenerateData();

    // Create an END entry in the stack trace
    processCallStackTraceList.emplace_back(
      m_IdNumber, CallRecord::RecordTypeEnum::END_CALL, CallRecord::MethodTypeEnum::GENERATE_DATA);
  }

  /** Override EnlargeOutputRequestedTemporalRegion for debug output */
  void
  EnlargeOutputRequestedTemporalRegion(TemporalDataObject * output) override
  {
    std::cout << "(ID = " << m_IdNumber << ") - EnlargeOutputRequestedTemporalRegion" << std::endl;
    Superclass::EnlargeOutputRequestedTemporalRegion(output);
  }

  /** Override GenerateInputRequestedTemporalRegion for debug output */
  void
  GenerateInputRequestedTemporalRegion() override
  {
    std::cout << "(ID = " << m_IdNumber << ") - GenerateInputRequestedTemporalRegion" << std::endl;
    Superclass::GenerateInputRequestedTemporalRegion();
  }

protected:
  /** Constructor */
  DummyTemporalProcessObject()

  {
    auto po = DummyTemporalDataObject::New();

    this->SetNthOutput(0, po.GetPointer());
  }

private:
  /** ID number used for debugging */
  SizeValueType m_IdNumber{ 0 };
};

} // namespace itk::TemporalProcessObjectTest


int
itkTemporalProcessObjectTest(int, char *[])
{

  using SizeValueType = itk::SizeValueType;
  using OffsetValueType = itk::OffsetValueType;

  // Set up pipeline

  // Create 3 new DummyTemporalProcessObjects
  using TPOType = itk::TemporalProcessObjectTest::DummyTemporalProcessObject;
  auto tpo1 = TPOType::New();
  tpo1->SetIdNumber(1);
  auto tpo2 = TPOType::New();
  tpo2->SetIdNumber(2);
  auto tpo3 = TPOType::New();
  tpo3->SetIdNumber(3);

  // Set up the Process Objects in a pipeline
  tpo2->SetInput(tpo1->GetOutput());
  tpo3->SetInput(tpo2->GetOutput());

  // Set up the Unit input/output numbers of frames
  tpo1->SetUnitInputNumberOfFrames(3);
  tpo1->SetUnitOutputNumberOfFrames(1);
  tpo2->SetUnitInputNumberOfFrames(3);
  tpo2->SetUnitOutputNumberOfFrames(3);
  tpo3->SetUnitInputNumberOfFrames(2);
  tpo3->SetUnitOutputNumberOfFrames(1);
  tpo3->SetFrameSkipPerOutput(2);
  tpo2->GetOutput()->SetNumberOfBuffers(6);

  // Set up frame stencils
  tpo1->SetInputStencilCurrentFrameIndex(1); // "current frame" centered in
                                             // group of 3
  tpo2->SetInputStencilCurrentFrameIndex(0); // "current frame" at start of
                                             // group of 3
  tpo3->SetInputStencilCurrentFrameIndex(1); // "current frame" at end of group
                                             // of 2

  // Create a new TemporalDataObject to pass through the pipeline
  using TDOType = itk::TemporalProcessObjectTest::DummyTemporalDataObject;
  auto tdo = TDOType::New();
  tpo1->SetInput(tdo);

  // Set up regions for TemporalDataObject
  itk::TemporalRegion largestRegion;
  itk::TemporalRegion requestedRegion;
  itk::TemporalRegion bufferedRegion;
  largestRegion.SetFrameStart(0);
  largestRegion.SetFrameDuration(20);
  tdo->SetLargestPossibleTemporalRegion(largestRegion);
  requestedRegion.SetFrameStart(0);
  requestedRegion.SetFrameDuration(1);
  tdo->SetRequestedTemporalRegion(requestedRegion);
  bufferedRegion.SetFrameStart(0);
  bufferedRegion.SetFrameDuration(0);
  tdo->SetBufferedTemporalRegion(bufferedRegion);

  // Fill the TemporalDataObject input with frames for the entire region
  tdo->SetBufferToXNewFrames(largestRegion.GetFrameDuration());

  // Test results of LargestTemporalRegion computation

  // Update to get largest possible temporal region information
  tpo3->UpdateOutputInformation();

  // Check largest possible temporal region after propagation
  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameDuration(), 18);
  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameStart(), 1);

  ITK_TEST_EXPECT_EQUAL(tpo2->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameDuration(), 48);
  ITK_TEST_EXPECT_EQUAL(tpo2->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameStart(), 1);

  ITK_TEST_EXPECT_EQUAL(tpo3->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameDuration(), 24);
  ITK_TEST_EXPECT_EQUAL(tpo3->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameStart(), 2);

  // Test results of requested region propagation

  // Set up requested region for the end of the pipeline
  const itk::TemporalRegion endLargestPossibleRegion = tpo3->GetOutput()->GetLargestPossibleTemporalRegion();
  itk::TemporalRegion       finalRequest;
  finalRequest.SetFrameStart(endLargestPossibleRegion.GetFrameStart());
  finalRequest.SetFrameDuration(1);
  itk::TemporalProcessObjectTest::DummyTemporalDataObject * finalOutput = tpo3->GetOutput();
  finalOutput->SetRequestedTemporalRegion(finalRequest);

  // Update to propagate the requested temporal region
  finalOutput->PropagateRequestedRegion();

  // Check requested region up the pipeline

  // for tpo3, the requested input region should be size 3 because tpo2 can
  // only output in groups of 3
  ITK_TEST_EXPECT_EQUAL(tpo3->GetInput()->GetRequestedTemporalRegion().GetFrameDuration(), 3);
  ITK_TEST_EXPECT_EQUAL(tpo3->GetInput()->GetRequestedTemporalRegion().GetFrameStart(), 3);

  // tpo2 is 3->3, so an initial request of 2 gets enlarged to 3 which results
  // in propagating a request for 3 to tpo1
  ITK_TEST_EXPECT_EQUAL(tpo2->GetInput()->GetRequestedTemporalRegion().GetFrameDuration(), 3);
  ITK_TEST_EXPECT_EQUAL(tpo2->GetInput()->GetRequestedTemporalRegion().GetFrameStart(), 3);

  // tpo1 is 3->1 and skips 1 frame for each output, so a request for 3
  // requires 5 as input
  ITK_TEST_EXPECT_EQUAL(tpo1->GetInput()->GetRequestedTemporalRegion().GetFrameDuration(), 5);
  ITK_TEST_EXPECT_EQUAL(tpo1->GetInput()->GetRequestedTemporalRegion().GetFrameStart(), 2);

  // Test Generation of data

  // Call update to execute the entire pipeline and track the call stack
  itk::TemporalProcessObjectTest::processCallStackTraceList.clear();
  tpo3->Update();

  // Print out duration of buffered output region
  const itk::TemporalProcessObjectTest::DummyTemporalDataObject::Pointer outputObject = tpo3->GetOutput();
  const OffsetValueType outputStart = outputObject->GetBufferedTemporalRegion().GetFrameStart();
  const SizeValueType   outputDuration = outputObject->GetBufferedTemporalRegion().GetFrameDuration();
  std::cout << "Buffered Output Region: " << outputStart << "->" << outputStart + outputDuration - 1 << std::endl;

  // Create a list of CallRecord items representing the correct
  // stack trace
  using RecordType = itk::TemporalProcessObjectTest::CallRecord;
  std::vector<RecordType> correctCallStack;

  // GenDat - START - obj 3
  correctCallStack.emplace_back(3, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // GenDat - START - obj 2
  correctCallStack.emplace_back(2, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // GenDat - START - obj 1
  correctCallStack.emplace_back(1, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // TempStreamGenDat - START - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - END - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - START - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - END - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - START - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - END - obj 1
  correctCallStack.emplace_back(
    1, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // GenDat - END - obj 1
  correctCallStack.emplace_back(1, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // TempStreamGenDat - START - obj 2
  correctCallStack.emplace_back(
    2, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - END - obj 2
  correctCallStack.emplace_back(
    2, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // GenDat - END - obj 2
  correctCallStack.emplace_back(2, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // TempStreamGenDat - START - obj 3
  correctCallStack.emplace_back(
    3, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // TempStreamGenDat - END - obj 3
  correctCallStack.emplace_back(
    3, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::STREAMING_GENERATE_DATA);

  // GenDat - END - obj 3
  correctCallStack.emplace_back(3, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // Check that correct number of calls made
  ITK_TEST_EXPECT_EQUAL(itk::TemporalProcessObjectTest::processCallStackTraceList.size(), correctCallStack.size());

  // Check that call lists match
  std::cout << std::endl;
  for (SizeValueType i = 0; i < itk::TemporalProcessObjectTest::processCallStackTraceList.size(); ++i)
  {
    if (itk::TemporalProcessObjectTest::processCallStackTraceList[i] != correctCallStack[i])
    {
      std::cerr << "Test failed!" << std::endl;
      std::cerr << "Error in call stack at index [" << i << "]" << std::endl;
      std::cerr << "Expected value ";
      correctCallStack[i].Print();
      std::cerr << std::endl;
      std::cerr << " differs from ";
      itk::TemporalProcessObjectTest::processCallStackTraceList[i].Print();
      return EXIT_FAILURE;
    }
  }

  // Test Generation of next output frame -- Since tpo3 skips two frames of
  // input for every frame of output and tpo2 can only generate 3 outputs at a
  // time, tpo2 must generate 6,7,8 (none of which are already buffered), so
  // the entire pipeline runs again (so the call stack should be the same).

  // Set the requested region to the next output frame
  finalRequest.SetFrameStart(finalRequest.GetFrameStart() + 1);
  finalOutput = tpo3->GetOutput();
  finalOutput->SetRequestedTemporalRegion(finalRequest);

  // Call update to execute the entire pipeline and track the call stack
  itk::TemporalProcessObjectTest::processCallStackTraceList.clear();
  tpo3->Update();

  // Check that correct number of calls made
  ITK_TEST_EXPECT_EQUAL(itk::TemporalProcessObjectTest::processCallStackTraceList.size(), correctCallStack.size());

  // Check that call lists match
  std::cout << std::endl;
  for (SizeValueType i = 0; i < itk::TemporalProcessObjectTest::processCallStackTraceList.size(); ++i)
  {
    if (itk::TemporalProcessObjectTest::processCallStackTraceList[i] != correctCallStack[i])
    {
      std::cerr << "Test failed!" << std::endl;
      std::cerr << "Error in call stack at index [" << i << "]" << std::endl;
      std::cerr << "Expected value ";
      correctCallStack[i].Print();
      std::cerr << std::endl;
      std::cerr << " differs from ";
      itk::TemporalProcessObjectTest::processCallStackTraceList[i].Print();
      return EXIT_FAILURE;
    }
  }

  // Call Update again and make sure that nothing happens except one call to
  // GenerateData at the bottom which doesn't end up needing to do anything

  itk::TemporalProcessObjectTest::processCallStackTraceList.clear();
  tpo3->Update();

  correctCallStack.clear();

  // GenDat - START - obj 3
  correctCallStack.emplace_back(3, RecordType::RecordTypeEnum::START_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // GenDat - END - obj 3
  correctCallStack.emplace_back(3, RecordType::RecordTypeEnum::END_CALL, RecordType::MethodTypeEnum::GENERATE_DATA);

  // Check that correct number of calls made
  ITK_TEST_EXPECT_EQUAL(itk::TemporalProcessObjectTest::processCallStackTraceList.size(), correctCallStack.size());

  // Check that call lists match
  std::cout << std::endl;
  for (SizeValueType i = 0; i < itk::TemporalProcessObjectTest::processCallStackTraceList.size(); ++i)
  {
    if (itk::TemporalProcessObjectTest::processCallStackTraceList[i] != correctCallStack[i])
    {
      std::cerr << "Test failed!" << std::endl;
      std::cerr << "Error in call stack at index [" << i << "]" << std::endl;
      std::cerr << "Expected value ";
      correctCallStack[i].Print();
      std::cerr << std::endl;
      std::cerr << " differs from ";
      itk::TemporalProcessObjectTest::processCallStackTraceList[i].Print();
      return EXIT_FAILURE;
    }
  }

  // Test that the requested temporal region for the output of a temporal
  // process object gets set to the largest possible temporal region if no
  // temporal region has been set

  // Reset tpo1 and the requested temporal region of tdo
  tpo1 = TPOType::New();
  const itk::TemporalRegion emptyRegion;
  tdo->SetRequestedTemporalRegion(emptyRegion);
  tpo1->SetInput(tdo);
  tpo1->UpdateOutputInformation();

  // Make sure the requested temporal region of tpo1's output is empty
  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetRequestedTemporalRegion(), emptyRegion);

  tpo1->PropagateRequestedRegion(tpo1->GetOutput());
  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetRequestedTemporalRegion(),
                        tpo1->GetOutput()->GetLargestPossibleTemporalRegion());
  ITK_TEST_EXPECT_TRUE(!(tpo1->GetOutput()->GetRequestedTemporalRegion() == emptyRegion));

  // Test that if largest possible temporal region has infinite duration,
  // request gets set to duration 1
  tpo1 = TPOType::New();
  largestRegion = tdo->GetLargestPossibleTemporalRegion();
  largestRegion.SetFrameDuration(ITK_INFINITE_FRAME_DURATION);
  tdo->SetLargestPossibleTemporalRegion(largestRegion);
  tpo1->SetInput(tdo);
  tpo1->UpdateOutputInformation();
  tpo1->PropagateRequestedRegion(tpo1->GetOutput());

  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetLargestPossibleTemporalRegion().GetFrameDuration(),
                        ITK_INFINITE_FRAME_DURATION);
  ITK_TEST_EXPECT_EQUAL(tpo1->GetOutput()->GetRequestedTemporalRegion().GetFrameDuration(), 1);

  // Test streaming enumeration for CallRecordEnums::RecordType elements
  const std::set<itk::TemporalProcessObjectTest::CallRecordEnums::RecordType> allRecordType{
    itk::TemporalProcessObjectTest::CallRecordEnums::RecordType::START_CALL,
    itk::TemporalProcessObjectTest::CallRecordEnums::RecordType::END_CALL,
    itk::TemporalProcessObjectTest::CallRecordEnums::RecordType::MAX_RECORD_TYPE
  };
  for (const auto & ee : allRecordType)
  {
    std::cout << "STREAMED ENUM VALUE CallRecordEnums::RecordType: " << ee << std::endl;
  }

  // Test streaming itk::TemporalProcessObjectTest::CallRecordEnums::MethodType elements
  const std::set<itk::TemporalProcessObjectTest::CallRecordEnums::MethodType> allMethodType{
    itk::TemporalProcessObjectTest::CallRecordEnums::MethodType::GENERATE_DATA,
    itk::TemporalProcessObjectTest::CallRecordEnums::MethodType::STREAMING_GENERATE_DATA,
    itk::TemporalProcessObjectTest::CallRecordEnums::MethodType::MAX_METHOD_TYPE
  };
  for (const auto & ee : allMethodType)
  {
    std::cout << "STREAMED ENUM VALUE CallRecordEnums::MethodType: " << ee << std::endl;
  }


  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
