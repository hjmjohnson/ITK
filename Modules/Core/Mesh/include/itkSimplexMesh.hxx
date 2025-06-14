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
#ifndef itkSimplexMesh_hxx
#define itkSimplexMesh_hxx


#include "itkProcessObject.h"
#include <algorithm>

#include "vxl_version.h"
#include "vnl/vnl_cross.h"

namespace itk
{

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SimplexMesh()
  : m_LastCellId(0)
{
  m_GeometryData = GeometryMapType::New();
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
SimplexMesh<TPixelType, VDimension, TMeshTraits>::~SimplexMesh()
{
  itkDebugMacro("Mesh Destructor ");

  const GeometryMapPointer  geometryMap = this->GetGeometryData();
  GeometryMapIterator       pointDataIterator = geometryMap->Begin();
  const GeometryMapIterator pointDataEnd = geometryMap->End();

  while (pointDataIterator != pointDataEnd)
  {
    SimplexMeshGeometry * geometry = pointDataIterator->Value();
    delete geometry;
    ++pointDataIterator;
  }
  // clear the map
  geometryMap->Initialize();
  this->ReleaseCellsMemory();
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::CopyInformation(const DataObject * data)
{
  const auto * mesh = dynamic_cast<const Superclass *>(data);

  if (mesh == nullptr)
  {
    // pointer could not be cast back down
    itkExceptionMacro("itk::Mesh::CopyInformation() cannot cast " << typeid(data).name() << " to "
                                                                  << typeid(Superclass *).name());
  }

  this->m_MaximumNumberOfRegions = mesh->GetMaximumNumberOfRegions();
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetBarycentricCoordinates(PointIdentifier idx, PointType value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->eps = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetBarycentricCoordinates(PointIdentifier idx) const -> PointType
{
  return m_GeometryData->GetElement(idx)->eps;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetReferenceMetrics(PointIdentifier idx, PointType value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->referenceMetrics = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetReferenceMetrics(PointIdentifier idx) const -> PointType
{
  return m_GeometryData->GetElement(idx)->referenceMetrics;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetPhi(PointIdentifier idx, double value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->phi = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
double
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetPhi(PointIdentifier idx) const
{
  PointType test;

  this->GetPoint(idx, &test);

  return m_GeometryData->GetElement(idx)->phi;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetMeanCurvature(PointIdentifier idx, double value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->meanCurvature = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
double
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetMeanCurvature(PointIdentifier idx) const
{
  return m_GeometryData->GetElement(idx)->meanCurvature;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetRadius(PointIdentifier idx, double value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->circleRadius = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
double
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetRadius(PointIdentifier idx) const
{
  return m_GeometryData->GetElement(idx)->circleRadius;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetDistance(PointIdentifier idx, double value)
{
  SimplexMeshGeometry * geometry = m_GeometryData->GetElement(idx);

  geometry->distance = value;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
double
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetDistance(PointIdentifier idx) const
{
  return m_GeometryData->GetElement(idx)->distance;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::AddEdge(PointIdentifier startPointId, PointIdentifier endPointId)
  -> CellIdentifier
{
  CellAutoPointer      NewCellPointer(new LineType, true);
  const CellIdentifier edgeId = m_LastCellId;

  NewCellPointer->SetPointId(0, startPointId);
  NewCellPointer->SetPointId(1, endPointId);

  this->SetCell(edgeId, NewCellPointer);
  ++m_LastCellId;
  return edgeId;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::AddFace(CellAutoPointer & cellPointer) -> CellIdentifier
{
  this->SetCell(m_LastCellId, cellPointer);
  ++m_LastCellId;
  return m_LastCellId - 1;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::ReplaceFace(CellIdentifier    replaceIndex,
                                                              CellAutoPointer & cellPointer) -> CellIdentifier
{
  // Release previous cell, if any.
  // See documentation of Mesh::SetCell().
  CellAutoPointer cellToDelete;
  this->GetCell(replaceIndex, cellToDelete);
  cellToDelete.TakeOwnership();

  // Now place the new cell and its cell data.
  this->SetCell(replaceIndex, cellPointer);
  this->SetCellData(replaceIndex, (PixelType)1.0);
  return replaceIndex;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::PrintSelf(std::ostream & os, Indent indent) const
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "LastCellId: " << static_cast<typename NumericTraits<CellIdentifier>::PrintType>(m_LastCellId)
     << std::endl;

  itkPrintSelfObjectMacro(GeometryData);
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SetGeometryData(PointIdentifier       pointId,
                                                                  SimplexMeshGeometry * geometryData)
{
  SimplexMeshGeometry * oldGeometryData = nullptr;
  if (m_GeometryData->GetElementIfIndexExists(pointId, &oldGeometryData))
  {
    delete oldGeometryData;
  }
  m_GeometryData->InsertElement(pointId, geometryData);
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetNeighbors(PointIdentifier idx) const -> IndexArray
{
  return m_GeometryData->GetElement(idx)->neighborIndices;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::GetNeighbors(PointIdentifier    idx,
                                                               unsigned int       radius,
                                                               NeighborListType * list) const -> NeighborListType *
{
  if (list == nullptr)
  {
    list = new NeighborListType();
    IndexArray neighborArray = GetNeighbors(idx);
    list->push_back(neighborArray[0]);
    list->push_back(neighborArray[1]);
    list->push_back(neighborArray[2]);

    if (radius > 0)
    {
      list = GetNeighbors(neighborArray[0], radius - 1, list);
      list = GetNeighbors(neighborArray[1], radius - 1, list);
      list = GetNeighbors(neighborArray[2], radius - 1, list);
    }
    auto it = std::find(list->begin(), list->end(), idx);
    if (it != list->end())
    {
      list->erase(it);
    }

    return list;
  }

  IndexArray neighborArray = GetNeighbors(idx);

  auto foundIt1 = std::find(list->begin(), list->end(), neighborArray[0]);
  auto foundIt2 = std::find(list->begin(), list->end(), neighborArray[1]);
  auto foundIt3 = std::find(list->begin(), list->end(), neighborArray[2]);
  auto endIt = list->end();
  bool found1 = false;
  if (foundIt1 != endIt)
  {
    found1 = true;
  }
  bool found2 = false;
  if (foundIt2 != endIt)
  {
    found2 = true;
  }
  bool found3 = false;
  if (foundIt3 != endIt)
  {
    found3 = true;
  }

  if (!found1)
  {
    list->push_back(neighborArray[0]);
  }
  if (!found2)
  {
    list->push_back(neighborArray[1]);
  }
  if (!found3)
  {
    list->push_back(neighborArray[2]);
  }

  if (radius == 0)
  {
    return list;
  }
  else
  {
    list = GetNeighbors(neighborArray[0], radius - 1, list);
    list = GetNeighbors(neighborArray[1], radius - 1, list);
    list = GetNeighbors(neighborArray[2], radius - 1, list);
    return list;
  }
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::AddNeighbor(PointIdentifier pointIdx, PointIdentifier neighborIdx)
{
  SimplexMeshGeometry * data = m_GeometryData->GetElement(pointIdx);

  for (int i = 0; i < 3; ++i)
  {
    if (data->neighborIndices[i] == ((PointIdentifier)NumericTraits<PointIdentifier>::max()))
    {
      data->neighborIndices[i] = neighborIdx;
      break;
    }
  }
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::ReplaceNeighbor(PointIdentifier pointIdx,
                                                                  PointIdentifier oldIdx,
                                                                  PointIdentifier newIdx)
{
  SimplexMeshGeometry * data = m_GeometryData->GetElement(pointIdx);

  for (int i = 0; i < 3; ++i)
  {
    if (data->neighborIndices[i] == oldIdx)
    {
      data->neighborIndices[i] = newIdx;
    }
  }
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
void
SimplexMesh<TPixelType, VDimension, TMeshTraits>::SwapNeighbors(PointIdentifier pointIdx,
                                                                PointIdentifier firstIdx,
                                                                PointIdentifier secondIdx)
{
  SimplexMeshGeometry * data = m_GeometryData->GetElement(pointIdx);
  int                   firstFound = -1;
  int                   secondFound = -1;

  for (int i = 0; i < 3; ++i)
  {
    if (data->neighborIndices[i] == firstIdx)
    {
      firstFound = i;
    }
    else if (data->neighborIndices[i] == secondIdx)
    {
      secondFound = i;
    }
  }
  if (firstFound == -1 || secondFound == -1)
  {
    itkExceptionMacro("first and second not found");
  }
  data->neighborIndices[firstFound] = secondIdx;
  data->neighborIndices[secondFound] = firstIdx;
}

template <typename TPixelType, unsigned int VDimension, typename TMeshTraits>
auto
SimplexMesh<TPixelType, VDimension, TMeshTraits>::ComputeNormal(PointIdentifier idx) const -> CovariantVectorType
{
  PointType p{};
  PointType n1{};
  PointType n2{};
  PointType n3{};

  IndexArray neighbors = this->GetNeighbors(idx);
  this->GetPoint(idx, &p);
  this->GetPoint(neighbors[0], &n1);
  this->GetPoint(neighbors[1], &n2);
  this->GetPoint(neighbors[2], &n3);

  // compute normals
  CovariantVectorType normal{};
  CovariantVectorType z;
  z.SetVnlVector(vnl_cross_3d((n2 - n1).GetVnlVector(), (n3 - n1).GetVnlVector()));
  z.Normalize();
  normal += z;

  return normal;
}
} // end namespace itk

#endif
