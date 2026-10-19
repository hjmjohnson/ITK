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
#include "itkMembershipFunctionBase.h"
#include "itkGTest.h"

namespace
{

template <typename TMeasurementVector>
class MyMembershipFunctionBase : public itk::Statistics::MembershipFunctionBase<TMeasurementVector>
{
public:
  /** Standard class type alias. */
  using Self = MyMembershipFunctionBase;

  using Superclass = itk::Statistics::MembershipFunctionBase<TMeasurementVector>;

  using Pointer = itk::SmartPointer<Self>;

  using ConstPointer = itk::SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(MyMembershipFunctionBase);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Evaluate membership score */
  double
  Evaluate(const TMeasurementVector &) const override
  {
    constexpr double score{ 1 };
    return score;
  }
};

} // namespace


/* Test MembershipFunctionBase using a resizable vector type */
TEST(MembershipFunctionBase, ConvertedLegacyTest2)
{

  constexpr unsigned int MeasurementVectorSize{ 3 };

  using MeasurementVectorType = itk::Array<float>;

  using MembershipFunctionBaseType = MyMembershipFunctionBase<MeasurementVectorType>;

  auto function = MembershipFunctionBaseType::New();

  std::cout << function->GetNameOfClass() << std::endl;
  std::cout << function->MembershipFunctionBaseType::Superclass::GetNameOfClass() << std::endl;

  function->Print(std::cout);

  function->SetMeasurementVectorSize(MeasurementVectorSize);
  EXPECT_EQ(function->GetMeasurementVectorSize(), MeasurementVectorSize) << "Set/GetMeasurementVectorSize() Failed !";

  // Test if it is possible to reset the vector size
  function->SetMeasurementVectorSize(MeasurementVectorSize);
  EXPECT_EQ(function->GetMeasurementVectorSize(), MeasurementVectorSize) << "Set/GetMeasurementVectorSize() Failed !";

  // test if it is possible to change the measurement vector size
  constexpr MembershipFunctionBaseType::MeasurementVectorSizeType newSize{ 5 };
  function->SetMeasurementVectorSize(newSize); // for code coverage

  EXPECT_EQ(function->GetMeasurementVectorSize(), newSize) << "Set/GetMeasurementVectorSize() Failed !";
}
