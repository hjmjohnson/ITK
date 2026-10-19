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
#include "itkLabelObjectLine.h"
#include "itkGTest.h"

TEST(LabelObjectLine, ConvertedLegacyTest)
{
  using LabelObjectLineType = itk::LabelObjectLine<2>;
  using IndexType = itk::LabelObjectLine<2>::IndexType;
  IndexType currentIndex;
  currentIndex[0] = 3;
  currentIndex[1] = 7;

  IndexType nextIndex;
  nextIndex[0] = 14;
  nextIndex[1] = 7;

  LabelObjectLineType labelLine;
  labelLine.SetIndex(currentIndex);
  labelLine.SetLength(11);

  IndexType indexBack = labelLine.GetIndex();

  EXPECT_EQ(indexBack[0], 3) << "Set/Get Index failed on null constructor. " << indexBack;
  EXPECT_EQ(indexBack[1], 7) << "Set/Get Index failed on null constructor. " << indexBack;

  const LabelObjectLineType::LengthType length = labelLine.GetLength();
  EXPECT_EQ(length, 11u) << "Set/Get length failed on null constructor." << length;

  labelLine = LabelObjectLineType(currentIndex, 11);
  indexBack = labelLine.GetIndex();

  EXPECT_EQ(indexBack[0], 3) << "Set/Get Index failed on arg constructor. " << indexBack;
  EXPECT_EQ(indexBack[1], 7) << "Set/Get Index failed on arg constructor. " << indexBack;

  EXPECT_EQ(labelLine.GetLength(), 11u) << "Set/Get length failed on arg constructor." << length;

  EXPECT_TRUE(labelLine.HasIndex(currentIndex)) << "Has Index failed.";

  EXPECT_FALSE(labelLine.HasIndex(nextIndex)) << "Has Index failed.";

  EXPECT_FALSE(labelLine.IsNextIndex(currentIndex)) << "Is Next Index failed.";

  EXPECT_TRUE(labelLine.IsNextIndex(nextIndex)) << "Is Next Index failed.";

  labelLine.Print(std::cout);
}
