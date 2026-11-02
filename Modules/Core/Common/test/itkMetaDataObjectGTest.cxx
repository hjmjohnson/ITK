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

#include "itkMetaDataObject.h"
#include "itkImage.h"
#include "itkMath.h"
#include "itkGTest.h"

namespace
{
template <typename TMetaData>
void
testMetaData(const TMetaData & value)
{
  using MetaDataType = TMetaData;

  using MetaDataObjectType = itk::MetaDataObject<MetaDataType>;

  auto metaDataObject = MetaDataObjectType::New();

  // Not ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS: Print() of a default std::string value is empty.
  metaDataObject->Print(std::cout);
  EXPECT_STREQ(metaDataObject->GetNameOfClass(), "MetaDataObject");
  EXPECT_STREQ(metaDataObject->Superclass::GetNameOfClass(), "MetaDataObjectBase");


  metaDataObject->SetMetaDataObjectValue(value);
  EXPECT_EQ(metaDataObject->GetMetaDataObjectValue(), value) << "Set value does not equal original value!";

  std::cout << "The metadata's type name is: " << metaDataObject->GetMetaDataObjectTypeName() << std::endl;
  std::cout << "The metadata object: " << std::endl;
  metaDataObject->Print(std::cout);

  std::cout << std::endl << std::endl;
}
} // namespace

TEST(MetaDataObject, ConvertedLegacyTest)
{
  testMetaData<unsigned char>(24);
  testMetaData<char>(-24);
  testMetaData<unsigned short>(24);
  testMetaData<short>(-24);
  testMetaData<unsigned int>(24);
  testMetaData<int>(-24);
  testMetaData<unsigned long>(24);
  testMetaData<long>(-24);
  testMetaData<unsigned long long>(24);
  testMetaData<long long>(-24);
  testMetaData<float>(-24);
  testMetaData<double>(-24);
  testMetaData<std::string>("I T K");
  testMetaData<std::vector<double>>({ 1.0, 2.0, 3.0 });
  testMetaData<std::vector<std::vector<double>>>({ { 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 } });
  testMetaData(itk::Array<char>(3, 'I'));
  testMetaData<itk::Array<double>>(itk::Array<double>(3, 3.0));
  testMetaData(itk::Matrix<float, 4, 4>());
  testMetaData<itk::Matrix<double, 3, 3>>(itk::Matrix<double, 3, 3>::GetIdentity());
  using ImageType = itk::Image<unsigned short, 3>;
  const ImageType::Pointer image = nullptr;
  testMetaData<ImageType::Pointer>(image);
}
