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
#include "itkLabelObject.h"
#include "itkGTest.h"

TEST(LabelObject, ConvertedLegacyTest)
{
  constexpr int dim{ 3 };

  using LabelObjectType = itk::LabelObject<unsigned long, dim>;
  using IndexType = LabelObjectType::IndexType;

  // testing AddLine(), GetNumberOfLines(), GetLineContainer() const and Optimize()

  auto lo = LabelObjectType::New();

  IndexType idx;
  idx[0] = 1;
  idx[1] = 20;
  idx[2] = 30;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 0;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 1;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 1;
  idx[2] = 0;
  lo->AddLine(idx, 10);

  idx[0] = 0;
  idx[1] = 1;
  idx[2] = 1;
  lo->AddLine(idx, 10);

  idx[0] = 10;
  idx[1] = 1;
  idx[2] = 1;
  // add this line with an itk::LabelLineObject to test the AddLine(LabelObjectLine) method
  lo->AddLine(LabelObjectType::LineType(idx, 1));

  lo->Optimize();

  // the expected result after Optimize()
  auto ref = LabelObjectType::New();

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 0;
  ref->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 1;
  idx[2] = 0;
  ref->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 1;
  ref->AddLine(idx, 10);

  idx[0] = 0;
  idx[1] = 1;
  idx[2] = 1;
  ref->AddLine(idx, 11);

  idx[0] = 1;
  idx[1] = 20;
  idx[2] = 30;
  ref->AddLine(idx, 14);

  // compare the result
  ASSERT_EQ(lo->GetNumberOfLines(), ref->GetNumberOfLines()) << "number of lines is different!";

  using IteratorType = LabelObjectType::ConstLineIterator;

  auto         it1 = IteratorType(ref);
  IteratorType it2(lo);

  lo->Print(std::cerr);

  while (!it1.IsAtEnd())
  {
    std::cout << it1.GetLine().GetIndex() << '-' << it1.GetLine().GetLength() << "    ";
    std::cout << it2.GetLine().GetIndex() << '-' << it2.GetLine().GetLength();
    std::cout << std::endl;
    EXPECT_EQ(it1.GetLine().GetIndex(), it2.GetLine().GetIndex()) << "Line mismatch.";
    EXPECT_EQ(it1.GetLine().GetLength(), it2.GetLine().GetLength()) << "Line mismatch.";
    // test both versions of the iterator
    it1++;
    ++it2;
  }

  EXPECT_TRUE(it2.IsAtEnd()) << "it2 not at end";

  // testing AddIndex(), GetIndex() and HasIndex()

  lo = LabelObjectType::New();
  std::vector<IndexType> idxs;

  // one isolated pixel
  idx[0] = 0;
  idx[1] = 0;
  idx[2] = 0;
  lo->AddIndex(idx);
  idxs.push_back(idx);

  // and two consecutive ones
  idx[0] = 1;
  idx[1] = 2;
  idx[2] = 3;
  lo->AddIndex(idx);
  idxs.push_back(idx);

  idx[0] = 2;
  idx[1] = 2;
  idx[2] = 3;
  lo->AddIndex(idx);
  idxs.push_back(idx);

  // should produce 2 lines
  EXPECT_EQ(lo->GetNumberOfLines(), 2u) << "number of lines should be 2!";

  // should produce 3 pixels
  ASSERT_EQ(lo->Size(), 3u) << "size should be 3!";

  for (unsigned int i = 0; i < lo->Size(); ++i)
  {
    EXPECT_EQ(lo->GetIndex(i), idxs[i]) << "Wrong index returned by GetIndex(" << i << ')';
    EXPECT_TRUE(lo->HasIndex(idxs[i])) << "label object should have the index " << idxs[i] << '!';
  }

  // test with an index not there
  idx[0] = 10;
  idx[1] = 10;
  idx[2] = 10;
  EXPECT_FALSE(lo->HasIndex(idx)) << "label object shouldn't have the index " << idx << '!';
}
