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

#include "itkWaveletUtilities.h"
#include "itkGTest.h"

namespace
{
void
IndexToLevelBandTest(const unsigned int & linearIndex,
                     const unsigned int & levels,
                     const unsigned int & bands,
                     const unsigned int & expectedLevel,
                     const unsigned int & expectedBand)
{
  using namespace itk::utils;
  IndexPairType pairLvBand = IndexToLevelBandSteerablePyramid(linearIndex, levels, bands);
  unsigned int  lv = pairLvBand.first;
  unsigned int  b = pairLvBand.second;
  EXPECT_EQ(lv, expectedLevel) << "Error for linearIndex: " << linearIndex;
  EXPECT_EQ(b, expectedBand) << "Error for linearIndex: " << linearIndex;
}

void
testComputeMaxNumberOfLevels()
{
  constexpr unsigned int Dimension = 3;

  unsigned int scaleFactor = 2;
  using SizeType = itk::Size<Dimension>;
  SizeType inputSize;
  inputSize.Fill(12);
  unsigned int expected = 3;

  unsigned int result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);
  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  inputSize.Fill(16);
  expected = 4;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  inputSize.Fill(17);
  expected = 1;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  inputSize.Fill(22);
  expected = 2;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  inputSize.Fill(3);
  expected = 1;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  // Change scaleFactor
  scaleFactor = 3;
  inputSize.Fill(27);
  expected = 3;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  scaleFactor = 4;
  inputSize.Fill(16);
  expected = 2;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;

  // With odd values
  scaleFactor = 2;
  inputSize.Fill(111);
  expected = 1;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  scaleFactor = 2;
  inputSize.Fill(112);
  // four division by the scale factor resulting in an integer.
  // 112 / 2 / 2 / 2 / 2 = 7
  expected = 5;
  result = itk::utils::ComputeMaxNumberOfLevels(inputSize, scaleFactor);

  EXPECT_EQ(result, expected) << "Error in ComputeMaxNumberOfLevels with scaleFactor = " << scaleFactor
                              << ", inputSize = " << inputSize;
}
} // namespace


TEST(WaveletUtilities, ConvertedLegacyTest)
{
  // Test IndexToLevelBand
  {
    unsigned int linearIndex = 0;
    unsigned int levels = 1;
    unsigned int bands = 1;
    unsigned int expectedLevel = 0;
    unsigned int expectedBand = 1;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 1;
    unsigned int levels = 1;
    unsigned int bands = 1;
    unsigned int expectedLevel = levels;
    unsigned int expectedBand = 0;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 4;
    unsigned int levels = 1;
    unsigned int bands = 1;
    EXPECT_THROW(itk::utils::IndexToLevelBandSteerablePyramid(linearIndex, levels, bands), itk::ExceptionObject);
  }
  {
    unsigned int linearIndex = 0;
    unsigned int levels = 2;
    unsigned int bands = 2;
    unsigned int expectedLevel = 0;
    unsigned int expectedBand = 1;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 1;
    unsigned int levels = 2;
    unsigned int bands = 2;
    unsigned int expectedLevel = 0;
    unsigned int expectedBand = 2;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 2;
    unsigned int levels = 2;
    unsigned int bands = 2;
    unsigned int expectedLevel = 1;
    unsigned int expectedBand = 1;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 3;
    unsigned int levels = 2;
    unsigned int bands = 2;
    unsigned int expectedLevel = 1;
    unsigned int expectedBand = 2;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 4;
    unsigned int levels = 2;
    unsigned int bands = 2;
    unsigned int expectedLevel = levels;
    unsigned int expectedBand = 0;
    IndexToLevelBandTest(linearIndex, levels, bands, expectedLevel, expectedBand);
  }
  {
    unsigned int linearIndex = 5;
    unsigned int levels = 2;
    unsigned int bands = 2;
    EXPECT_THROW(itk::utils::IndexToLevelBandSteerablePyramid(linearIndex, levels, bands), itk::ExceptionObject);
  }

  // Test ComputeMaxNumberOfLevels
  testComputeMaxNumberOfLevels();
}
