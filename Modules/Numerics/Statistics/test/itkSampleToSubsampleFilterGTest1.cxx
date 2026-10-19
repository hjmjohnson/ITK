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
#include "itkSampleToSubsampleFilter.h"
#include "itkGTest.h"

namespace
{

template <typename TSample>
class SubsamplerTester : public itk::Statistics::SampleToSubsampleFilter<TSample>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(SubsamplerTester);

  /** Standard class type aliases. */
  using Self = SubsamplerTester;
  using Superclass = itk::Statistics::SampleToSubsampleFilter<TSample>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(SubsamplerTester);
  itkNewMacro(Self);

protected:
  SubsamplerTester() = default;
  ~SubsamplerTester() override = default;
  void
  PrintSelf(std::ostream & os, itk::Indent indent) const override
  {
    this->Superclass::PrintSelf(os, indent);
    os << "Superclass = " << this->Superclass::GetNameOfClass() << std::endl;
  }

  void
  GenerateData() override
  {}
};

} // namespace


TEST(SampleToSubsampleFilter, ConvertedLegacyTest1)
{

  constexpr unsigned int MeasurementVectorSize{ 17 };

  using MeasurementVectorType = itk::FixedArray<float, MeasurementVectorSize>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using FilterType = SubsamplerTester<SampleType>;


  auto sample = SampleType::New();

  auto filter = FilterType::New();

  // Test GetInput() before setting the input
  EXPECT_EQ(filter->GetInput(), nullptr) << "GetInput() should have returned nullptr";

  // Test GetOutput() before creating the output
  EXPECT_NE(filter->GetOutput(), nullptr) << "GetOutput() should have returned NON-nullptr";

  filter->SetInput(sample);

  EXPECT_EQ(filter->GetInput(), sample.GetPointer()) << "GetInput() didn't matched SetInput()";


  //
  // Exercise the Print() method
  //
  filter->Print(std::cout);


  filter->Update();


  // Exercise the GetNameOfClass() method in the
  // SampleToSubsampleFilter:
  std::cout << "Classname  " << filter->GetNameOfClass() << std::endl;
  std::cout << "Superclass " << filter->FilterType::Superclass::GetNameOfClass() << std::endl;
}
