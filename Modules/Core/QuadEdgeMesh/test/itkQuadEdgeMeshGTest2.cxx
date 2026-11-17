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

#include "itkQuadEdgeMesh.h"
#include "itkGTest.h"

TEST(QuadEdgeMesh2, ConvertedLegacyTest)
{
  std::cout << "Testing points and simple edges... " << std::ends;

  using PixelType = double;
  using MeshType = itk::QuadEdgeMesh<PixelType, 3>;
  using CellType = MeshType::CellType;
  using LineType = itk::QuadEdgeMeshLineCell<CellType>;
  using QuadEdgeType = LineType::QEType;
  using CellAutoPointer = CellType::CellAutoPointer;

  auto mesh = MeshType::New();

  MeshType::PointType p0;
  MeshType::PointType p1;
  MeshType::PointType p2;

  p0[0] = -1.0;
  p0[1] = 0.0;
  p0[2] = 0.0;
  p1[0] = 1.0;
  p1[1] = 0.0;
  p1[2] = 0.0;
  p2[0] = 1.0;
  p2[1] = 1.0;
  p2[2] = 0.0;

  mesh->SetPoint(0, p0);
  mesh->SetPoint(1, p1);
  mesh->SetPoint(2, p2);

  CellAutoPointer line0;
  line0.TakeOwnership(new LineType);
  line0->SetPointId(0, 0);
  line0->SetPointId(1, 1);
  mesh->SetCell(0, line0);

  CellAutoPointer line1;
  line1.TakeOwnership(new LineType);
  line1->SetPointId(0, 1);
  line1->SetPointId(1, 2);
  mesh->SetCell(1, line1);

  CellAutoPointer line2;
  line2.TakeOwnership(new LineType);
  line2->SetPointId(0, 2);
  line2->SetPointId(1, 0);
  mesh->SetCell(2, line2);

  EXPECT_EQ(mesh->GetNumberOfPoints(), 3u) << "Not all points added.";

  if (mesh->GetNumberOfCells() != 0)
  {
    EXPECT_EQ(mesh->GetNumberOfEdges(), 3u) << "Not all cells added.";
  }

  using CellIterator = MeshType::CellsContainer::Iterator;
  CellIterator       cellIterator = mesh->GetCells()->Begin();
  const unsigned int ids[] = { 0, 1, 2, 1, 2, 0, 2, 0, 1 };
  int                itIds = 0;

  while (cellIterator != mesh->GetCells()->End())
  {
    MeshType::CellType * cellptr = cellIterator.Value();
    auto *               lineCell = dynamic_cast<LineType *>(cellptr);
    lineCell->GetNameOfClass();
    QuadEdgeType *             QEGeom = lineCell->GetQEGeom();
    QuadEdgeType::IteratorGeom git = QEGeom->BeginGeomLnext();
    while (git != QEGeom->EndGeomLnext())
    {
      EXPECT_EQ(ids[itIds], *git) << "Problem with splicing edges.";
      itIds++;
      git++;
    }
    cellIterator++;
  }

  std::cout << "done!" << std::endl;
}
