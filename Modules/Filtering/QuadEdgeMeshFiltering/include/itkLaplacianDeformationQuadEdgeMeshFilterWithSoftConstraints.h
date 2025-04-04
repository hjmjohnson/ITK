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
#ifndef itkLaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints_h
#define itkLaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints_h

#include "itkLaplacianDeformationQuadEdgeMeshFilter.h"

namespace itk
{
/** \class LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints
 *
 *  \brief Laplacian deformation with soft constraints (approximating
 *  displacement for handle points).
 *
 * Laplacian mesh deformation offers the ability to deform 3D surface mesh
 * while preserving local details.
 *
 * In this context output mesh vertices are somehow closed to provided output
 * locations, the weight associated to one constrain can be set by the means of
 * m_Lambda (for all constraints), or for one particular constraint by using
 * SetLocalLambda
 *
 * For details, see https://doi.org/10.54294/s91axg
 *
 *  \ingroup ITKQuadEdgeMeshFiltering
 */
template <class TInputMesh, class TOutputMesh, class TSolverTraits>
class ITK_TEMPLATE_EXPORT LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints
  : public LaplacianDeformationQuadEdgeMeshFilter<TInputMesh, TOutputMesh, TSolverTraits>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints);

  /** Basic types. */
  using Self = LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints;
  using Superclass = LaplacianDeformationQuadEdgeMeshFilter<TInputMesh, TOutputMesh, TSolverTraits>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Input types. */
  using InputMeshType = TInputMesh;

  static constexpr unsigned int InputPointDimension = InputMeshType::PointDimension;

  /** Output types. */
  using OutputMeshType = TOutputMesh;
  using typename Superclass::OutputPointType;
  using typename Superclass::OutputCoordinateType;
  using typename Superclass::OutputPointIdentifier;

  static constexpr unsigned int OutputPointDimension = OutputMeshType::PointDimension;

  using SolverTraits = TSolverTraits;
  using typename Superclass::ValueType;
  using typename Superclass::MatrixType;
  using typename Superclass::VectorType;

  itkNewMacro(Self);
  itkOverrideGetNameOfClassMacro(LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints);

  itkSetMacro(Lambda, OutputCoordinateType);
  itkGetMacro(Lambda, OutputCoordinateType);

  void
  SetLocalLambda(OutputPointIdentifier vId, OutputCoordinateType iL);

protected:
  LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints();
  ~LaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /**
   *  \brief Fill matrix iM and vectors Bx and m_By depending on if one
   *  vertex is on the border or not.
   */
  void
  FillMatrix(MatrixType & iM, VectorType & iBx, VectorType & iBy, VectorType & iBz);

  void
  GenerateData() override;

  using typename Superclass::ConstraintMapType;
  using typename Superclass::ConstraintMapConstIterator;

  using typename Superclass::OutputMapPointIdentifier;
  using typename Superclass::OutputMapPointIdentifierIterator;
  using typename Superclass::OutputMapPointIdentifierConstIterator;


  using typename Superclass::RowType;
  using typename Superclass::RowConstIterator;
  using typename Superclass::RowIterator;

  void
  ComputeVertexIdMapping() override;

  OutputCoordinateType m_Lambda{};
  OutputCoordinateType m_LambdaSquare{};

  std::unordered_map<OutputPointIdentifier, OutputCoordinateType> m_LocalLambdaSquare{};
};
} // end namespace itk

#include "itkLaplacianDeformationQuadEdgeMeshFilterWithSoftConstraints.hxx"

#endif
