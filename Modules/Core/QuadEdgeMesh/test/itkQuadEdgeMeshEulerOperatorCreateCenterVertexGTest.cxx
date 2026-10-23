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

#include "itkQuadEdgeMeshEulerOperatorCreateCenterVertexFunction.h"
#include "itkQuadEdgeMeshEulerOperatorsTestHelper.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshEulerOperatorCreateCenterVertex, ConvertedLegacyTest)
{

  using MeshType = itk::QuadEdgeMesh<double, 3>;
  using MeshPointer = MeshType::Pointer;
  using QEType = MeshType::QEType;

  using CreateCenterVertex = itk::QuadEdgeMeshEulerOperatorCreateCenterVertexFunction<MeshType, QEType>;

  /////////////////////////////////////////
  //
  //          Create Center Vertex
  //
  /////////////////////////////////////////
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
  //    |        __/ |        __/ |        __//|        __/ |
  //    |     __/    |     __/    |     __/  / |     __/    |
  //    |  __/       |  __/       |  __/ __x/  |  __/       |
  //    | /          | /          | /___/   \_ | /          |
  //    0 ---------- 1 ---------- 2  --------- 3 ---------  4

  std::cout << "Checking CreateCenterVertex." << std::endl;

  const MeshPointer mesh = MeshType::New();
  CreateSquareTriangularMesh<MeshType>(mesh);

  auto createCenterVertex = CreateCenterVertex::New();
#ifndef NDEBUG
  std::cout << "     "
            << "Test No Mesh Input";
  EXPECT_FALSE(createCenterVertex->Evaluate((QEType *)1));
  std::cout << "OK" << std::endl;
#endif
  EXPECT_EQ(std::string_view("QuadEdgeMeshEulerOperatorCreateCenterVertexFunction"),
            std::string_view(createCenterVertex->GetNameOfClass()));

  createCenterVertex->SetInput(mesh);
#ifndef NDEBUG
  std::cout << "     "
            << "Test QE Input with no left face";
  auto * dummy = new QEType;
  EXPECT_FALSE(createCenterVertex->Evaluate(dummy));
  delete dummy;
  std::cout << "OK" << std::endl;

  std::cout << "     "
            << "Test No QE Input";
  EXPECT_FALSE(createCenterVertex->Evaluate((QEType *)nullptr));
  std::cout << "OK" << std::endl;
#endif

  std::cout << "     ";
  std::cout << "Create a center vertex of a triangle (possible).";
  ASSERT_TRUE(createCenterVertex->Evaluate(mesh->FindEdge(8, 2)));
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 26, 59, 34, 1, 0));
  EXPECT_EQ(mesh->GetPoint(createCenterVertex->GetNewPointID()).GetValence(), 3)
    << "wrong valence for vertex " << createCenterVertex->GetNewPointID() << '.';
  std::cout << ".OK" << std::endl;
  // test with a bigger polygon
  //
  //   20 --------- 21 --------- 22 --------- 23 --------- 24
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //   15 --------- 16 --------- 17 --------- 18 --------- 19
  //    |        __/ | \__        |        __/ |        __/ |
  //    |     __/    |    \__     |     __/    |     __/    |
  //    |  __/       |       \__  |  __/       |  __/       |
  //    | /          |          \ | /          | /          |
  //   10 --------- 11---------- xx --------- 13 --------- 14
  //    |        __/ |        __/ | \__        |        __/ |
  //    |     __/    |     __/    |    \__     |     __/    |
  //    |  __/       |  __/       |       \__  |  __/       |
  //    | /          | /          |          \ | /          |
  //    5 ---------- 6 ---------- 7 ---------- 8 ---------  9
  //    |        __/ |        __/ |        __/ |        __/ |
  //    |     __/    |     __/    |     __/    |     __/    |
  //    |  __/       |  __/       |  __/       |  __/       |
  //    | /          | /          | /          | /          |
  //    0 ---------- 1 ---------- 2  --------- 3 ---------  4

  CreateSquareTriangularMesh<MeshType>(mesh);

  std::cout << "     ";
  std::cout << "Create a center vertex of a Polygon (possible).";

  // this create the 16-17-18-13-8-7-6-11 polygon.
  mesh->LightWeightDeleteEdge(mesh->FindEdge(11, 12));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(6, 12));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(7, 12));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(7, 13));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(12, 13));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(12, 18));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(12, 17));
  mesh->LightWeightDeleteEdge(mesh->FindEdge(11, 17));
  mesh->DeletePoint(12);
  mesh->AddFace(mesh->FindEdge(6, 7));
  ASSERT_TRUE(createCenterVertex->Evaluate(mesh->FindEdge(6, 7)));
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  EXPECT_EQ(mesh->GetPoint(createCenterVertex->GetNewPointID()).GetValence(), 8)
    << "wrong valence for vertex " << createCenterVertex->GetNewPointID() << '.';
  std::cout << ".OK" << std::endl;
  std::cout << "Checking CreateCenterVertex."
            << "OK" << std::endl
            << std::endl;
}
