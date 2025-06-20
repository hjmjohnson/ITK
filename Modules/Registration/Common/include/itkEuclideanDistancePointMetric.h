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
#ifndef itkEuclideanDistancePointMetric_h
#define itkEuclideanDistancePointMetric_h

#include "itkPointSetToPointSetMetric.h"
#include "itkCovariantVector.h"
#include "itkPointSet.h"
#include "itkImage.h"

namespace itk
{
/** \class EuclideanDistancePointMetric
 * \brief Computes the minimum distance between a moving point-set
 *  and a fixed point-set. A vector of minimum closest point distance is
 *  created for each point in the moving point-set.
 *  No correspondence is needed.
 *  For speed consideration, the point-set with the minimum number of points
 *  should be used as the moving point-set.
 *  If the number of points is high, the possibility of setting a distance map
 *  should improve the speed of the closest point computation.
 *
 *  For more details see \cite besl1992.
 *
 * \ingroup RegistrationMetrics
 * \ingroup ITKRegistrationCommon
 */
template <typename TFixedPointSet,
          typename TMovingPointSet,
          typename TDistanceMap = itk::Image<unsigned short, TMovingPointSet::PointDimension>>
class ITK_TEMPLATE_EXPORT EuclideanDistancePointMetric
  : public PointSetToPointSetMetric<TFixedPointSet, TMovingPointSet>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(EuclideanDistancePointMetric);

  /** Standard class type aliases. */
  using Self = EuclideanDistancePointMetric;
  using Superclass = PointSetToPointSetMetric<TFixedPointSet, TMovingPointSet>;

  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(EuclideanDistancePointMetric);

  /** Types transferred from the base class. */
  using typename Superclass::TransformType;
  using typename Superclass::TransformPointer;
  using typename Superclass::TransformParametersType;
  using typename Superclass::TransformJacobianType;

  using typename Superclass::MeasureType;
  using typename Superclass::DerivativeType;
  using typename Superclass::FixedPointSetType;
  using typename Superclass::MovingPointSetType;
  using typename Superclass::FixedPointSetConstPointer;
  using typename Superclass::MovingPointSetConstPointer;

  using typename Superclass::FixedPointIterator;
  using typename Superclass::FixedPointDataIterator;

  using typename Superclass::MovingPointIterator;
  using typename Superclass::MovingPointDataIterator;

  using DistanceMapType = TDistanceMap;
  using DistanceMapPointer = typename DistanceMapType::ConstPointer;

  /** Get the number of values, i.e. the number of points in the moving set. */
  [[nodiscard]] unsigned int
  GetNumberOfValues() const override;

  /** Get the derivatives of the match measure. */
  void
  GetDerivative(const TransformParametersType & itkNotUsed(parameters),
                DerivativeType &                itkNotUsed(derivative)) const override
  {}

  /**  Get the match measure, i.e. the value for single valued optimizers. */
  MeasureType
  GetValue(const TransformParametersType & parameters) const override;

  /**  Get value and derivatives for multiple valued optimizers. */
  void
  GetValueAndDerivative(const TransformParametersType & parameters,
                        MeasureType &                   value,
                        DerivativeType &                derivative) const;

  /** Set/Get the distance map. */
  /** @ITKStartGrouping */
  itkSetConstObjectMacro(DistanceMap, DistanceMapType);
  itkGetConstObjectMacro(DistanceMap, DistanceMapType);
  /** @ITKEndGrouping */
  /** Set/Get if the distance should be squared.
   *  When set to true, the filter's computational speed is substantially improved
   *  (by avoiding numerous sqrt() calls), but it will result in minimizing the sum
   *  of distances^4 instead of the sum of distances^2. Default is false. */
  /** @ITKStartGrouping */
  itkSetMacro(ComputeSquaredDistance, bool);
  itkGetConstMacro(ComputeSquaredDistance, bool);
  itkBooleanMacro(ComputeSquaredDistance);
  /** @ITKEndGrouping */
protected:
  EuclideanDistancePointMetric();
  ~EuclideanDistancePointMetric() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  DistanceMapPointer m_DistanceMap{};
  bool               m_ComputeSquaredDistance{ false };
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkEuclideanDistancePointMetric.hxx"
#endif

#endif
