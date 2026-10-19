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


#include <fstream>

#include "itkPointSetToListSampleAdaptor.h"
#include "itkGTest.h"

TEST(PointSetToListSampleAdaptor, ConvertedLegacyTest)
{
  using PointSetType = itk::PointSet<double, 3>;
  using PointSetToListSampleAdaptorType = itk::Statistics::PointSetToListSampleAdaptor<PointSetType>;

  auto                    pointSet = PointSetType::New();
  PointSetType::PointType point;

  constexpr unsigned int numberOfPoints{ 10 };
  for (unsigned int i = 0; i < numberOfPoints; ++i)
  {
    point[0] = i * 3;
    point[1] = i * 3 + 1;
    point[2] = i * 3 + 2;
    pointSet->SetPoint(i, point);
  }

  auto listSample = PointSetToListSampleAdaptorType::New();

  // Test if the methods throw exceptions if invoked before setting the pointset
  EXPECT_THROW(listSample->Size(), itk::ExceptionObject);
  EXPECT_THROW(listSample->GetTotalFrequency(), itk::ExceptionObject);
  EXPECT_THROW(listSample->GetMeasurementVector(0), itk::ExceptionObject);
  EXPECT_THROW(listSample->GetPointSet(), itk::ExceptionObject);
  EXPECT_THROW(listSample->GetFrequency(0), itk::ExceptionObject);

  listSample->SetPointSet(pointSet);

  // exercise returned pointset
  const PointSetToListSampleAdaptorType::PointSetType * pointSetReturned = listSample->GetPointSet();

  // check for nullptr
  EXPECT_NE(pointSetReturned, nullptr) << "GetPointSet() returned a nullptr pointer";

  // check size
  EXPECT_EQ(numberOfPoints, listSample->Size()) << "Size() is not returning the correct size";

  // check frequency
  EXPECT_EQ(listSample->GetFrequency(0), 1u) << "GetFrequency() is not returning the correct frequency";

  // check frequency
  EXPECT_EQ(numberOfPoints, listSample->GetTotalFrequency())
    << "GetTotalFrequency() is not returning the correct frequency";


  listSample->Print(std::cout);

  for (unsigned int i = 0; i < numberOfPoints; ++i)
  {
    const PointSetToListSampleAdaptorType::InstanceIdentifier id = i;
    PointSetType::PointType                                   tempPointSet(0.0);
    pointSet->GetPoint(i, &tempPointSet);

    EXPECT_EQ(listSample->GetMeasurementVector(id), tempPointSet) << "Error in point set accessed by the adaptor";
  }

  // Test the iterators
  std::cerr << "Iterators..." << std::endl;
  {
    // forward iterator
    using IteratorType = PointSetToListSampleAdaptorType::Iterator;

    IteratorType s_iter = listSample->Begin();

    // copy constructor
    const IteratorType bs_iter(s_iter);
    EXPECT_EQ(bs_iter, s_iter) << "Iterator::Copy Constructor failed";

    // assignment operator
    IteratorType assignment_iter(bs_iter);
    assignment_iter = s_iter;
    EXPECT_EQ(assignment_iter, s_iter) << "Iterator::assignment operator failed";

    PointSetToListSampleAdaptorType::InstanceIdentifier id = 0;
    while (s_iter != listSample->End())
    {
      EXPECT_EQ(listSample->GetMeasurementVector(id), s_iter.GetMeasurementVector())
        << "Iterator::GetMeasurementVector (forward) failed";
      EXPECT_EQ(id, s_iter.GetInstanceIdentifier()) << "Iterator::GetInstanceIdentifier (forward) failed";
      EXPECT_EQ(s_iter.GetFrequency(), 1u) << "Iterator::GetFrequency (forward) failed";
      EXPECT_EQ(listSample->GetFrequency(id), 1u) << "GetFrequency (forward) failed";
      ++id;
      ++s_iter;
    }

    EXPECT_EQ(s_iter, listSample->End()) << "Iterator::End (forward) failed";
  }

  std::cerr << "Const Iterators..." << std::endl;
  {
    // forward iterator
    using ConstIteratorType = PointSetToListSampleAdaptorType::ConstIterator;

    ConstIteratorType s_iter = listSample->Begin();

    // copy constructor
    const ConstIteratorType bs_iter(s_iter);
    EXPECT_EQ(bs_iter, s_iter) << "Iterator::Copy Constructor (from const) failed";

    // assignment operator
    ConstIteratorType assignment_iter(bs_iter);
    assignment_iter = s_iter;
    EXPECT_EQ(assignment_iter, s_iter) << "Const Iterator::operator= () failed";

    // copy from non-const iterator
    const PointSetToListSampleAdaptorType::Iterator nonconst_iter = listSample->Begin();
    PointSetToListSampleAdaptorType::ConstIterator  s2_iter(nonconst_iter);
    EXPECT_EQ(s2_iter, s_iter) << "Iterator::Copy Constructor (from non-const) failed";

    // assignment from non-const iterator
    s2_iter = nonconst_iter;
    EXPECT_EQ(s2_iter, s_iter) << "Iterator::assignment (from non-const) failed";

    PointSetToListSampleAdaptorType::InstanceIdentifier id = 0;
    while (s_iter != listSample->End())
    {
      EXPECT_EQ(listSample->GetMeasurementVector(id), s_iter.GetMeasurementVector())
        << "Iterator::GetMeasurementVector (forward) failed";
      EXPECT_EQ(id, s_iter.GetInstanceIdentifier()) << "Iterator::GetInstanceIdentifier (forward) failed";
      EXPECT_EQ(s_iter.GetFrequency(), 1u) << "Iterator::GetFrequency (forward) failed";
      ++id;
      ++s_iter;
    }

    EXPECT_EQ(s_iter, listSample->End()) << "Iterator::End (forward) failed";
  }
}
