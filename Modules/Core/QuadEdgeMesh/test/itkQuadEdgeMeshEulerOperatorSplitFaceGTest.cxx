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

#include "itkQuadEdgeMeshEulerOperatorSplitFacetFunction.h"
#include "itkQuadEdgeMeshEulerOperatorJoinFacetFunction.h"
#include "itkQuadEdgeMeshEulerOperatorsTestHelper.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshEulerOperatorSplitFace, ConvertedLegacyTest)
{

  using MeshType = itk::QuadEdgeMesh<double, 3>;
  using MeshPointer = MeshType::Pointer;
  using QEType = MeshType::QEType;

  using SplitFacet = itk::QuadEdgeMeshEulerOperatorSplitFacetFunction<MeshType, QEType>;
  using JoinFacet = itk::QuadEdgeMeshEulerOperatorJoinFacetFunction<MeshType, QEType>;

  /////////////////////////////////////////
  //
  //         Split Facet
  //
  /////////////////////////////////////////

  // Split the facet again in order to restore the original situation:
  std::cout << "Checking SplitFacet." << std::endl;

  auto splitFacet = SplitFacet::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(
    splitFacet, QuadEdgeMeshEulerOperatorSplitFacetFunction, QuadEdgeMeshFunctionBase);


  std::cout << "     "
            << "Test No Mesh Input";
  EXPECT_EQ(splitFacet->Evaluate((QEType *)1, (QEType *)2), nullptr);
  std::cout << "OK" << std::endl;

  const MeshPointer mesh = MeshType::New();
  CreateSquareTriangularMesh<MeshType>(mesh);

  splitFacet->SetInput(mesh);

  std::cout << "     "
            << "Test No QE Input";
  EXPECT_EQ(splitFacet->Evaluate((QEType *)nullptr, (QEType *)nullptr), nullptr);
  std::cout << "OK" << std::endl;

  std::cout << "     "
            << "Test two QE Input not sharing the same left";
  EXPECT_EQ(splitFacet->Evaluate(mesh->FindEdge(10, 16), mesh->FindEdge(13, 19)), nullptr);
  std::cout << "OK" << std::endl;

  std::cout << "     "
            << "Test twice same non-null QE Input";
  EXPECT_EQ(splitFacet->Evaluate((QEType *)1, (QEType *)1), nullptr);
  std::cout << "OK" << std::endl;

  std::cout << "     "
            << "Test two consecutive QE Input";
  EXPECT_EQ(splitFacet->Evaluate(mesh->FindEdge(10, 16), mesh->FindEdge(10, 16)->GetLnext()), nullptr);
  std::cout << "OK" << std::endl;

  auto joinFacet = JoinFacet::New();
  joinFacet->SetInput(mesh);
  QEType * DeletedEdge = mesh->FindEdge(12, 7);
  QEType * G = DeletedEdge->GetSym()->GetLprev();
  QEType * H = joinFacet->Evaluate(DeletedEdge);

  EXPECT_NE(splitFacet->Evaluate(H, G), nullptr);

  std::cout << "     "
            << "Split a face (possible)";
  // The number of edges and faces must be respectively identical to
  // the original number edges and faces:
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  EXPECT_EQ(mesh->GetPoint(12).GetValence(), 6) << "wrong valence for vertex " << 12;
  std::cout << "OK" << std::endl;
  std::cout << "Checking SplitFacet. OK" << std::endl << std::endl;

  std::cout << "Checking JoinFacet( SplitFacet( edge ) ) invariance.";
  G = mesh->FindEdge(12, 7)->GetSym()->GetLprev();
  H = joinFacet->Evaluate(mesh->FindEdge(12, 7));
  ASSERT_NE(H, nullptr);
  EXPECT_NE(joinFacet->Evaluate(splitFacet->Evaluate(H, G)), nullptr);
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 55, 31, 1, 0));
  EXPECT_EQ(mesh->GetPoint(12).GetValence(), 5) << "wrong valence for vertex " << 12;
  std::cout << ".OK" << std::endl << std::endl;
}
