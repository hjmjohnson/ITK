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
#ifndef itkTriangleMeshToSimplexMeshFilter_hxx
#define itkTriangleMeshToSimplexMeshFilter_hxx

namespace itk
{
template <typename TInputMesh, typename TOutputMesh>
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::TriangleMeshToSimplexMeshFilter()
  : m_FaceSet(nullptr)
  , m_Edges(nullptr)
  , m_EdgeNeighborList(nullptr)
  , m_VertexNeighborList(nullptr)
  , m_LineCellIndices(nullptr)
  , m_CellIdxOffset(0)
  , m_IdOffset(0)
  , m_EdgeCellId(0)
  , m_HandledEdgeIds(IdVectorType::New())
{
  const OutputMeshPointer output = TOutputMesh::New();

  this->ProcessObject::SetNumberOfRequiredOutputs(1);
  this->ProcessObject::SetNthOutput(0, output.GetPointer());
}

template <typename TInputMesh, typename TOutputMesh>
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::~TriangleMeshToSimplexMeshFilter()
{
  delete m_FaceSet;
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::GenerateData()
{
  this->Initialize();
  this->CreateSimplexPoints();
  this->CreateSimplexNeighbors();
  this->CreateCells();
  this->GetOutput()->BuildCellLinks();
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::Initialize()
{

  const InputMeshType * input = this->GetInput(0);

  m_IdOffset = input->GetNumberOfCells();

  m_EdgeCellId = 0;
  m_EdgeNeighborList = EdgeNeighborListType::New();
  m_VertexNeighborList = VertexNeighborListType::New();
  m_LineCellIndices = LineCellIndexType::New();
  m_Edges = EdgeMapType::New();
  delete m_FaceSet;

  m_FaceSet = new IndexSetType();

  InputPointType v1;
  InputPointType v2;
  InputPointType v3;
  for (unsigned int idx1 = 0; idx1 < m_IdOffset; ++idx1)
  {
    m_FaceSet->insert(idx1);

    CellAutoPointer triCellPointer;
    input->GetCell(idx1, triCellPointer);
    const PointIdentifier * tp = triCellPointer->GetPointIds();
    if (!input->GetPoint(tp[0], &v1))
    {
      itkExceptionMacro("Point with id " << tp[0] << " does not exist in the input mesh");
    }
    if (!input->GetPoint(tp[1], &v2))
    {
      itkExceptionMacro("Point with id " << tp[1] << " does not exist in the input mesh");
    }
    if (!input->GetPoint(tp[2], &v3))
    {
      itkExceptionMacro("Point with id " << tp[2] << " does not exist in the input mesh");
    }

    this->CreateNewEdge(idx1, 0, tp[0], tp[1], input);
    this->CreateNewEdge(idx1, 1, tp[1], tp[2], input);
    this->CreateNewEdge(idx1, 2, tp[2], tp[0], input);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::CreateSimplexPoints()
{
  // create the points of the simplex mesh
  auto faceIterator = m_FaceSet->begin();

  const InputMeshType * input = this->GetInput(0);
  TOutputMesh *         output = this->GetOutput();

  while (faceIterator != m_FaceSet->end())
  {
    const InputPointType newPoint = ComputeFaceCenter(*faceIterator, input);
    OutputPointType      copyPoint;
    copyPoint.CastFrom(newPoint);

    const unsigned int id = *faceIterator;
    output->SetPoint(id, copyPoint);
    output->SetGeometryData(id, new itk::SimplexMeshGeometry());
    ++faceIterator;
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::CreateEdgeForTrianglePair(CellIdentifier pointIndex,
                                                                                    CellIdentifier boundaryId,
                                                                                    TOutputMesh *  outputMesh)
{
  const EdgeIdentifierType facePair = m_EdgeNeighborList->GetElement(boundaryId);

  if (facePair.first == pointIndex)
  {
    outputMesh->AddNeighbor(pointIndex, facePair.second);
  }
  else
  {
    outputMesh->AddNeighbor(pointIndex, facePair.first);
  }

  if (!m_HandledEdgeIds->IndexExists(boundaryId))
  {
    const CellIdentifier edgeId = outputMesh->AddEdge(facePair.first, facePair.second);
    m_LineCellIndices->InsertElement(facePair, edgeId);
    m_HandledEdgeIds->InsertElement(boundaryId, edgeId);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::CreateSimplexNeighbors()
{
  TOutputMesh * output = this->GetOutput(0);

  // add neighbor vertices
  const OutputPointsContainerPointer outputPointsContainer = output->GetPoints();
  OutputPointsContainerIterator      points = outputPointsContainer->Begin();

  const InputBoundaryAssignmentsContainerPointer cntlines = this->GetInput(0)->GetBoundaryAssignments(1);

  while (points != outputPointsContainer->End())
  {
    const PointIdentifier                    idx = points.Index();
    const InputBoundnaryAssignmentIdentifier key0(idx, 0);
    const InputBoundnaryAssignmentIdentifier key1(idx, 1);
    const InputBoundnaryAssignmentIdentifier key2(idx, 2);

    const CellIdentifier tp0 = cntlines->GetElement(key0);
    const CellIdentifier tp1 = cntlines->GetElement(key1);
    const CellIdentifier tp2 = cntlines->GetElement(key2);

    CreateEdgeForTrianglePair(idx, tp0, output);
    CreateEdgeForTrianglePair(idx, tp1, output);
    CreateEdgeForTrianglePair(idx, tp2, output);

    ++points;
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::CreateNewEdge(CellIdentifier        currentCellId,
                                                                        CellFeatureIdentifier featureId,
                                                                        PointIdentifier       startPointId,
                                                                        PointIdentifier       endPointId,
                                                                        const InputMeshType * input)
{
  CellIdentifier boundaryId;

  // The filter shouldn't modify the input...
  auto * nonConstInput = const_cast<InputMeshType *>(input);

  const EdgeIdentifierType edge = std::make_pair(startPointId, endPointId);
  const EdgeIdentifierType edgeInv = std::make_pair(endPointId, startPointId);

  if (!m_Edges->IndexExists(edge) && !m_Edges->IndexExists(edgeInv))
  {
    boundaryId = m_IdOffset + m_EdgeCellId;
    m_Edges->InsertElement(edge, boundaryId);
    m_NewInputMeshCellPointer.TakeOwnership(new LineType);
    m_NewInputMeshCellPointer->SetPointId(0, startPointId);
    m_NewInputMeshCellPointer->SetPointId(1, endPointId);
    nonConstInput->SetCell(boundaryId, m_NewInputMeshCellPointer);
    ++m_EdgeCellId;
  }
  else
  {
    if (m_Edges->IndexExists(edge))
    {
      boundaryId = m_Edges->GetElement(edge);
    }
    else
    {
      boundaryId = m_Edges->GetElement(edgeInv);
    }
  }
  nonConstInput->SetBoundaryAssignment(1, currentCellId, featureId, boundaryId);

  if (!m_EdgeNeighborList->IndexExists(boundaryId))
  {
    const EdgeIdentifierType neighboringCells =
      std::make_pair(currentCellId, (CellIdentifier)NumericTraits<CellIdentifier>::max());
    m_EdgeNeighborList->InsertElement(boundaryId, neighboringCells);
  }
  else
  {
    EdgeIdentifierType neighboringCells = m_EdgeNeighborList->GetElement(boundaryId);

    if (neighboringCells.second == NumericTraits<CellIdentifier>::max())
    {
      neighboringCells.second = currentCellId;
    }
    m_EdgeNeighborList->InsertElement(boundaryId, neighboringCells);
  }

  if (!m_VertexNeighborList->IndexExists(startPointId))
  {
    IndexSetType neighborEdges;
    neighborEdges.insert(boundaryId);
    m_VertexNeighborList->InsertElement(startPointId, neighborEdges);
  }
  else
  {
    IndexSetType neighborEdges = m_VertexNeighborList->GetElement(startPointId);
    neighborEdges.insert(boundaryId);
    m_VertexNeighborList->InsertElement(startPointId, neighborEdges);
  }

  if (!m_VertexNeighborList->IndexExists(endPointId))
  {
    IndexSetType neighborEdges;
    neighborEdges.insert(boundaryId);
    m_VertexNeighborList->InsertElement(endPointId, neighborEdges);
  }
  else
  {
    IndexSetType neighborEdges = m_VertexNeighborList->GetElement(endPointId);
    neighborEdges.insert(boundaryId);
    m_VertexNeighborList->InsertElement(endPointId, neighborEdges);
  }
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "FaceSet: " << m_FaceSet << std::endl;

  itkPrintSelfObjectMacro(Edges);
  itkPrintSelfObjectMacro(EdgeNeighborList);
  itkPrintSelfObjectMacro(VertexNeighborList);
  itkPrintSelfObjectMacro(LineCellIndices);

  os << indent << "IdOffset: " << static_cast<typename NumericTraits<PointIdentifier>::PrintType>(m_IdOffset)
     << std::endl;
  os << indent << "EdgeCellId: " << static_cast<typename NumericTraits<CellIdentifier>::PrintType>(m_EdgeCellId)
     << std::endl;
  os << indent
     << "HandledEdgeIds: " << static_cast<typename NumericTraits<IdVectorPointer>::PrintType>(m_HandledEdgeIds)
     << std::endl;
  os << indent << "IdOffset: " << static_cast<typename NumericTraits<PointIdentifier>::PrintType>(m_IdOffset)
     << std::endl;

  // ToDo
  // os << indent << "NewInputMeshCellPointer: " << m_NewInputMeshCellPointer << std::endl;
  // os << indent << "NewSimplexCellPointer: " << m_NewSimplexCellPointer << std::endl;
}

template <typename TInputMesh, typename TOutputMesh>
void
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::CreateCells()
{
  const InputPointsContainer *      pointsContainer = this->GetInput(0)->GetPoints();
  InputPointsContainerConstIterator points = pointsContainer->Begin();
  TOutputMesh *                     outputMesh = this->GetOutput();

  using MapType = itk::MapContainer<CellIdentifier, CellIdentifier>;

  while (points != pointsContainer->End())
  {
    const PointIdentifier idx = points.Index();
    IndexSetType          vertexNeighbors = m_VertexNeighborList->GetElement(idx);

    auto iterator1 = vertexNeighbors.begin();

    auto           tmpMap = MapType::New();
    CellIdentifier startIdx = NumericTraits<CellIdentifier>::max();
    CellIdentifier lastIdx = 0;
    CellIdentifier wrongIdx = 0;

    while (lastIdx != startIdx)
    {
      if (startIdx == NumericTraits<CellIdentifier>::max())
      {
        const EdgeIdentifierType neighboringCells = m_EdgeNeighborList->GetElement(*iterator1);
        startIdx = neighboringCells.first;
        tmpMap->InsertElement(neighboringCells.first, neighboringCells.second);

        lastIdx = neighboringCells.second;
        wrongIdx = neighboringCells.first;
      }
      else
      {
        auto iterator2 = vertexNeighbors.begin();
        while (iterator2 != vertexNeighbors.end())
        {
          const EdgeIdentifierType compare = m_EdgeNeighborList->GetElement(*iterator2);
          if (compare.first == lastIdx && compare.second != wrongIdx)
          {
            tmpMap->InsertElement(compare.first, compare.second);
            lastIdx = compare.second;
            wrongIdx = compare.first;
            break;
          }
          if (compare.second == lastIdx && compare.first != wrongIdx)
          {
            tmpMap->InsertElement(compare.second, compare.first);
            lastIdx = compare.first;
            wrongIdx = compare.second;
            break;
          }
          ++iterator2;
        }
      }
      ++iterator1;
    }

    // create a new cell
    m_NewSimplexCellPointer.TakeOwnership(new OutputPolygonType);
    PointIdentifier       vertexIdx{};
    CellIdentifier        nextIdx = startIdx;
    CellFeatureIdentifier featureId = 0;

    const CellIdentifier faceIndex = outputMesh->AddFace(m_NewSimplexCellPointer);

    while (tmpMap->IndexExists(nextIdx))
    {
      m_NewSimplexCellPointer->SetPointId(vertexIdx++, nextIdx);
      const CellIdentifier newIdx = tmpMap->GetElement(nextIdx);

      const EdgeIdentifierType line = std::make_pair(nextIdx, newIdx);
      const EdgeIdentifierType lineInv = std::make_pair(newIdx, nextIdx);

      CellIdentifier edgeIdx{};

      if (m_LineCellIndices->IndexExists(line))
      {
        edgeIdx = m_LineCellIndices->GetElement(line);
      }
      else if (m_LineCellIndices->IndexExists(lineInv))
      {
        edgeIdx = m_LineCellIndices->GetElement(lineInv);
      }
      else
      {
        std::cout << "error!!! " << std::endl;
      }
      outputMesh->SetBoundaryAssignment(1, faceIndex, featureId++, edgeIdx);

      if (newIdx == startIdx)
      {
        break;
      }

      nextIdx = newIdx;

      ++featureId;
    }
    ++points;
  }
}

template <typename TInputMesh, typename TOutputMesh>
auto
TriangleMeshToSimplexMeshFilter<TInputMesh, TOutputMesh>::ComputeFaceCenter(CellIdentifier        faceId,
                                                                            const InputMeshType * inputMesh)
  -> InputPointType
{
  CellAutoPointer cellPointer;
  inputMesh->GetCell(faceId, cellPointer);
  const PointIdentifier * tp = cellPointer->GetPointIds();
  InputPointType          v1;
  if (!inputMesh->GetPoint(tp[0], &v1))
  {
    itkExceptionMacro("Point with id " << tp[0] << " does not exist in the input mesh");
  }
  InputPointType v2;
  if (!inputMesh->GetPoint(tp[1], &v2))
  {
    itkExceptionMacro("Point with id " << tp[1] << " does not exist in the input mesh");
  }
  InputPointType v3;
  if (!inputMesh->GetPoint(tp[2], &v3))
  {
    itkExceptionMacro("Point with id " << tp[2] << " does not exist in the input mesh");
  }

  InputPointType result;
  result[0] = (static_cast<double>(v1[0] + v2[0] + v3[0])) / 3.0;
  result[1] = (static_cast<double>(v1[1] + v2[1] + v3[1])) / 3.0;
  result[2] = (static_cast<double>(v1[2] + v2[2] + v3[2])) / 3.0;

  return result;
}
} // namespace itk

#endif //_TRIANGLE_MESH_TO_SIMPLEX_MESH_FILTER_TXX
