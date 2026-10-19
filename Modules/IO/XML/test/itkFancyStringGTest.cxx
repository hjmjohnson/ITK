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

/*
This program tests operations of itk::FancyString.
*/

#include "itkFancyString.h"
#include "itkGTest.h"

#include <iostream>
#include "itkMacro.h"
#include "itkMath.h"

namespace
{
void
testFancyStringWithBasicType();

void
testFancyStringWithStdVector();

void
testFancyStringWithItkArray();

void
testFancyStringForStringOperations();

void
testFancyStringUnequalOperator();

void
testFancyStringEqualOperator();
} // namespace


TEST(FancyString, ConvertedLegacyTest)
{
  ASSERT_NO_THROW(testFancyStringWithBasicType());

  ASSERT_NO_THROW(testFancyStringWithStdVector());

  ASSERT_NO_THROW(testFancyStringWithItkArray());

  ASSERT_NO_THROW(testFancyStringForStringOperations());

  ASSERT_NO_THROW(testFancyStringUnequalOperator());

  ASSERT_NO_THROW(testFancyStringEqualOperator());


  std::cout << "Test finished." << std::endl;
}

namespace
{
// test for basic data type
void
testFancyStringWithBasicType()
{
  // for unsigned char
  {
    using DataType = unsigned char;

    itk::FancyString s;

    // write out
    constexpr DataType dataIn{ '*' };
    s << dataIn;

    // read back
    DataType dataOut = ' ';
    s >> dataOut;

    // check result
    EXPECT_EQ(dataIn, dataOut) << "uchar: input and output data do not match";

    std::cout << "testFancyStringWithBasicType: uchar OK!" << std::endl;
  }

  // for short
  {
    using DataType = short;

    itk::FancyString s;

    // write out
    constexpr DataType dataIn{ -1024 };
    s << dataIn;

    // read back
    DataType dataOut = 0;
    s >> dataOut;

    // check result
    EXPECT_EQ(dataIn, dataOut) << "short: input and output data do not match";

    std::cout << "testFancyStringWithBasicType: short OK!" << std::endl;
  }

  // for double
  {
    using DataType = double;

    itk::FancyString s;

    // write out
    constexpr DataType dataIn{ -0.1 };
    s << dataIn;

    // read back
    DataType dataOut = 0.0;
    s >> dataOut;

    // check result
    EXPECT_EQ(dataIn, dataOut) << "double: input and output data do not match";

    std::cout << "testFancyStringWithBasicType: double OK!" << std::endl;
  }

  // all testings were successful if reached here
}

// test for std::vector<T>
void
testFancyStringWithStdVector()
{
  itk::FancyString svalue;

  std::vector<float> dataIn(10, -0.1f);
  svalue << dataIn;
  // add one more data element to the end of the string
  svalue.Append(" 10 ");

  // read all data elements in the string
  std::vector<float> dataOut1;
  itk::FancyString   s = svalue;
  s.ToData(dataOut1);
  // check successful or not
  EXPECT_FALSE(dataOut1.size() != (dataIn.size() + 1) || dataOut1.back() != 10.0f)
    << "testFancyStringWithStdVector: failed reading all elements in the string (1)";
  for (size_t i = 0; i < dataIn.size(); ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut1[i]) << "testFancyStringWithStdVector: failed reading all elements in the string (2)";
  }
  std::cout << "testFancyStringWithStdVector: dataOut1 OK!" << std::endl;

  // read all data elements for the output vector
  std::vector<float> dataOut2(5, 0.0f);
  s = svalue;
  s >> dataOut2;
  // check successful or not
  EXPECT_EQ(dataOut2.size(), 5u)
    << "testFancyStringWithStdVector: failed reading all elements for the output vector (1)";
  for (size_t i = 0; i < dataOut2.size(); ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut2[i])
      << "testFancyStringWithStdVector: failed reading all elements for the output vector (2)";
  }
  std::cout << "testFancyStringWithStdVector: dataOut2 OK!" << std::endl;

  // read user-specified number of data elements (output data exist)
  std::vector<float> dataOut3(10, 0.0f);
  s = svalue;
  s.ToData(dataOut3, 5);
  // check successful or not
  EXPECT_FALSE(dataOut3.size() != 10 || dataOut3[5] != 0.0f)
    << "testFancyStringWithStdVector: failed reading user-specified number of elements (1.1)";
  for (size_t i = 0; i < 5; ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut3[i])
      << "testFancyStringWithStdVector: failed reading user-specified number of elements (1.2)";
  }
  std::cout << "testFancyStringWithStdVector: dataOut3 OK!" << std::endl;

  // read user-specified number of data elements (output data do not exist)
  std::vector<float> dataOut4;
  s = svalue;
  s.ToData(dataOut4, 5);
  // check successful or not
  ASSERT_EQ(dataOut4.size(), 5u)
    << "testFancyStringWithStdVector: failed reading user-specified number of elements (2.1)";
  for (size_t i = 0; i < 5; ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut4[i])
      << "testFancyStringWithStdVector: failed reading user-specified number of elements (2.2)";
  }
  std::cout << "testFancyStringWithStdVector: dataOut4 OK!" << std::endl;

  // all testings were successful if reached here
}

// test for itk::Array<T>
void
testFancyStringWithItkArray()
{
  using DataType = itk::Array<double>;

  itk::FancyString svalue;

  DataType dataIn(10, -0.1);
  svalue << dataIn;
  // add one more data element to the end of the string
  svalue.Append(" 10 ");

  // read all data elements in the string
  DataType         dataOut1;
  itk::FancyString s = svalue;
  s.ToData(dataOut1);
  // check successful or not
  EXPECT_FALSE(dataOut1.GetSize() != (dataIn.GetSize() + 1) || dataOut1[10] != 10.0)
    << "testFancyStringWithItkArray: failed reading all elements in the string (1)";
  for (unsigned int i = 0; i < dataIn.GetSize(); ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut1[i]) << "testFancyStringWithItkArray: failed reading all elements in the string (2)";
  }
  std::cout << "testFancyStringWithItkArray: dataOut1 OK!" << std::endl;

  // read all data elements for the output vector
  DataType dataOut2(5, 0.0);
  s = svalue;
  s >> dataOut2;
  // check successful or not
  EXPECT_EQ(dataOut2.GetSize(), 5u)
    << "testFancyStringWithItkArray: failed reading all elements for the output vector (1)";
  for (unsigned int i = 0; i < dataOut2.GetSize(); ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut2[i])
      << "testFancyStringWithItkArray: failed reading all elements for the output vector (2)";
  }
  std::cout << "testFancyStringWithItkArray: dataOut2 OK!" << std::endl;

  // read user-specified number of data elements (output data exist)
  DataType dataOut3(10, 0.0);
  s = svalue;
  s.ToData(dataOut3, 5);
  // check successful or not
  EXPECT_FALSE(dataOut3.GetSize() != 10 || dataOut3[5] != 0.0)
    << "testFancyStringWithItkArray: failed reading user-specified number of elements (1.1)";
  for (unsigned int i = 0; i < 5; ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut3[i])
      << "testFancyStringWithItkArray: failed reading user-specified number of elements (1.2)";
  }
  std::cout << "testFancyStringWithItkArray: dataOut3 OK!" << std::endl;

  // read user-specified number of data elements (output data do not exist)
  DataType dataOut4;
  s = svalue;
  s.ToData(dataOut4, 5);
  // check successful or not
  ASSERT_EQ(dataOut4.GetSize(), 5u)
    << "testFancyStringWithItkArray: failed reading user-specified number of elements (2.1)";
  for (unsigned int i = 0; i < 5; ++i)
  {
    EXPECT_EQ(dataIn[i], dataOut4[i])
      << "testFancyStringWithItkArray: failed reading user-specified number of elements (2.2)";
  }
  std::cout << "testFancyStringWithItkArray: dataOut4 OK!" << std::endl;

  // all testings were successful if reached here
}

void
testFancyStringForStringOperations()
{
  itk::FancyString s;

  s = " Hello World! ";
  EXPECT_FALSE(s.TrimLeft() != "Hello World! ") << "testFancyStringForStringOperations: failed trimming left";
  std::cout << "testFancyStringForStringOperations: TrimLeft() OK!" << std::endl;

  s = " Hello World! ";
  EXPECT_FALSE(s.TrimRight() != " Hello World!") << "testFancyStringForStringOperations: failed trimming right";
  std::cout << "testFancyStringForStringOperations: TrimRight() OK!" << std::endl;

  s = " Hello World! ";
  EXPECT_FALSE(s.Trim() != "Hello World!") << "testFancyStringForStringOperations: failed trimming both sides";
  std::cout << "testFancyStringForStringOperations: Trim() OK!" << std::endl;

  s = "Hello World!";
  EXPECT_FALSE(s.ToUpperCase() != "HELLO WORLD!")
    << "testFancyStringForStringOperations: failed converting to upper case";
  std::cout << "testFancyStringForStringOperations: ToUpperCase() OK!" << std::endl;

  s = "Hello World!";
  EXPECT_FALSE(s.ToLowerCase() != "hello world!")
    << "testFancyStringForStringOperations: failed converting to lower case";
  std::cout << "testFancyStringForStringOperations: ToLowerCase() OK!" << std::endl;

  s = " origin = 0 0 0 ";
  std::string lpart;
  std::string rpart;
  s.Split(lpart, rpart);
  EXPECT_EQ(lpart, "origin") << "testFancyStringForStringOperations: failed splitting into two parts";
  EXPECT_EQ(rpart, "0 0 0") << "testFancyStringForStringOperations: failed splitting into two parts";
  std::cout << "testFancyStringForStringOperations: Split(-,-) OK!" << std::endl;

  s = " size = 256 256 100; spacing = 0.3 0.3 0.7; origin = * ";
  std::vector<std::string> parts;
  s.Split(parts);
  EXPECT_EQ(parts[0], "size = 256 256 100")
    << "testFancyStringForStringOperations: failed splitting into a sequence of strings";
  EXPECT_EQ(parts[1], "spacing = 0.3 0.3 0.7")
    << "testFancyStringForStringOperations: failed splitting into a sequence of strings";
  EXPECT_EQ(parts[2], "origin = *")
    << "testFancyStringForStringOperations: failed splitting into a sequence of strings";
  std::cout << "testFancyStringForStringOperations: Split(vector) OK!" << std::endl;

  s = " size = 256 256 100; spacing = 0.3 0.3 0.7; origin = * ";
  std::map<std::string, std::string> items;
  s.Split(items);
  EXPECT_EQ(items["size"], "256 256 100")
    << "testFancyStringForStringOperations: failed splitting into a map or dictionary";
  EXPECT_EQ(items["spacing"], "0.3 0.3 0.7")
    << "testFancyStringForStringOperations: failed splitting into a map or dictionary";
  EXPECT_EQ(items["origin"], "*") << "testFancyStringForStringOperations: failed splitting into a map or dictionary";
  std::cout << "testFancyStringForStringOperations: Split(map) OK!" << std::endl;

  s = "Hello World!";
  EXPECT_TRUE(s.MatchWith("hello world!")) << "testFancyStringForStringOperations: failed MatchWith testing (1)";
  EXPECT_FALSE(s.MatchWith("hello world!", false))
    << "testFancyStringForStringOperations: failed MatchWith testing (2)";
  EXPECT_FALSE(s.MatchWith(" hello world! ")) << "testFancyStringForStringOperations: failed MatchWith testing (3)";
  std::cout << "testFancyStringForStringOperations: MatchWith(-) OK!" << std::endl;

  s = "Hello World!";
  EXPECT_TRUE(s.StartWith("hello")) << "testFancyStringForStringOperations: failed StartWith testing (1)";
  EXPECT_FALSE(s.StartWith("hello", false)) << "testFancyStringForStringOperations: failed StartWith testing (2)";
  std::cout << "testFancyStringForStringOperations: StartWith(-) OK!" << std::endl;

  s = "Hello World!";
  EXPECT_TRUE(s.EndWith("world!")) << "testFancyStringForStringOperations: failed EndWith testing (1)";
  EXPECT_FALSE(s.EndWith("world!", false)) << "testFancyStringForStringOperations: failed EndWith testing (2)";
  std::cout << "testFancyStringForStringOperations: EndWith(-) OK!" << std::endl;

  s = "Hello World!";
  EXPECT_TRUE(s.ContainSub("Lo wo")) << "testFancyStringForStringOperations: failed ContainSub testing (1)";
  EXPECT_FALSE(s.ContainSub("Lo wo", false)) << "testFancyStringForStringOperations: failed ContainSub testing (2)";
  std::cout << "testFancyStringForStringOperations: ContainSub(-) OK!" << std::endl;

  // all testings were successful if reached here
}

void
testFancyStringUnequalOperator()
{
  {
    const std::string str = "Hello World!";

    itk::FancyString  s1{ str };
    const std::string s2{ "Hello World" };

    EXPECT_TRUE(s1 != s2);

    const std::string s3{ "Hello world!" };

    EXPECT_TRUE(s1 != s3);

    EXPECT_FALSE(s1 != str);
  }

  {
    itk::FancyString s1{ "s" };
    const char *     s2{ "S" };

    EXPECT_TRUE(s1 != s2);
  }

  {
    itk::FancyString       s1{ "Hello World!" };
    const itk::FancyString s2{ "Hello World" };

    EXPECT_TRUE(s1 != s2);

    const itk::FancyString s3{ "Hello world!" };

    EXPECT_TRUE(s1 != s3);
  }
}

void
testFancyStringEqualOperator()
{
  {
    itk::FancyString  s1{ "Hello World!" };
    const std::string s2{ "Hello World!" };

    EXPECT_TRUE(s1 == s2);

    EXPECT_FALSE(s1 == "Hello");
  }

  {
    itk::FancyString s1{ "s" };
    const char *     s2{ "s" };

    EXPECT_TRUE(s1 == s2);
  }

  {
    itk::FancyString       s1{ "Hello World!" };
    const itk::FancyString s2{ "Hello World!" };

    EXPECT_TRUE(s1 == s2);
  }
}
} // namespace
