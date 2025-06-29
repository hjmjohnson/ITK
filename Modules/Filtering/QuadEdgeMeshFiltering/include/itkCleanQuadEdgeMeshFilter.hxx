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
#ifndef itkCleanQuadEdgeMeshFilter_hxx
#define itkCleanQuadEdgeMeshFilter_hxx

#include "itkMath.h"

namespace itk
{

template <typename TInputMesh, typename TOutputMesh>
CleanQuadEdgeMeshFilter<TInputMesh, TOutputMesh>::CleanQuadEdgeMeshFilter()
  : m_AbsoluteTolerance(InputCoordinateType{})
  , m_RelativeTolerance(InputCoordinateType{})
  , m_BoundingBox(BoundingBoxType::New())
  , m_Criterion(CriterionType::New())
  , m_Decimation(DecimationType::New())
{
  this->m_Criterion->SetTopologicalChange(false);
  this->m_Decimation->SetCriterion(this->m_Criterion);
}


template <typename TInputMesh, typename TOutputMesh>
void
CleanQuadEdgeMeshFilter<TInputMesh, TOutputMesh>::GenerateData()
{
  constexpr InputCoordinateType zeroValue{};

  InputCoordinateType absoluteToleranceSquared = this->m_AbsoluteTolerance * this->m_AbsoluteTolerance;
  if ((Math::ExactlyEquals(this->m_AbsoluteTolerance, zeroValue)) &&
      (Math::NotExactlyEquals(this->m_RelativeTolerance, zeroValue)))
  {
    this->m_BoundingBox->SetPoints(this->GetInput()->GetPoints());
    this->m_BoundingBox->ComputeBoundingBox();

    absoluteToleranceSquared =
      this->m_RelativeTolerance * this->m_RelativeTolerance * this->m_BoundingBox->GetDiagonalLength2();
  }

  this->MergePoints(absoluteToleranceSquared);
  this->CleanPoints();
}


template <typename TInputMesh, typename TOutputMesh>
void
CleanQuadEdgeMeshFilter<TInputMesh, TOutputMesh>::MergePoints(const InputCoordinateType absoluteToleranceSquared)
{
  const OutputMeshPointer output = this->GetOutput();

  this->m_Criterion->SetMeasureBound(absoluteToleranceSquared);

  this->m_Decimation->SetInput(this->GetInput());
  this->m_Decimation->Update();

  const InputMeshPointer decimatedMesh = this->m_Decimation->GetOutput();

  InputPointsContainerIterator       pointsIt = decimatedMesh->GetPoints()->Begin();
  const InputPointsContainerIterator pointsItEnd = decimatedMesh->GetPoints()->End();

  OutputPointType outputPoint;

  while (pointsIt != pointsItEnd)
  {
    outputPoint.CastFrom(pointsIt.Value());
    output->SetPoint(pointsIt.Index(), outputPoint);
    ++pointsIt;
  }

  // Copy Edge Cells
  InputCellsContainerIterator cellIt = decimatedMesh->GetEdgeCells()->Begin();
  InputCellsContainerIterator cellItEnd = decimatedMesh->GetEdgeCells()->End();

  while (cellIt != cellItEnd)
  {
    auto qeCell = dynamic_cast<InputEdgeCellType *>(cellIt.Value());
    auto qeGeometry = qeCell->GetQEGeom();
    output->AddEdgeWithSecurePointList(qeGeometry->GetOrigin(), qeGeometry->GetDestination());
    ++cellIt;
  }

  // Copy cells
  cellIt = decimatedMesh->GetCells()->Begin();
  cellItEnd = decimatedMesh->GetCells()->End();

  while (cellIt != cellItEnd)
  {
    auto polygonCell = dynamic_cast<InputPolygonCellType *>(cellIt.Value());
    if (polygonCell)
    {
      InputPointIdList points;

      for (InputPointsIdInternalIterator pit = polygonCell->InternalPointIdsBegin();
           pit != polygonCell->InternalPointIdsEnd();
           ++pit)
      {
        points.push_back((*pit));
      }
      output->AddFaceWithSecurePointList(points);
    }
    ++cellIt;
  }
}


template <typename TInputMesh, typename TOutputMesh>
void
CleanQuadEdgeMeshFilter<TInputMesh, TOutputMesh>::CleanPoints()
{
  const OutputMeshPointer output = this->GetOutput();

  OutputPointsContainerIterator       p_it = output->GetPoints()->Begin();
  const OutputPointsContainerIterator p_end = output->GetPoints()->End();
  OutputPointIdentifier               id(0);

  while (p_it != p_end)
  {
    id = p_it->Index();
    if (output->FindEdge(id) == nullptr)
    {
      output->DeletePoint(id);
    }
    ++p_it;
  }

  output->SqueezePointsIds();
}


template <typename TInputMesh, typename TOutputMesh>
void
CleanQuadEdgeMeshFilter<TInputMesh, TOutputMesh>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "AbsoluteTolerance: " << m_AbsoluteTolerance << std::endl;
  os << indent << "RelativeTolerance: " << m_RelativeTolerance << std::endl;
}

} // end namespace itk

#endif
