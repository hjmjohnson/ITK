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
#include "itkSubsample.h"
#include "itkGTest.h"

TEST(Subsample, ConvertedLegacyTest2)
{
  std::cout << "Subsample Test \n \n";

  using MeasurementVectorType = itk::Array<float>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  constexpr SampleType::MeasurementVectorSizeType measurementVectorSize{ 3 };
  std::cerr << "Measurement vector size: " << measurementVectorSize << std::endl;

  constexpr unsigned int sampleSize{ 10 };

  auto sample = SampleType::New();

  sample->SetMeasurementVectorSize(measurementVectorSize);

  MeasurementVectorType mv(measurementVectorSize);
  for (unsigned int i = 0; i < sampleSize; ++i)
  {
    for (unsigned int j = 0; j < measurementVectorSize; ++j)
    {
      mv[j] = j + i * measurementVectorSize;
    }
    std::cout << "Adding measurement vector: " << mv << std::endl;
    sample->PushBack(mv);
  }

  // tests begin
  using SubsampleType = itk::Statistics::Subsample<SampleType>;
  auto subSample = SubsampleType::New();
  subSample->SetSample(sample);

  // Add measurement vectors in sample with even id number to subSample
  for (unsigned int i = 0; i < sample->Size(); i = i + 2)
  {
    subSample->AddInstance(i);
    std::cout << "Adding instance: " << i << " to subSample" << std::endl;
  }

  EXPECT_EQ(subSample->Size(), 5u) << "Size of the subsample container should be 5";

  for (unsigned int i = 0; i < subSample->Size(); ++i)
  {
    std::cout << "Measurement Vector: " << i << '\t' << subSample->GetMeasurementVector(i) << std::endl;

    EXPECT_EQ(subSample->GetMeasurementVector(i), sample->GetMeasurementVector(i * 2))
      << "Subsampling is not correctly done!";
  }

  using CascadedSubsampleType = itk::Statistics::Subsample<SubsampleType>;
  auto subSample2 = CascadedSubsampleType::New();
  subSample2->SetSample(subSample);

  // Add measurement vectors in subsample with even id number to subSample2
  for (unsigned int i = 0; i < subSample->Size(); i = i + 2)
  {
    std::cout << "Adding instance: " << i << " to subSample2" << std::endl;
    subSample2->AddInstance(i);
  }

  EXPECT_EQ(subSample2->Size(), 3u) << "Size of the subsample2 container should be 3";

  subSample2->Swap(0, 2);

  // swap back
  subSample2->Swap(2, 0);

  for (unsigned int i = 0; i < subSample2->Size(); ++i)
  {
    std::cout << "Measurement Vector: " << i << '\t' << subSample2->GetMeasurementVector(i) << std::endl;

    EXPECT_EQ(subSample2->GetMeasurementVector(i), sample->GetMeasurementVector(i * 4))
      << "Subsampling of a subsample is not correctly done!";
  }

  std::cout << subSample2->GetSample() << std::endl;

  using IteratorType = CascadedSubsampleType::Iterator;

  IteratorType iter = subSample2->Begin();
  while (iter != subSample2->End())
  {
    std::cout << iter.GetInstanceIdentifier() << ' ';
    std::cout << iter.GetMeasurementVector() << ' ';
    std::cout << iter.GetFrequency() << std::endl;
    ++iter;
  }

  using ConstIteratorType = CascadedSubsampleType::ConstIterator;

  IteratorType citer = subSample2->Begin();
  while (citer != subSample2->End())
  {
    std::cout << citer.GetInstanceIdentifier() << ' ';
    std::cout << citer.GetMeasurementVector() << ' ';
    std::cout << citer.GetFrequency() << std::endl;
    ++citer;
  }

  const IteratorType iter1 = subSample2->Begin();
  const IteratorType iter2 = subSample2->Begin();

  citer = iter1;

  EXPECT_EQ(citer, iter1) << "Error in iterator != operator ";


  EXPECT_EQ(citer, iter1) << "Error in iterator == operator ";


  EXPECT_EQ(iter1, iter2) << "Error in iterator != operator ";


  EXPECT_EQ(iter1, iter2) << "Error in iterator == operator ";


  //
  // Additional iterator tests
  //

  // Testing methods specific to Iterators
  {
    const IteratorType iter7 = subSample2->Begin();
    IteratorType       iter8 = subSample2->End();

    iter8 = iter7;
    EXPECT_EQ(iter8, iter7) << "Iterator operator=() failed";

    IteratorType iter3 = subSample2->Begin();
    EXPECT_EQ(iter3, subSample2->Begin()) << "Iterator constructor from sample failed";

    unsigned int counter = 0;
    while (iter3 != subSample2->End())
    {
      ++iter3;
      counter++;
    }

    EXPECT_EQ(counter, subSample2->Size()) << "Iterator walk failed";

    const IteratorType iter4(iter8);
    EXPECT_EQ(iter4, iter8) << "Iterator copy constructor failed";

    const IteratorType iter5 = iter8;
    EXPECT_EQ(iter5, iter8) << "Iterator operator= failed";

    IteratorType           iter6(subSample2);
    constexpr unsigned int targetEntry{ 2 };
    for (unsigned int kk = 0; kk < targetEntry; ++kk)
    {
      std::cout << "GetInstanceIdentifier() = " << iter6.GetInstanceIdentifier() << std::endl;
      ++iter6;
    }

    EXPECT_EQ(iter6.GetInstanceIdentifier(), targetEntry) << "Iterator Constructor with instance identifier failed";
  }

  // Testing methods specific to ConstIterators
  {
    const ConstIteratorType iter11 = subSample2->Begin();
    ConstIteratorType       iter12 = subSample2->End();

    iter12 = iter11;

    EXPECT_EQ(iter12, iter11) << "ConstIterator operator!=() or operator=() failed";

    EXPECT_EQ(iter12, iter11) << "ConstIterator operator==() failed";

    const ConstIteratorType iter3(iter12);
    EXPECT_EQ(iter3, iter12) << "ConstIterator copy constructor failed";

    const CascadedSubsampleType * constSample = subSample2.GetPointer();

    const ConstIteratorType iter4(constSample->Begin());
    const ConstIteratorType iter5(subSample2->Begin());
    EXPECT_EQ(iter4, iter5) << "Constructor from const container Begin() differs from non-const Begin() ";

    const ConstIteratorType iter6(constSample);
    const ConstIteratorType iter7(subSample2);
    EXPECT_EQ(iter6, iter7) << "ConstIterator Constructor from const container differs from non-const container";

    const ConstIteratorType iter8(subSample2);
    EXPECT_EQ(iter8.GetInstanceIdentifier(), 0u) << "Constructor with instance identifier 0 failed";


    ConstIteratorType      iter9(subSample2);
    constexpr unsigned int targetEntry{ 2 };
    for (unsigned int kk = 0; kk < targetEntry; ++kk)
    {
      std::cout << "Instance identifier = " << iter9.GetInstanceIdentifier() << std::endl;
      ++iter9;
    }

    std::cout << "Instance identifier = " << iter9.GetInstanceIdentifier() << std::endl;
    MeasurementVectorType vector9a = iter9.GetMeasurementVector();
    MeasurementVectorType vector9b = subSample2->GetMeasurementVector(targetEntry);
    for (unsigned int kitr = 0; kitr < measurementVectorSize; ++kitr)
    {
      EXPECT_EQ(vector9b[kitr], vector9a[kitr]) << "Constructor with container followed by increments failed";
    }

    unsigned int      counter = 0;
    ConstIteratorType iter10(constSample);
    EXPECT_EQ(iter10, constSample->Begin()) << "ConstIterator constructor from sample failed";


    while (iter10 != constSample->End())
    {
      ++iter10;
      counter++;
    }

    EXPECT_EQ(counter, constSample->Size()) << "Iterator walk failed";
  }
}
