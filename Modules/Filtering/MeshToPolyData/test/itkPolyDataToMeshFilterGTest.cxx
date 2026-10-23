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
#include "itkMesh.h"
#include "itkPolyData.h"
#include "itkPolyDataToMeshFilter.h"

#include "itkGTest.h"

namespace
{
template <typename TPixelType>
void
MakePolyDataSample(itk::PolyData<TPixelType> *);
} // namespace

TEST(PolyDataToMeshFilter, ConvertedLegacyTest)
{

  using PixelType = double;

  using PolyDataType = itk::PolyData<PixelType>;
  PolyDataType::Pointer polyData = PolyDataType::New();

  MakePolyDataSample<PixelType>(polyData);

  using FilterType = itk::PolyDataToMeshFilter<PolyDataType>;
  FilterType::Pointer filter = FilterType::New();

  filter->SetInput(polyData);

  EXPECT_NO_THROW(filter->Update());

  using MeshType = FilterType::OutputMeshType;
  MeshType::Pointer meshResult = filter->GetOutput();

  EXPECT_EQ(meshResult->GetNumberOfPoints(), polyData->GetNumberOfPoints());
  EXPECT_EQ(meshResult->GetPoint(0)[0], 1);
  EXPECT_EQ(meshResult->GetPoint(0)[1], 3);
  EXPECT_EQ(meshResult->GetPoint(0)[2], 5);
  EXPECT_EQ(meshResult->GetPoint(1)[0], 4);
  EXPECT_EQ(meshResult->GetPoint(1)[1], 6);
  EXPECT_EQ(meshResult->GetPoint(1)[2], 8);
  EXPECT_EQ(meshResult->GetPoint(2)[0], 3);
  EXPECT_EQ(meshResult->GetPoint(2)[1], 5);
  EXPECT_EQ(meshResult->GetPoint(2)[2], 7);

  ASSERT_EQ(meshResult->GetNumberOfCells(), 7u);

  // Verify vertex cells
  typename MeshType::CellAutoPointer cellPtr;
  meshResult->GetCell(0, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 1u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 4u);
  meshResult->GetCell(1, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 1u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 7u);

  // Verify line cells
  meshResult->GetCell(2, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 3u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 3u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[1], 4u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[2], 5u);
  meshResult->GetCell(3, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 2u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 7u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[1], 8u);

  // Verify triangle strips (now cells
  meshResult->GetCell(4, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 3u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 0u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[1], 2u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[2], 1u);
  meshResult->GetCell(5, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 3u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 2u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[1], 1u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[2], 3u);


  // Verify triangle cells
  meshResult->GetCell(6, cellPtr);
  ASSERT_EQ(cellPtr->GetNumberOfPoints(), 3u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[0], 0u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[1], 1u);
  EXPECT_EQ(cellPtr->GetPointIdsContainer()[2], 2u);
}

namespace
{
// From itkPolyDataTest.cxx
template <typename TPixelType>
void
MakePolyDataSample(itk::PolyData<TPixelType> * polyData)
{
  using PolyDataType = itk::PolyData<TPixelType>;

  polyData->Initialize();

  using PointsContainerType = typename PolyDataType::PointsContainer;
  typename PointsContainerType::Pointer pointsContainer = PointsContainerType::New();

  typename PolyDataType::PointType point;
  point[0] = 1.0;
  point[1] = 3.0;
  point[2] = 5.0;
  pointsContainer->InsertElement(0, point);
  point[0] = 2.0;
  point[1] = 4.0;
  point[2] = 6.0;
  pointsContainer->InsertElement(1, point);
  point[0] = 3.0;
  point[1] = 5.0;
  point[2] = 7.0;
  pointsContainer->InsertElement(2, point);
  polyData->SetPoints(pointsContainer);

  point[0] = 4.0;
  point[1] = 6.0;
  point[2] = 8.0;
  polyData->SetPoint(1, point);

  using CellContainerType = typename PolyDataType::CellsContainer;
  typename CellContainerType::Pointer vertices = CellContainerType::New();
  vertices->InsertElement(0, 1);
  vertices->InsertElement(1, 4);
  vertices->InsertElement(2, 1);
  vertices->InsertElement(3, 7);
  polyData->SetVertices(vertices);

  typename CellContainerType::Pointer lines = CellContainerType::New();
  lines->InsertElement(0, 3);
  lines->InsertElement(1, 3);
  lines->InsertElement(2, 4);
  lines->InsertElement(3, 5);

  lines->InsertElement(4, 2);
  lines->InsertElement(5, 7);
  lines->InsertElement(6, 8);
  polyData->SetLines(lines);

  typename CellContainerType::Pointer strips = CellContainerType::New();
  strips->InsertElement(0, 4);
  strips->InsertElement(1, 0);
  strips->InsertElement(2, 2);
  strips->InsertElement(3, 1);
  strips->InsertElement(4, 3);
  polyData->SetTriangleStrips(strips);

  typename CellContainerType::Pointer polygons = CellContainerType::New();
  polygons->InsertElement(0, 3);
  polygons->InsertElement(1, 0);
  polygons->InsertElement(2, 1);
  polygons->InsertElement(3, 2);
  polyData->SetPolygons(polygons);

  return;
}
} // namespace
