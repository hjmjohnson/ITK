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

#include "itkPolygonSpatialObject.h"
#include "itkGTest.h"
#include <iostream>

TEST(PolygonSpatialObject, ConvertedLegacyTest)
{
  using PolygonType = itk::PolygonSpatialObject<3>;

  //
  // create rectangle
  auto rectangle = PolygonType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(rectangle, PolygonSpatialObject, PointBasedSpatialObject);


  constexpr double             d1[3]{ 0.0, 0.0, 0.0 };
  const PolygonType::PointType p1(d1);
  constexpr double             d2[3]{ 2.0, 0.0, 0.0 };
  const PolygonType::PointType p2(d2);
  constexpr double             d3[3]{ 2.0, 1.0, 0.0 };
  const PolygonType::PointType p3(d3);
  constexpr double             d4[3]{ 0.0, 1.0, 0.0 };
  const PolygonType::PointType p4(d4);

  PolygonType::PolygonPointListType pList;
  PolygonType::PolygonPointType     pPoint;
  pList.clear();
  pPoint.SetPositionInObjectSpace(p1);
  pList.push_back(pPoint);
  pPoint.SetPositionInObjectSpace(p2);
  pList.push_back(pPoint);
  pPoint.SetPositionInObjectSpace(p3);
  pList.push_back(pPoint);
  pPoint.SetPositionInObjectSpace(p4);
  pList.push_back(pPoint);
  rectangle->SetPoints(pList);

  constexpr double objectSpaceThickness{ 10 };
  rectangle->SetThicknessInObjectSpace(objectSpaceThickness);
  EXPECT_EQ(objectSpaceThickness, rectangle->GetThicknessInObjectSpace());

  constexpr bool isClosed{ true };
  rectangle->SetIsClosed(isClosed);
  ITK_GTEST_SET_GET_BOOLEAN(rectangle, IsClosed, isClosed);


  rectangle->Update();

  for (unsigned int i = 0; i < rectangle->GetNumberOfPoints(); ++i)
  {
    std::cout << i << " : ";
    rectangle->GetPoint(i)->Print(std::cout);
  }
  //
  // test number of points
  std::cout << "Testing number of points for rectangle: ";
  EXPECT_EQ(rectangle->GetNumberOfPoints(), 4u) << "[Failed]" << '\n' << rectangle->GetNumberOfPoints() << " != 4";

  //
  // test area
  std::cout << "Testing area for rectangle: ";
  EXPECT_EQ(rectangle->MeasureAreaInObjectSpace(), 2.0) << "[Failed]" << '\n'
                                                        << rectangle->MeasureAreaInObjectSpace() << " != 2.0";

  //
  // test volume
  std::cout << "Testing volume for rectangle: ";
  EXPECT_EQ(rectangle->MeasureVolumeInObjectSpace(), 20.0) << "[Failed]" << '\n'
                                                           << rectangle->MeasureVolumeInObjectSpace() << " != 20.0";

  //
  // test perimeter
  std::cout << "Testing perimeter for rectangle: ";
  EXPECT_EQ(rectangle->MeasurePerimeterInObjectSpace(), 6.0) << "Wrong perimeter for rectangle" << '\n'
                                                             << "[Failed]" << '\n'
                                                             << rectangle->MeasurePerimeterInObjectSpace() << " != 6.0";

  //
  // test number of points
  std::cout << "Testing closest point for rectangle: ";
  constexpr double                    tp1[3]{ 0.25, 0.0, 0.0 };
  const PolygonType::PointType        testPoint1(tp1);
  const PolygonType::PolygonPointType closestPoint = rectangle->ClosestPointInWorldSpace(testPoint1);
  EXPECT_EQ(closestPoint.GetPositionInObjectSpace(), p1) << "[Failed]" << '\n'
                                                         << closestPoint.GetPositionInObjectSpace() << " != " << p1;

  //
  // test number of points
  std::cout << "Testing closest point for rectangle (2): ";
  constexpr double                    tp2[3]{ 0.25, 5.0, 5.0 };
  const PolygonType::PointType        testPoint2(tp2);
  const PolygonType::PolygonPointType closestPoint2 = rectangle->ClosestPointInWorldSpace(testPoint2);
  EXPECT_EQ(closestPoint2.GetPositionInObjectSpace(), p4) << "[Failed]" << '\n'
                                                          << closestPoint2.GetPositionInObjectSpace() << " != " << p4;


  std::cout << "Test finished" << std::endl;
}
