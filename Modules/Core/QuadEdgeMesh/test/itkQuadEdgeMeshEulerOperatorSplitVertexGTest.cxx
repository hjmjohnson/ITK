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

#include "itkQuadEdgeMeshEulerOperatorSplitVertexFunction.h"
#include "itkQuadEdgeMeshEulerOperatorJoinVertexFunction.h"
#include "itkQuadEdgeMeshEulerOperatorsTestHelper.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshEulerOperatorSplitVertex, ConvertedLegacyTest)
{

  using MeshType = itk::QuadEdgeMesh<double, 3>;
  using MeshPointer = MeshType::Pointer;
  using QEType = MeshType::QEType;
  using PointType = MeshType::PointType;

  using SplitVertex = itk::QuadEdgeMeshEulerOperatorSplitVertexFunction<MeshType, QEType>;
  using JoinVertex = itk::QuadEdgeMeshEulerOperatorJoinVertexFunction<MeshType, QEType>;

  /////////////////////////////////////////
  //
  //          Split Vertex
  //
  /////////////////////////////////////////
  std::cout << "Checking SplitVertex." << std::endl;
  const MeshPointer mesh = MeshType::New();
  CreateSquareTriangularMesh<MeshType>(mesh);

  auto splitVertex = SplitVertex::New();
  std::cout << "     "
            << "Test No Mesh Input";
  EXPECT_FALSE(splitVertex->Evaluate((QEType *)1, (QEType *)1));
  std::cout << "OK" << std::endl;

  EXPECT_EQ(std::string_view("QuadEdgeMeshEulerOperatorSplitVertexFunction"),
            std::string_view(splitVertex->GetNameOfClass()));

  splitVertex->SetInput(mesh);
  std::cout << "     "
            << "Test No QE Input";
  EXPECT_FALSE(splitVertex->Evaluate((QEType *)nullptr, (QEType *)nullptr));
  std::cout << "OK" << std::endl;

  std::cout << "     ";
  std::cout << "Split Vertex (Possible).";
  ASSERT_TRUE(splitVertex->Evaluate(mesh->FindEdge(5, 11), mesh->FindEdge(17, 11)));
  // move the new point, for example along z axis for special effect :-D
  PointType PtTmp = mesh->GetPoint(splitVertex->GetNewPointID());
  PtTmp[2] = 1;
  mesh->SetPoint(splitVertex->GetNewPointID(), PtTmp);
  // Test
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 26, 57, 32, 1, 0)) << "wrong topology";
  EXPECT_EQ(mesh->GetPoint(splitVertex->GetNewPointID()).GetValence(), 4)
    << "wrong valence for vertex " << splitVertex->GetNewPointID() << '.';
  EXPECT_EQ(mesh->GetPoint(11).GetValence(), 4) << "wrong valence for vertex 11";
  std::cout << ".OK" << std::endl;
  // test antenna
  CreateSquareTriangularMesh<MeshType>(mesh);
  std::cout << "     ";
  std::cout << "Try to split antenna (impossible).";

  splitVertex->SetInput(mesh);
  EXPECT_FALSE(splitVertex->Evaluate(mesh->FindEdge(12, 17), mesh->FindEdge(12, 17)));
  std::cout << ".OK" << std::endl;
  // test different dest( )
  CreateSquareTriangularMesh<MeshType>(mesh);
  std::cout << "     ";
  std::cout << "Test with args with different Dest( ) (Impossible).";

  splitVertex->SetInput(mesh);
  EXPECT_FALSE(splitVertex->Evaluate(mesh->FindEdge(5, 11), mesh->FindEdge(5, 6)));
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  EXPECT_EQ(mesh->GetPoint(5).GetValence(), 4) << "wrong valence for vertex 5.";
  std::cout << ".OK" << std::endl;
  std::cout << "Checking SplitVertex." << std::endl << std::endl;

  std::cout << "Checking JoinVertex( SplitVertex()) Invariance.";

  CreateSquareTriangularMesh<MeshType>(mesh);

  splitVertex->SetInput(mesh);

  auto joinVertex = JoinVertex::New();
  joinVertex->SetInput(mesh);
  ASSERT_TRUE(joinVertex->Evaluate(splitVertex->Evaluate(mesh->FindEdge(5, 11), mesh->FindEdge(17, 11))));
  mesh->DeletePoint(joinVertex->GetOldPointID());
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  std::cout << ".OK" << std::endl << std::endl;
}
