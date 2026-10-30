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

#include "itkQuadEdgeMeshPoint.h"
#include "itkMesh.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshPoint, ConvertedLegacyTest)
{
  std::cout << "Testing points..." << std::endl;

  //
  // These type alias are taken from a traditional itk mesh just
  // to get definitions that are consistent with the derived class.
  //
  using NonQuadEdgeMeshType = itk::Mesh<float, 3>;
  using PointIdentifier = NonQuadEdgeMeshType::PointIdentifier;
  using FaceIdentifier = NonQuadEdgeMeshType::CellIdentifier;

  using PrimalDataType = bool;
  using DualDataType = bool;

  constexpr bool ThisIsDual{ true };

  using QuadEdgeType =
    itk::GeometricalQuadEdge<PointIdentifier, FaceIdentifier, PrimalDataType, DualDataType, ThisIsDual>;

  using PointType = itk::QuadEdgeMeshPoint<float, 3, QuadEdgeType>;

  using SuperclassPointType = PointType::Superclass;

  PointType p1;
  p1[0] = 17.7;
  p1[1] = 39.7;
  p1[2] = -49.7;

  const PointType p2(p1); // Test copy constructor

  EXPECT_LE(p1.EuclideanDistanceTo(p2), 1e-6) << "Error in the copy constructor";

  //
  // Test assignment from an itk::Point
  //
  SuperclassPointType ps;

  ps[0] = 29;
  ps[1] = 31;
  ps[2] = 37;

  const PointType pp = ps;

  EXPECT_LE(pp.EuclideanDistanceTo(ps), 1e-6) << "Error in the array constructor";

  PointType pp2;
  pp2.SetPoint(ps);

  EXPECT_LE(pp2.EuclideanDistanceTo(ps), 1e-6) << "Error in the array constructor";

  PointType::ValueArrayType cc;
  cc[0] = 17.7;
  cc[1] = 39.7;
  cc[2] = -49.7;

  const PointType p3(cc); // Test Array based constructor

  EXPECT_LE(p2.EuclideanDistanceTo(p1), 1e-6) << "Error in the array constructor";

  const PointType p4 = p1;
  const PointType p4b = p1; // Test assignment operator to Self

  EXPECT_LE(p4.EuclideanDistanceTo(p1), 1e-6) << "Error in the assignment operator to Self";

  EXPECT_LE(p4b.EuclideanDistanceTo(p4), 1e-6) << "Error in the assignment operator to Self";

  PointType::Superclass pp1;
  pp1[0] = 17.7;
  pp1[1] = 39.7;
  pp1[2] = -49.7;

  const PointType p5 = pp1;
  const PointType p5b = pp1; // Test assignment operator from Superclass

  EXPECT_LE(p5.EuclideanDistanceTo(pp1), 1e-6) << "Error assignment operator from Superclass";

  EXPECT_LE(p5b.EuclideanDistanceTo(p5), 1e-6) << "Error assignment operator from Superclass";

  PointType       p6 = cc;
  const PointType p6b = cc; // Test assignment operator from array

  EXPECT_LE(p6.EuclideanDistanceTo(p3), 1e-6) << "Error in the assignment operator from Array ";

  EXPECT_LE(p6b.EuclideanDistanceTo(p6), 1e-6) << "Error in the assignment operator from Array ";

  auto * edge1 = new QuadEdgeType;

  p6.SetEdge(edge1);

  EXPECT_EQ(p6.GetEdge(), edge1) << "Error in SetEdge()/GetEdge() ";

  auto * edge2 = new QuadEdgeType;

  p6.SetEdge(edge2);

  EXPECT_EQ(p6.GetEdge(), edge2) << "Error in SetEdge()/GetEdge() ";

  // The following tests are commented out
  // because the point code is not safe yet.
#if defined(POINTMAKESAFE)
  bool internal = p6.IsInternal();

  EXPECT_TRUE(internal) << "Error in IsInternal() "; // FIXME: verify with a realistic case

  PointType p7;
  EXPECT_FALSE(p7.IsInternal()) << "Error in IsInternal() ";

  int valence = p6.GetValence();
  EXPECT_EQ(valence, 1) << "Error in GetValence() ";
#endif

  delete edge1;
  delete edge2;

  std::cout << "Test passed" << std::endl;
}
