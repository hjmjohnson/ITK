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
#ifndef itkKernelTransform_h
#define itkKernelTransform_h

#include "itkTransform.h"
#include "itkMatrix.h"
#include "itkPointSet.h"
#include <deque>
#include <cmath>
#include "vnl/vnl_matrix_fixed.h"
#include "vnl/vnl_matrix.h"
#include "vnl/vnl_vector.h"
#include "vnl/vnl_vector_fixed.h"
#include "vnl/algo/vnl_svd.h"

namespace itk
{
/**
 * \class KernelTransform
 * Intended to be a base class for elastic body spline and thin plate spline.
 * This is implemented in as straightforward a manner as possible from
 * \cite davis1997. Notation closely follows the paper, so if you have it
 * in front of you, this code will make a lot more sense.
 *
 * KernelTransform:
 *  Provides support for defining source and target landmarks
 *  Defines a number of data types used in the computations
 *  Defines the mathematical framework used to compute all splines,
 *    so that subclasses need only provide a kernel specific to
 *    that spline
 *
 * This formulation allows the stiffness of the spline to
 * be adjusted, allowing the spline to vary from interpolating the
 * landmarks to approximating the landmarks.  This part of the
 * formulation is based on \cite sprengel1996.
 *
 *
 * \ingroup ITKTransform
 */
template <typename TParametersValueType, unsigned int VDimension>
class ITK_TEMPLATE_EXPORT KernelTransform : public Transform<TParametersValueType, VDimension, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(KernelTransform);

  /** Standard class type aliases. */
  using Self = KernelTransform;
  using Superclass = Transform<TParametersValueType, VDimension, VDimension>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(KernelTransform);

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro(Self);

  /** Dimension of the domain space. */
  static constexpr unsigned int SpaceDimension = VDimension;

  /** Scalar type. */
  using typename Superclass::ScalarType;

  /** Parameters type. */
  using typename Superclass::FixedParametersType;
  using typename Superclass::ParametersType;

  /** Jacobian types. */
  using typename Superclass::JacobianType;
  using typename Superclass::JacobianPositionType;
  using typename Superclass::InverseJacobianPositionType;

  /** Transform category type. */
  using typename Superclass::TransformCategoryEnum;

  /** Standard coordinate point type for this class. */
  using typename Superclass::InputPointType;
  using typename Superclass::OutputPointType;

  /** Standard vector type for this class. */
  using typename Superclass::InputVectorType;
  using typename Superclass::OutputVectorType;

  /** Standard covariant vector type for this class */
  using typename Superclass::InputCovariantVectorType;
  using typename Superclass::OutputCovariantVectorType;

  /** Standard vnl_vector type for this class. */
  using typename Superclass::InputVnlVectorType;
  using typename Superclass::OutputVnlVectorType;

  /** The number of parameters defining this transform. */
  using typename Superclass::NumberOfParametersType;

  /** PointList type alias. This type is used for maintaining lists of points,
   * specifically, the source and target landmark lists. */
  using PointSetTraitsType =
    DefaultStaticMeshTraits<TParametersValueType, VDimension, VDimension, TParametersValueType, TParametersValueType>;
  using PointSetType = PointSet<InputPointType, VDimension, PointSetTraitsType>;

  using PointSetPointer = typename PointSetType::Pointer;
  using PointsContainer = typename PointSetType::PointsContainer;
  using PointsIterator = typename PointSetType::PointsContainerIterator;
  using PointsConstIterator = typename PointSetType::PointsContainerConstIterator;
  using PointIdentifier = typename PointSetType::PointIdentifier;

  /** VectorSet type alias. */
  using VectorSetType = itk::VectorContainer<InputVectorType>;
  using VectorSetPointer = typename VectorSetType::Pointer;

  /** Get/Set the source landmarks list, which we will denote \f$ p \f$. */
  /** @ITKStartGrouping */
  itkGetModifiableObjectMacro(SourceLandmarks, PointSetType); // NOTE: This is used to circumvent the SetTargetLandmarks
  virtual void
  SetSourceLandmarks(PointSetType *);
  /** @ITKEndGrouping */
  /** Get the target landmarks list, which we will denote  \f$ q \f$. */
  /** @ITKStartGrouping */
  itkGetModifiableObjectMacro(TargetLandmarks, PointSetType); // NOTE: This is used to circumvent the SetTargetLandmarks
  virtual void
  SetTargetLandmarks(PointSetType *);
  /** @ITKEndGrouping */
  /** Get the displacements list, which we will denote \f$ d \f$,
   * where \f$ d_i = q_i - p_i \f$. */
  itkGetModifiableObjectMacro(Displacements, VectorSetType);

  /** Compute W matrix. */
  void
  ComputeWMatrix();

  /** Compute the position of point in the new space */
  OutputPointType
  TransformPoint(const InputPointType & thisPoint) const override;

  /** These vector transforms are not implemented for this transform */
  /** @ITKStartGrouping */
  using Superclass::TransformVector;
  OutputVectorType
  TransformVector(const InputVectorType &) const override
  {
    itkExceptionMacro("TransformVector(const InputVectorType &) is not implemented for KernelTransform");
  }
  /** @ITKEndGrouping */
  OutputVnlVectorType
  TransformVector(const InputVnlVectorType &) const override
  {
    itkExceptionMacro("TransformVector(const InputVnlVectorType &) is not implemented for KernelTransform");
  }

  /**  Method to transform a CovariantVector. */
  /** @ITKStartGrouping */
  using Superclass::TransformCovariantVector;
  OutputCovariantVectorType
  TransformCovariantVector(const InputCovariantVectorType &) const override
  {
    itkExceptionMacro(
      << "TransformCovariantVector(const InputCovariantVectorType &) is not implemented for KernelTransform");
  }
  /** @ITKEndGrouping */
  /** 'I' (identity) matrix type alias. */
  using IMatrixType = vnl_matrix_fixed<TParametersValueType, VDimension, VDimension>;

  /** Compute the Jacobian Matrix of the transformation at one point */
  void
  ComputeJacobianWithRespectToParameters(const InputPointType & p, JacobianType & jacobian) const override;

  void
  ComputeJacobianWithRespectToPosition(const InputPointType &, JacobianPositionType &) const override
  {
    itkExceptionMacro("ComputeJacobianWithRespectToPosition not yet implemented "
                      "for "
                      << this->GetNameOfClass());
  }
  using Superclass::ComputeJacobianWithRespectToPosition;

  /** Set the Transformation Parameters and update the internal transformation.
   * The parameters represent the source landmarks. Each landmark point is
   * represented by VDimension doubles. All the landmarks are concatenated to
   * form one flat Array<double>. */
  void
  SetParameters(const ParametersType &) override;

  /** Set Transform Fixed Parameters:
   *     To support the transform file writer this function was
   *     added to set the target landmarks similar to the
   *     SetParameters function setting the source landmarks
   */
  void
  SetFixedParameters(const FixedParametersType &) override;

  /** Update the Parameters array from the landmarks coordinates. */
  virtual void
  UpdateParameters() const;

  /** Get the Transformation Parameters - Gets the Source Landmarks */
  const ParametersType &
  GetParameters() const override;

  /** Get Transform Fixed Parameters - Gets the Target Landmarks */
  const FixedParametersType &
  GetFixedParameters() const override;

  /** This transform is not linear, because the transformation of a linear
   * combination of points is not equal to the linear combination of the
   * transformations of individual points */
  TransformCategoryEnum
  GetTransformCategory() const override
  {
    return Self::TransformCategoryEnum::Spline;
  }

  /** Stiffness of the spline.  A stiffness of zero results in the
   * standard interpolating spline.  A non-zero stiffness allows the
   * spline to approximate rather than interpolate the landmarks.
   * Stiffness values are usually rather small, typically in the range
   * of 0.001 to 0.1. The approximating spline formulation is based on
   * \cite sprengel1996.
   */
  /** @ITKStartGrouping */
  itkSetClampMacro(Stiffness, double, 0.0, NumericTraits<double>::max());
  itkGetConstMacro(Stiffness, double);
  /** @ITKEndGrouping */
protected:
  KernelTransform();
  ~KernelTransform() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

public:
  /** 'G' matrix type alias. */
  using GMatrixType = vnl_matrix_fixed<TParametersValueType, VDimension, VDimension>;

  /** 'L' matrix type alias. */
  using LMatrixType = vnl_matrix<TParametersValueType>;

  /** 'K' matrix type alias. */
  using KMatrixType = vnl_matrix<TParametersValueType>;

  /** 'P' matrix type alias. */
  using PMatrixType = vnl_matrix<TParametersValueType>;

  /** 'Y' matrix type alias. */
  using YMatrixType = vnl_matrix<TParametersValueType>;

  /** 'W' matrix type alias. */
  using WMatrixType = vnl_matrix<TParametersValueType>;

  /** 'D' matrix type alias. Deformation component */
  using DMatrixType = vnl_matrix<TParametersValueType>;

  /** 'A' matrix type alias. Rotational part of the Affine component */
  using AMatrixType = vnl_matrix_fixed<TParametersValueType, VDimension, VDimension>;

  /** 'B' matrix type alias. Translational part of the Affine component */
  using BMatrixType = vnl_vector_fixed<TParametersValueType, VDimension>;

  /** Row matrix type alias. */
  using RowMatrixType = vnl_matrix_fixed<TParametersValueType, 1, VDimension>;

  /** Column matrix type alias. */
  using ColumnMatrixType = vnl_matrix_fixed<TParametersValueType, VDimension, 1>;

protected:
  /** Compute G(x)
   * This is essentially the kernel of the transform.
   * By overriding this method, we can obtain (among others):
   *    Elastic body spline
   *    Thin plate spline
   *    Volume spline */
  virtual void
  ComputeG(const InputVectorType & landmarkVector, GMatrixType & gmatrix) const;

  /** Compute a G(x) for a point to itself (i.e. for the block diagonal
   * elements of the matrix K. Parameter indicates for which landmark
   * the reflexive G is to be computed. The default implementation for
   * the reflexive contribution is a diagonal matrix where the diagonal
   * elements are the stiffness of the spline.
   *
   * \warning this method is not thread-safe. However this method is called
   * only through ComputeWMatrix() that is itself normally called from a single
   * thread during the initialization of the Transform. */
  virtual const GMatrixType & ComputeReflexiveG(PointsIterator) const;

  /** Compute the contribution of the landmarks weighted by the kernel function
      to the global deformation of the space  */
  virtual void
  ComputeDeformationContribution(const InputPointType & thisPoint, OutputPointType & result) const;

  /** Compute K matrix. */
  void
  ComputeK();

  /** Compute L matrix. */
  void
  ComputeL();

  /** Compute P matrix. */
  void
  ComputeP();

  /** Compute Y matrix. */
  void
  ComputeY();

  /** Compute displacements \f$ q_i - p_i \f$. */
  void
  ComputeD();

  /** Reorganize the components of W into
    D (deformable), A (rotation part of affine)
    and B (translational part of affine ) components.
    \warning This method release the memory of the W Matrix  */
  void
  ReorganizeW();

  /** Stiffness parameter */
  double m_Stiffness{};

  /** The list of displacements.
   * d[i] = q[i] - p[i]; */
  VectorSetPointer m_Displacements{};

  /** The L matrix. */
  LMatrixType m_LMatrix{};

  /** The K matrix. */
  KMatrixType m_KMatrix{};

  /** The P matrix. */
  PMatrixType m_PMatrix{};

  /** The Y matrix. */
  YMatrixType m_YMatrix{};

  /** The W matrix. */
  WMatrixType m_WMatrix{};

  /** The Deformation matrix.
      This is an auxiliary matrix that will hold the
      Deformation (non-affine) part of the transform.
      Those are the coefficients that will multiply the
      Kernel function */
  DMatrixType m_DMatrix{};

  /** Rotational/Shearing part of the Affine component of the Transformation */
  AMatrixType m_AMatrix{};

  /** Translational part of the Affine component of the Transformation */
  BMatrixType m_BVector{};

  /** The G matrix.
   *  It is made mutable because m_GMatrix was made an ivar
   *  only to avoid copying the matrix at return time */
  mutable GMatrixType m_GMatrix{};

  /** Has the W matrix been computed? */
  bool m_WMatrixComputed{};

  /** Identity matrix. */
  IMatrixType m_I{};

  /** The list of source landmarks, denoted 'p'. */
  PointSetPointer m_SourceLandmarks{};

  /** The list of target landmarks, denoted 'q'. */
  PointSetPointer m_TargetLandmarks{};

private:
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkKernelTransform.hxx"
#endif

#endif // itkKernelTransform_h
