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

#include "itkGEAdwImageIO.h"
#include "itksys/SystemTools.hxx"

#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <vector>

#define ITK_GEADW_STRINGIFY(s) #s
#define ITK_GEADW_TOSTRING(s) std::string(ITK_GEADW_STRINGIFY(s))

namespace
{
// Byte offsets from the GE ADW header layout (GEAdwImageIO::GE_ADW_DEFINES).
constexpr std::size_t imageMatrixXOffset = 2216;
constexpr std::size_t imageMatrixYOffset = 2218;
constexpr std::size_t fixedHeaderLength = 3228;
constexpr std::size_t variableHeaderLengthOffset = 3232;

struct AdwHeader
{
  short matrixX{ 4 };
  short matrixY{ 4 };
  int   variableHeaderLength{ 0 };
};

// Sizes the zero-filled file with CanReadFile's own size_t arithmetic, so wrapped totals are reproduced.
std::string
WriteAdwFile(const std::string & name, const AdwHeader & header)
{
  const std::string dir = ITK_GEADW_TOSTRING(ITK_TEST_OUTPUT_DIR) + "/GEAdwImageIOGTest/" + name;
  itksys::SystemTools::RemoveADirectory(dir);
  if (!itksys::SystemTools::MakeDirectory(dir))
  {
    return std::string();
  }
  const std::size_t fileLength =
    header.variableHeaderLength + fixedHeaderLength + (header.matrixX * header.matrixY * sizeof(short));
  if (fileLength < variableHeaderLengthOffset + sizeof(int))
  {
    return std::string();
  }
  std::vector<char> bytes(fileLength, 0);
  const auto        putBigEndian = [&bytes](std::size_t offset, auto value) {
    for (std::size_t i = 0; i < sizeof(value); ++i)
    {
      bytes[offset + i] = static_cast<char>((value >> (8 * (sizeof(value) - 1 - i))) & 0xff);
    }
  };
  putBigEndian(imageMatrixXOffset, header.matrixX);
  putBigEndian(imageMatrixYOffset, header.matrixY);
  putBigEndian(variableHeaderLengthOffset, header.variableHeaderLength);

  const std::string path = dir + "/image.adw";
  std::ofstream     stream(path, std::ios::binary);
  stream.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  return path;
}

void
ExpectHeaderRejected(const std::string & name, short matrixX, short matrixY, int variableHeaderLength)
{
  AdwHeader header;
  header.matrixX = matrixX;
  header.matrixY = matrixY;
  header.variableHeaderLength = variableHeaderLength;
  const std::string path = WriteAdwFile(name, header);
  ASSERT_FALSE(path.empty());

  auto imageIO = itk::GEAdwImageIO::New();
  ASSERT_TRUE(imageIO->CanReadFile(path.c_str()));
  imageIO->SetFileName(path);
  EXPECT_THROW(imageIO->ReadImageInformation(), itk::ExceptionObject);
}
} // namespace

TEST(GEAdwImageIO, RejectsTwoNegativeSizes) { ExpectHeaderRejected("negative-matrix", -4, -4, 0); }

TEST(GEAdwImageIO, RejectsOneNegativeSize)
{
  // The negative pixel count wraps in size_t and the variable header length cancels it.
  ExpectHeaderRejected("one-negative-size", -4, 4, 40);
}

TEST(GEAdwImageIO, RejectsZeroSize)
{
  ExpectHeaderRejected("zero-x", 0, 4, 32);
  ExpectHeaderRejected("zero-y", 4, 0, 32);
}

TEST(GEAdwImageIO, ReadsMinimalHeader)
{
  const std::string path = WriteAdwFile("valid-matrix", AdwHeader());
  ASSERT_FALSE(path.empty());

  auto imageIO = itk::GEAdwImageIO::New();
  ASSERT_TRUE(imageIO->CanReadFile(path.c_str()));
  imageIO->SetFileName(path);
  ASSERT_NO_THROW(imageIO->ReadImageInformation());
  EXPECT_EQ(imageIO->GetDimensions(0), 4u);
  EXPECT_EQ(imageIO->GetDimensions(1), 4u);
  EXPECT_EQ(imageIO->GetDimensions(2), 1u);
}
