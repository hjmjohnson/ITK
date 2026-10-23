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

#include "itkQuadEdgeMeshEulerOperatorFlipEdgeFunction.h"
#include "itkQuadEdgeMeshEulerOperatorsTestHelper.h"
#include "itkGTest.h"

TEST(QuadEdgeMeshEulerOperatorFlip, ConvertedLegacyTest)
{

  using MeshType = itk::QuadEdgeMesh<double, 3>;
  using MeshPointer = MeshType::Pointer;
  using QEType = MeshType::QEType;

  using FlipEdge = itk::QuadEdgeMeshEulerOperatorFlipEdgeFunction<MeshType, QEType>;

  const MeshPointer mesh = MeshType::New();
  CreateSquareTriangularMesh<MeshType>(mesh);
  auto flipEdge = FlipEdge::New();
  std::cout << flipEdge << std::endl;

#ifndef NDEBUG
  EXPECT_FALSE(flipEdge->Evaluate((QEType *)1));
  std::cout << "OK" << std::endl;
#endif

  std::cout << flipEdge->GetNameOfClass() << std::endl;

  flipEdge->SetInput(mesh);

#ifndef NDEBUG
  std::cout << "     "
            << "Test QE Input not internal";
  auto * dummy = new QEType;
  EXPECT_FALSE(flipEdge->Evaluate(dummy));
  delete dummy;
  std::cout << "OK" << std::endl;
  std::cout << "     "
            << "Test No QE Input";
  EXPECT_FALSE(flipEdge->Evaluate((QEType *)nullptr));
  std::cout << "OK" << std::endl;
#endif

  mesh->LightWeightDeleteEdge(mesh->FindEdge(12, 18));
  mesh->AddFace(mesh->FindEdge(17, 12));
  std::cout << "     "
            << "Flip an edge with a polygonal face (impossible)";
  QEType * tempFlippedEdge = flipEdge->Evaluate(mesh->FindEdge(12, 17));
  EXPECT_EQ(tempFlippedEdge, nullptr);

  CreateSquareTriangularMesh<MeshType>(mesh);
  std::cout << "     "
            << "Flip an edge (possible)";
  tempFlippedEdge = flipEdge->Evaluate(mesh->FindEdge(12, 6));
  ASSERT_NE(tempFlippedEdge, nullptr);
  // The number of edges and faces must be unchanged:
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  EXPECT_EQ(mesh->GetPoint(12).GetValence(), 5) << "wrong valence for vertex 12";
  EXPECT_EQ(mesh->GetPoint(6).GetValence(), 5) << "wrong valence for vertex 6";
  EXPECT_EQ(mesh->GetPoint(11).GetValence(), 7) << "wrong valence for vertex 11";
  EXPECT_EQ(mesh->GetPoint(7).GetValence(), 7) << "wrong valence for vertex 7";
  std::cout << ".OK" << std::endl;
  // Checking invariance (i.e. FlipEdge is its own inverse):
  std::cout << "     "
            << "Check FlipEdge(FlipEdge()) invariance (possible for triangles).";
  EXPECT_TRUE(flipEdge->Evaluate(tempFlippedEdge));
  // The number of edges and faces must be unchanged:
  EXPECT_TRUE(AssertTopologicalInvariants<MeshType>(mesh, 25, 56, 32, 1, 0));
  EXPECT_EQ(mesh->GetPoint(12).GetValence(), 6) << "wrong valence for vertex 12";
  EXPECT_EQ(mesh->GetPoint(6).GetValence(), 6) << "wrong valence for vertex 6";
  EXPECT_EQ(mesh->GetPoint(11).GetValence(), 6) << "wrong valence for vertex 11";
  EXPECT_EQ(mesh->GetPoint(7).GetValence(), 6) << "wrong valence for vertex 7";
  std::cout << "OK" << std::endl;
  std::cout << "Checking FlipEdge."
            << "OK" << std::endl
            << std::endl;

  // Test streaming enumeration for QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType elements
  const std::set<itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType> allEdgeStatusType{
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::STANDARD_CONFIG,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::EDGE_NULL,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::MESH_NULL,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::NON_INTERNAL_EDGE,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::NON_TRIANGULAR_RIGHT_FACE,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::NON_TRIANGULAR_LEFT_FACE,
    itk::QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType::EXISTING_OPPOSITE_EDGE
  };
  for (const auto & ee : allEdgeStatusType)
  {
    std::cout << "STREAMED ENUM VALUE QuadEdgeMeshEulerOperatorFlipEdgeFunctionEnums::EdgeStatusType: " << ee
              << std::endl;
  }
}
