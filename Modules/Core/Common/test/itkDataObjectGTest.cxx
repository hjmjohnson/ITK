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

#include "itkDataObject.h"
#include "itkRealTimeClock.h"
#include "itkGTest.h"

namespace
{

class DataObjectTestHelper : public itk::DataObject
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(DataObjectTestHelper);

  /** Standard type alias. */
  using Self = DataObjectTestHelper;
  using Superclass = itk::DataObject;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(DataObjectTestHelper);

protected:
  DataObjectTestHelper() = default;
  ~DataObjectTestHelper() override = default;
  void
  PrintSelf(std::ostream & os, itk::Indent indent) const override
  {
    this->Superclass::PrintSelf(os, indent);
  }
};

} // namespace

TEST(DataObject, ConvertedLegacyTest)
{
  const DataObjectTestHelper::Pointer dataObject = DataObjectTestHelper::New();

  const itk::RealTimeClock::Pointer clock = itk::RealTimeClock::New();
  dataObject->SetRealTimeStamp(clock->GetRealTimeStamp());
  const itk::RealTimeStamp timeStamp = dataObject->GetRealTimeStamp();
  dataObject->DataHasBeenGenerated();
  EXPECT_EQ(timeStamp, dataObject->GetRealTimeStamp());
}
