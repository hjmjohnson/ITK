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

#include "itkMixtureModelComponentBase.h"
#include "itkListSample.h"
#include "itkTestingMacros.h"

namespace itk
{
namespace Statistics
{

template <typename TSample>
class MixtureModelComponentBaseTestHelper : public MixtureModelComponentBase<TSample>
{
public:
  using Self = MixtureModelComponentBaseTestHelper;
  using Superclass = MixtureModelComponentBase<TSample>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  itkOverrideGetNameOfClassMacro(MixtureModelComponentBaseTestHelper);

  itkNewMacro(Self);

  void
  RunTests()
  {
    std::cout << "Superclass Name " << this->Superclass::GetNameOfClass() << '\n';
    std::cout << "This class Name " << this->GetNameOfClass() << '\n';

    this->Superclass::Print(std::cout);
    this->Print(std::cout);

    std::cout << "Full Parameters = " << this->Superclass::GetFullParameters() << '\n';
    std::cout << "Minimal change  = " << this->Superclass::GetMinimalParametersChange() << '\n';
  }

protected:
  void
  GenerateData() override
  {
    std::cout << "Executing GenerateData() " << '\n';
  }
};

} // namespace Statistics
} // namespace itk

int
itkMixtureModelComponentBaseTest(int, char *[])
{
  using MeasurementVectorType = itk::Array<double>;
  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using ComponentType = itk::Statistics::MixtureModelComponentBaseTestHelper<SampleType>;

  auto component = ComponentType::New();
  std::cout << "component->GetWeights(): " << component->GetWeights() << '\n';
  component->RunTests();

  ITK_TRY_EXPECT_EXCEPTION(component->GetWeight(5));

  std::cerr << "[PASSED]" << '\n';
  return EXIT_SUCCESS;
}
