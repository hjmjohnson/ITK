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

#include "itkQuadEdgeMeshEulerOperatorJoinFacetFunction.h"
#include "itkQuadEdgeMeshEulerOperatorsTestHelper.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshEulerOperatorJoinFacet, ConvertedLegacyTest)
{

  using MeshType = itk::QuadEdgeMesh<double, 3>;
  using MeshPointer = MeshType::Pointer;
  using QEType = MeshType::QEType;

  using JoinFacet = itk::QuadEdgeMeshEulerOperatorJoinFacetFunction<MeshType, QEType>;

  // EULER OPERATOR TESTS
  const MeshPointer mesh = MeshType::New();
  CreateSquareTriangularMesh<MeshType>(mesh);

  // The initial configuration and numbering of simpleSquare.vtk:
  //    Vertices: 25 , Edges: 56, Faces: 32, Boundary = 1, Chi = 1
  //
  //   20 --------- 21 --------- 22 --------- 23 --------- 24
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //   15 --------- 16 --------- 17 --------- 18 --------- 19
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //   10 --------- 11 --------- 12 --------- 13 --------- 14
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //    5 ---------- 6 ---------- 7 ---------- 8 ---------  9
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //    0 ---------- 1 ---------- 2  --------- 3 ---------  4
  //
  /////////////////////////////////////////
  //
  //          Join Facet
  //
  /////////////////////////////////////////

  std::cout << "Checking JointFacet." << std::endl;

  auto joinFacet = JoinFacet::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(
    joinFacet, QuadEdgeMeshEulerOperatorJoinFacetFunction, QuadEdgeMeshFunctionBase);


#ifndef NDEBUG
  std::cout << "     "
            << "Test No Mesh Input";
  EXPECT_EQ(joinFacet->Evaluate((QEType *)1), nullptr);
  std::cout << "OK" << std::endl;
#endif

  EXPECT_EQ(std::string_view("QuadEdgeMeshEulerOperatorJoinFacetFunction"),
            std::string_view(joinFacet->GetNameOfClass()));

  joinFacet->SetInput(mesh);

#ifndef NDEBUG
  std::cout << "     "
            << "Test QE Input not internal";
  auto * dummy = new QEType;
  EXPECT_EQ(joinFacet->Evaluate(dummy), nullptr);
  delete dummy;
  std::cout << "OK" << std::endl;

  std::cout << "     "
            << "Test No QE Input";
  EXPECT_EQ(joinFacet->Evaluate((QEType *)nullptr), nullptr);
  std::cout << "OK" << std::endl;
#endif

  //
  //   20 --------- 21 --------- 22 --------- 23 --------- 24
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //   15 --------- 16 --------- 17 --------- 18 --------- 19
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //   10 --------- 11 --------- 12 ---<-H--- 13 --------- 14
  //    |        __/ |        __/          __/ |        __/ |
  //    |     __/    |     __/ new      __/    |     __/    |
  //    |  __/       |  __/     face __/       |  __/       |
  //    | /          | /            /          | /          |
  //    5 ---------- 6 ----G->--- 7 ---------- 8 ---------  9
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //    0 ---------- 1 ---------- 2  --------- 3 ---------  4
  //

  std::cout << "     "
            << "Test Edge deletion (possible)";
  // Find an internal edge and collapse it
  EXPECT_NE(joinFacet->Evaluate(mesh->FindEdge(12, 7)), nullptr);

  // Since the edge was internal we lost an edge and an face:
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 55, 31, 1, 0));
  EXPECT_EQ(mesh->GetPoint(12).GetValence(), 5) << "wrong valence";
  std::cout << "OK" << std::endl;
  std::cout << "Checking JointFacet."
            << "OK" << std::endl
            << std::endl;
}
