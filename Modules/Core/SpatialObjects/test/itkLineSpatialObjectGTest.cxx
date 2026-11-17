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

#include "itkGTest.h"
#include "itkLineSpatialObject.h"
#include "itkMath.h"

TEST(LineSpatialObject, ConvertedLegacyTest)
{
  using LineType = itk::LineSpatialObject<3>;
  using LinePointer = LineType::Pointer;
  using LinePointType = LineType::LinePointType;
  using VectorType = itk::CovariantVector<double, 3>;

  std::cout << "==================================" << std::endl;
  std::cout << "Testing LineSpatialObject:" << std::endl << std::endl;

  LineType::LinePointListType list;
  for (unsigned int i = 0; i < 10; ++i)
  {
    LinePointType p;
    p.SetPositionInObjectSpace(i, i + 1, i + 2);
    VectorType normal1;
    VectorType normal2;
    for (unsigned int j = 0; j < 3; ++j)
    {
      normal1[j] = j;
      normal2[j] = j * 2;
    }

    p.SetNormalInObjectSpace(normal1, 0);
    p.SetNormalInObjectSpace(normal2, 1);
    list.push_back(p);
  }

  // For coverage
  LinePointType p;
  p.SetPositionInObjectSpace(0, 1, 2);
  p.Print(std::cout);

  // Create a Line Spatial Object
  const LinePointer line = LineType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(line, LineSpatialObject, PointBasedSpatialObject);


  line->GetProperty().SetName("Line 1");
  line->SetId(1);
  line->SetPoints(list);
  line->Update();

  // Number of points
  std::cout << "Testing Consistency: " << std::endl;
  std::cout << "Number of Points: ";

  EXPECT_EQ(line->GetPoints().size(), 10u) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  // Point consistency
  std::cout << "Point consistency: ";

  auto it = line->GetPoints().begin();

  unsigned int i = 0;
  while (it != line->GetPoints().end())
  {
    for (unsigned int d = 0; d < 3; ++d)
    {
      EXPECT_EQ(it->GetPositionInWorldSpace()[d], i + d) << "[FAILED]";

      EXPECT_EQ((it->GetNormalInObjectSpace(0))[d], d) << "[FAILED]";

      EXPECT_EQ((it->GetNormalInObjectSpace(1))[d], 2 * d) << "[FAILED]";
    }
    it++;
    i++;
  }

  std::cout << "[PASSED]" << std::endl;

  // Point consistency
  std::cout << "Is Inside: ";
  itk::Point<double, 3> in;
  in[0] = 1;
  in[1] = 2;
  in[2] = 3;
  itk::Point<double, 3> out;
  out[0] = 0;
  out[1] = 0;
  out[2] = 0;

  EXPECT_TRUE(line->IsInsideInWorldSpace(in)) << "[FAILED]";

  EXPECT_FALSE(line->IsInsideInWorldSpace(out)) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;

  // Testing IsEvaluableAt()
  std::cout << "IsEvaluableAt: ";
  EXPECT_TRUE(line->IsEvaluableAtInWorldSpace(in)) << "[FAILED]";
  EXPECT_FALSE(line->IsEvaluableAtInWorldSpace(out)) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;


  // Testing IsEvaluableAt()
  std::cout << "ValueAt: ";

  double value = NAN;
  EXPECT_TRUE(line->ValueAtInWorldSpace(in, value)) << "[FAILED]";

  EXPECT_EQ(value, 1) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;

  // Test Copy and Assignment for LinePointType
  {
    LinePointType pOriginal;

    // itk::SpatialObjectPoint
    pOriginal.SetId(250);
    pOriginal.SetColor(0.5, 0.4, 0.3, 0.2);
    pOriginal.SetPositionInObjectSpace(42, 41, 43);

    // itk::LineSpatialObjectPoint
    auto normal = itk::MakeFilled<VectorType>(276);
    pOriginal.SetNormalInObjectSpace(normal, 0);

    // Copy
    const LinePointType pCopy(pOriginal);
    // Assign
    const LinePointType pAssign = pOriginal;

    std::vector<LinePointType> pointVector{ pCopy, pAssign };

    for (const auto & pv : pointVector)
    {
      // itk::SpatialObjectPoint
      EXPECT_EQ(pOriginal.GetId(), pv.GetId());
      EXPECT_DOUBLE_EQ(pOriginal.GetRed(), pv.GetRed());
      EXPECT_DOUBLE_EQ(pOriginal.GetGreen(), pv.GetGreen());
      EXPECT_DOUBLE_EQ(pOriginal.GetBlue(), pv.GetBlue());
      EXPECT_DOUBLE_EQ(pOriginal.GetAlpha(), pv.GetAlpha());
      for (size_t j = 0; j < 3; ++j)
      {
        EXPECT_DOUBLE_EQ(pOriginal.GetPositionInObjectSpace()[j], pv.GetPositionInObjectSpace()[j]);
      }
      // itk::LineSpatialObjectPoint
      for (size_t j = 0; j < 3; ++j)
      {
        EXPECT_DOUBLE_EQ(pOriginal.GetNormalInObjectSpace(0)[j], pv.GetNormalInObjectSpace(0)[j]);
      }
    }
  }


  std::cout << "Test finished" << std::endl;
}
