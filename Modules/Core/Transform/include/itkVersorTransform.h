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
#ifndef itkVersorTransform_h
#define itkVersorTransform_h

#include <iostream>
#include "itkRigid3DTransform.h"
#include "vnl/vnl_quaternion.h"

namespace itk
{
/** \class VersorTransform
 *
 * VersorTransform of a vector space (e.g. space coordinates)
 *
 * This transform applies a rotation to the space. Rotation is about
 * a user specified center.
 *
 * The serialization of the optimizable parameters is an array of 3 elements
 * representing the right part of the versor.
 *
 * The serialization of the fixed parameters is an array of 3 elements defining
 * the center of rotation.
 *
 * TODO: Need to make sure that the translation parameters in the baseclass
 * cannot be set to non-zero values.
 *
 *
 * \ingroup ITKTransform
 */
template <typename TParametersValueType = double>
class ITK_TEMPLATE_EXPORT VersorTransform : public Rigid3DTransform<TParametersValueType>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(VersorTransform);

  /** Standard Self Typedef */
  using Self = VersorTransform;
  using Superclass = Rigid3DTransform<TParametersValueType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(VersorTransform);

  /** New macro for creation of through a Smart Pointer */
  itkNewMacro(Self);

  /** Dimension of parameters */
  static constexpr unsigned int SpaceDimension = 3;
  static constexpr unsigned int InputSpaceDimension = 3;
  static constexpr unsigned int OutputSpaceDimension = 3;
  static constexpr unsigned int ParametersDimension = 3;

  /** Parameters Type   */
  using typename Superclass::ScalarType;
  using typename Superclass::ParametersType;
  using typename Superclass::FixedParametersType;
  using typename Superclass::JacobianType;
  using typename Superclass::JacobianPositionType;
  using typename Superclass::InverseJacobianPositionType;
  using typename Superclass::InputPointType;
  using typename Superclass::OutputPointType;
  using typename Superclass::InputVectorType;
  using typename Superclass::OutputVectorType;
  using typename Superclass::InputVnlVectorType;
  using typename Superclass::OutputVnlVectorType;
  using typename Superclass::InputCovariantVectorType;
  using typename Superclass::OutputCovariantVectorType;
  using typename Superclass::MatrixType;
  using typename Superclass::InverseMatrixType;
  using typename Superclass::CenterType;
  using typename Superclass::OffsetType;

  /** VnlQuaternion Type */
  using VnlQuaternionType = vnl_quaternion<TParametersValueType>;

  /** Versor Type */
  using VersorType = Versor<TParametersValueType>;
  using AxisType = typename VersorType::VectorType;
  using AngleType = typename VersorType::ValueType;
  using AxisValueType = typename AxisType::ValueType;
  using ParametersValueType = typename ParametersType::ValueType;

  /**
   * Set the transformation from a container of parameters
   * This is typically used by optimizers.
   *
   * There are 3 parameters. They represent the components
   * of the right part of the versor. This can be seen
   * as the components of the vector parallel to the rotation
   * axis and multiplied by std::sin( angle / 2 ). */
  void
  SetParameters(const ParametersType & parameters) override;

  /** Get the Transformation Parameters. */
  const ParametersType &
  GetParameters() const override;

  /** Set the rotational part of the transform. */
  void
  SetRotation(const VersorType & versor);

  void
  SetRotation(const AxisType & axis, AngleType angle);

  itkGetConstReferenceMacro(Versor, VersorType);

  /** Set the parameters to the IdentityTransform */
  void
  SetIdentity() override;

  /** Compute the Jacobian of the transformation
   *  This method computes the Jacobian matrix of the transformation.
   *  given point or vector, returning the transformed point or
   *  vector. The rank of the Jacobian will also indicate if the
   *  transform is invertible at this point. */
  void
  ComputeJacobianWithRespectToParameters(const InputPointType & p, JacobianType & jacobian) const override;

protected:
  /** Construct an VersorTransform object */
  /** @ITKStartGrouping */
#if !defined(ITK_LEGACY_REMOVE)
  [[deprecated("Removed unused constructor")]] VersorTransform(const MatrixType &       matrix,
                                                               const OutputVectorType & offset);
#endif
  VersorTransform(unsigned int parametersDimension);
  VersorTransform();
  /** @ITKEndGrouping */
  /** Destroy an VersorTransform object */
  ~VersorTransform() override = default;

  void
  SetVarVersor(const VersorType & newVersor)
  {
    m_Versor = newVersor;
  }

  /** Print contents of a VersorTransform */
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** Compute Matrix
   *  Compute the components of the rotation matrix in the superclass */
  void
  ComputeMatrix() override;

  void
  ComputeMatrixParameters() override;

private:
  /** Versor containing the rotation */
  VersorType m_Versor{};
}; // class VersorTransform
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkVersorTransform.hxx"
#endif

#endif /* itkVersorTransform_h */
