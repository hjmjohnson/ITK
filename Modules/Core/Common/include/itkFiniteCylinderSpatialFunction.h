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
#ifndef itkFiniteCylinderSpatialFunction_h
#define itkFiniteCylinderSpatialFunction_h

#include "itkInteriorExteriorSpatialFunction.h"
#include "itkConceptChecking.h"

namespace itk
{
/**
 * \class FiniteCylinderSpatialFunction
 * \brief Function implementation of an finite cylinder
 *
 * Implements a function that returns 1 for points inside or on the surface
 * of a cylinder and 0 for points outside the cylinder.
 *
 * This function only works in 3 Dimensions.
 *
 * \ingroup ITKCommon
 */

template <unsigned int VDimension = 3, typename TInput = Point<double, VDimension>>
class ITK_TEMPLATE_EXPORT FiniteCylinderSpatialFunction : public InteriorExteriorSpatialFunction<VDimension, TInput>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(FiniteCylinderSpatialFunction);

  /** Standard class type aliases. */
  using Self = FiniteCylinderSpatialFunction;
  using Superclass = InteriorExteriorSpatialFunction<VDimension, TInput>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(FiniteCylinderSpatialFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Input type for the function */
  using typename Superclass::InputType;

  /** Output type for the function */
  using typename Superclass::OutputType;

  /** Set/Get and set the center of the cylinder. */
  /** @ITKStartGrouping */
  itkGetConstMacro(Center, InputType);
  itkSetMacro(Center, InputType);
  /** @ITKEndGrouping */
  /** Get and set the medial axis length of the cylinder. */
  /** @ITKStartGrouping */
  itkGetConstMacro(AxisLength, double);
  itkSetMacro(AxisLength, double);
  /** @ITKEndGrouping */
  /** Get and set the radius length of the cylinder. */
  /** @ITKStartGrouping */
  itkGetConstMacro(Radius, double);
  itkSetMacro(Radius, double);
  /** @ITKEndGrouping */
  /** Set the orientation vectors (must be orthogonal) of the ellipsoid axes.
   * Must be normalized!!!!! */
  /** @ITKStartGrouping */
  itkGetConstMacro(Orientation, InputType);
  virtual void
  SetOrientation(const InputType _Orientation);
  /** @ITKEndGrouping */
  /** Evaluates the function at a given position. */
  OutputType
  Evaluate(const InputType & position) const override;

  itkConceptMacro(DimensionShouldBe3, (Concept::SameDimension<VDimension, 3u>));
  itkConceptMacro(PointDimensionShouldBe3, (Concept::SameDimension<InputType::Dimension, 3u>));

protected:
  FiniteCylinderSpatialFunction();
  ~FiniteCylinderSpatialFunction() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  /** The center of the cylinder. */
  InputType m_Center{};

  /** The medial axis length of the cylinder. */
  double m_AxisLength{};

  /** The radius length of the cylinder. */
  double m_Radius{};

  /** The orientation vectors (must be orthogonal) of the ellipsoid axes. */
  InputType m_Orientation{};
  InputType m_NormalizedOrientation{};
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkFiniteCylinderSpatialFunction.hxx"
#endif

#endif
