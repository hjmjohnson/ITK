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

#include "itkArrowSpatialObject.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(ArrowSpatialObject, ConvertedLegacyTest)
{
  using ArrowType = itk::ArrowSpatialObject<3>;

  auto myArrow = ArrowType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(myArrow, ArrowSpatialObject, SpatialObject);


  // Testing the position
  SCOPED_TRACE("Testing position :");
  ArrowType::PointType pnt;
  pnt[0] = 0;
  pnt[1] = 1;
  pnt[2] = 0;
  myArrow->SetPositionInObjectSpace(pnt);
  myArrow->Update();

  EXPECT_EQ(pnt, myArrow->GetPositionInObjectSpace());

  // Testing the length
  SCOPED_TRACE("Testing length :");
  constexpr double length{ 2 };
  myArrow->SetLengthInObjectSpace(length);
  EXPECT_EQ(length, myArrow->GetLengthInObjectSpace());

  // Testing the direction of the arrow
  SCOPED_TRACE("Testing direction :");

  ArrowType::VectorType direction{};
  direction[1] = 1.0;

  myArrow->SetDirectionInObjectSpace(direction);
  myArrow->Update();

  EXPECT_EQ(direction, myArrow->GetDirectionInObjectSpace());

  // Point consistency
  SCOPED_TRACE("Is Inside (Inside):");
  itk::Point<double, 3> in;
  in[0] = 0;
  in[1] = 1;
  in[2] = 0;
  EXPECT_TRUE(myArrow->IsInsideInWorldSpace(in)) << "[FAILED]";

  SCOPED_TRACE("Is Inside (Outside):");
  itk::Point<double, 3> out;
  out[0] = 0;
  out[1] = 2.1;
  out[2] = 0;
  EXPECT_FALSE(myArrow->IsInsideInWorldSpace(out)) << "[FAILED]";


  SCOPED_TRACE("Update():");
  const ArrowType::BoundingBoxType * boundingBox = myArrow->GetMyBoundingBoxInWorldSpace();

  std::cout << boundingBox->GetBounds() << std::endl;
  EXPECT_EQ(boundingBox->GetBounds()[2], 1.0) << "[FAILED]";
  EXPECT_EQ(boundingBox->GetBounds()[3], 1.0) << "[FAILED]";

  SCOPED_TRACE("Testing 2D Arrow:");
  using Arrow2DType = itk::ArrowSpatialObject<2>;
  auto myArrow2D = Arrow2DType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(myArrow2D, ArrowSpatialObject, SpatialObject);
}
