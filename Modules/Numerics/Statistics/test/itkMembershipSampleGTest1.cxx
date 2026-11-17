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
#include "itkGTest.h"
#include "itkMembershipSample.h"

// MembershipSample test using FixedArray type measurement vector
TEST(MembershipSample, ConvertedLegacyTest1)
{

  constexpr unsigned int MeasurementVectorSize{ 3 };

  constexpr unsigned int numberOfClasses1{ 2 };

  using MeasurementVectorType = itk::FixedArray<float, MeasurementVectorSize>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using MembershipSampleType = itk::Statistics::MembershipSample<SampleType>;

  auto sample = SampleType::New();


  auto membershipSample = MembershipSampleType::New();

  membershipSample->SetSample(sample);

  EXPECT_EQ(membershipSample->GetSample(), sample) << "SetSample() / GetSample() failed";

  membershipSample->SetNumberOfClasses(numberOfClasses1);
  EXPECT_EQ(membershipSample->GetNumberOfClasses(), numberOfClasses1)
    << "SetNumberOfClasses() / GetNumberOfClasses() 1 failed";

  // Exercise the Print() method
  membershipSample->Print(std::cout);

  // Add measurement vectors to the list sample
  constexpr unsigned int sampleSize{ 10 };
  MeasurementVectorType  mv;

  std::cout << "Sample length = " << sample->GetMeasurementVectorSize() << std::endl;
  std::cout << "Vector length = " << itk::NumericTraits<MeasurementVectorType>::GetLength(mv) << std::endl;

  for (unsigned int i = 0; i < sampleSize; ++i)
  {
    for (unsigned int j = 0; j < MeasurementVectorSize; ++j)
    {
      mv[j] = rand() / (RAND_MAX + 1.0);
    }
    sample->PushBack(mv);
  }

  // Add instances to the membership sample
  const SampleType::ConstIterator begin = sample->Begin();
  const SampleType::ConstIterator end = sample->End();

  SampleType::ConstIterator iter = begin;

  MembershipSampleType::ClassLabelType classLabel = 0;

  unsigned int sampleCounter = 0;

  while (iter != end)
  {
    if (sampleCounter >= 5)
    {
      classLabel = 1;
    }
    const SampleType::InstanceIdentifier id = iter.GetInstanceIdentifier();
    membershipSample->AddInstance(classLabel, id);
    ++iter;
    ++sampleCounter;
  }

  // iterator tests
  //

  std::cerr << "Iterators..." << std::endl;
  sampleCounter = 0;
  {
    using IteratorType = MembershipSampleType::Iterator;

    IteratorType s_iter = membershipSample->Begin();

    const IteratorType bs_iter(s_iter);
    EXPECT_EQ(bs_iter, s_iter) << "Iterator::Copy Constructor failed";

    IteratorType assignment_iter(bs_iter);
    assignment_iter = s_iter;
    EXPECT_EQ(assignment_iter, s_iter) << "Iterator::assignment operator failed";

    MembershipSampleType::InstanceIdentifier id = 0;
    while (s_iter != membershipSample->End())
    {
      EXPECT_EQ(membershipSample->GetMeasurementVector(id), s_iter.GetMeasurementVector())
        << "Iterator::GetMeasurementVector (forward) failed";
      EXPECT_EQ(id, s_iter.GetInstanceIdentifier()) << "Iterator::GetInstanceIdentifier (forward) failed";
      EXPECT_EQ(s_iter.GetFrequency(), 1u) << "Iterator::GetFrequency (forward) failed";
      EXPECT_EQ(sample->GetFrequency(id), 1u) << "GetFrequency (forward) failed";
      if (sampleCounter < 5)
      {
        EXPECT_EQ(s_iter.GetClassLabel(), 0u) << "GetClassLabel failed";
      }
      else
      {
        EXPECT_EQ(s_iter.GetClassLabel(), 1u) << "GetClassLabel failed";
      }

      ++id;
      ++s_iter;
      ++sampleCounter;
    }

    EXPECT_EQ(s_iter, membershipSample->End()) << "Iterator::End (forward) failed";
  }

  // ConstIterator test
  std::cerr << "Const Iterators..." << std::endl;
  {
    // forward iterator
    using ConstIteratorType = MembershipSampleType::ConstIterator;
    ConstIteratorType s_iter = membershipSample->Begin();

    // copy constructor
    const ConstIteratorType bs_iter(s_iter);
    EXPECT_EQ(bs_iter, s_iter) << "Iterator::Copy Constructor (from const) failed";

    // assignment operator
    ConstIteratorType assignment_iter(bs_iter);
    assignment_iter = s_iter;
    EXPECT_EQ(assignment_iter, s_iter) << "Const Iterator::operator= () failed";

    // copy from non-const iterator
    const MembershipSampleType::Iterator nonconst_iter = membershipSample->Begin();
    MembershipSampleType::ConstIterator  s2_iter(nonconst_iter);
    EXPECT_EQ(s2_iter, s_iter) << "Iterator::Copy Constructor (from non-const) failed";
    // assignment from non-const iterator
    s2_iter = nonconst_iter;
    EXPECT_EQ(s2_iter, s_iter) << "Iterator::assignment (from non-const) failed";

    MembershipSampleType::InstanceIdentifier id = 0;
    while (s_iter != membershipSample->End())
    {
      EXPECT_EQ(membershipSample->GetMeasurementVector(id), s_iter.GetMeasurementVector())
        << "Iterator::GetMeasurementVector (forward) failed";
      EXPECT_EQ(id, s_iter.GetInstanceIdentifier()) << "Iterator::GetInstanceIdentifier (forward) failed";
      EXPECT_EQ(s_iter.GetFrequency(), 1u) << "Iterator::GetFrequency (forward) failed";
      ++id;
      ++s_iter;
    }

    EXPECT_EQ(s_iter, membershipSample->End()) << "Iterator::End (forward) failed";
  }
}
