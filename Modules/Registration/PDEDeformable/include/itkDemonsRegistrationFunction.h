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
#ifndef itkDemonsRegistrationFunction_h
#define itkDemonsRegistrationFunction_h

#include "itkPDEDeformableRegistrationFunction.h"
#include "itkPoint.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkCentralDifferenceImageFunction.h"
#include <mutex>

namespace itk
{
/**
 * \class DemonsRegistrationFunction
 *
 * This class encapsulate the PDE which drives the demons registration
 * algorithm. It is used by DemonsRegistrationFilter to compute the
 * output displacement field which will map a moving image onto a
 * a fixed image.
 *
 * Non-integer moving image values are obtained by using
 * interpolation. The default interpolator is of type
 * LinearInterpolateImageFunction. The user may set other
 * interpolators via method SetMovingImageInterpolator. Note that the input
 * interpolator must derive from baseclass InterpolateImageFunction.
 *
 * This class is templated over the fixed image type, moving image type,
 * and the displacement field type.
 *
 * \warning This filter assumes that the fixed image type, moving image type
 * and displacement field type all have the same number of dimensions.
 *
 * \sa DemonsRegistrationFilter
 * \ingroup FiniteDifferenceFunctions
 * \ingroup ITKPDEDeformableRegistration
 */
template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
class ITK_TEMPLATE_EXPORT DemonsRegistrationFunction
  : public PDEDeformableRegistrationFunction<TFixedImage, TMovingImage, TDisplacementField>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(DemonsRegistrationFunction);

  /** Standard class type aliases. */
  using Self = DemonsRegistrationFunction;
  using Superclass = PDEDeformableRegistrationFunction<TFixedImage, TMovingImage, TDisplacementField>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(DemonsRegistrationFunction);

  /** MovingImage image type. */
  using typename Superclass::MovingImageType;
  using typename Superclass::MovingImagePointer;

  /** FixedImage image type. */
  using typename Superclass::FixedImageType;
  using typename Superclass::FixedImagePointer;
  using IndexType = typename FixedImageType::IndexType;
  using SizeType = typename FixedImageType::SizeType;
  using SpacingType = typename FixedImageType::SpacingType;

  /** Deformation field type. */
  using typename Superclass::DisplacementFieldType;
  using typename Superclass::DisplacementFieldTypePointer;

  /** Inherit some enums from the superclass. */
  static constexpr unsigned int ImageDimension = Superclass::ImageDimension;

  /** Inherit some enums from the superclass. */
  using typename Superclass::PixelType;
  using typename Superclass::RadiusType;
  using typename Superclass::NeighborhoodType;
  using typename Superclass::FloatOffsetType;
  using typename Superclass::TimeStepType;

  /** Interpolator type. */
  using CoordinateType = double;
#ifndef ITK_FUTURE_LEGACY_REMOVE
  using CoordRepType ITK_FUTURE_DEPRECATED(
    "ITK 6 discourages using `CoordRepType`. Please use `CoordinateType` instead!") = CoordinateType;
#endif
  using InterpolatorType = InterpolateImageFunction<MovingImageType, CoordinateType>;
  using InterpolatorPointer = typename InterpolatorType::Pointer;
  using PointType = typename InterpolatorType::PointType;
  using DefaultInterpolatorType = LinearInterpolateImageFunction<MovingImageType, CoordinateType>;

  /** Covariant vector type. */
  using CovariantVectorType = CovariantVector<double, Self::ImageDimension>;

  /** Fixed image gradient calculator type. */
  using GradientCalculatorType = CentralDifferenceImageFunction<FixedImageType>;
  using GradientCalculatorPointer = typename GradientCalculatorType::Pointer;

  /** Moving image gradient calculator type. */
  using MovingImageGradientCalculatorType = CentralDifferenceImageFunction<MovingImageType, CoordinateType>;
  using MovingImageGradientCalculatorPointer = typename MovingImageGradientCalculatorType::Pointer;

  /** Set the moving image interpolator. */
  void
  SetMovingImageInterpolator(InterpolatorType * ptr)
  {
    m_MovingImageInterpolator = ptr;
  }

  /** Get the moving image interpolator. */
  InterpolatorType *
  GetMovingImageInterpolator()
  {
    return m_MovingImageInterpolator;
  }

  /** This class uses a constant timestep of 1. */
  TimeStepType
  ComputeGlobalTimeStep(void * itkNotUsed(GlobalData)) const override
  {
    return m_TimeStep;
  }

  /** Return a pointer to a global data structure that is passed to
   * this object from the solver at each calculation.  */
  void *
  GetGlobalDataPointer() const override
  {
    auto * global = new GlobalDataStruct();

    global->m_SumOfSquaredDifference = 0.0;
    global->m_NumberOfPixelsProcessed = 0L;
    global->m_SumOfSquaredChange = 0;
    return global;
  }

  /** Release memory for global data structure.
   *
   * Updates the metric and release the per-thread-global data.
   */
  void
  ReleaseGlobalDataPointer(void * gd) const override;

  /** Set the object's state before each iteration. */
  void
  InitializeIteration() override;

  /** Compute update at the specified neighbourhood.
   *
   * Called by a finite difference solver image filter a each pixel that does not lie on a data set boundary.
   */
  PixelType
  ComputeUpdate(const NeighborhoodType & it, void * gd, const FloatOffsetType & offset = FloatOffsetType(0.0)) override;

  /** Get the metric value. The metric value is the mean square difference
   * in intensity between the fixed image and transforming moving image
   * computed over the overlapping region between the two images. */
  virtual double
  GetMetric() const
  {
    return m_Metric;
  }

  /** Get the rms change in displacement field. */
  virtual double
  GetRMSChange() const
  {
    return m_RMSChange;
  }

  /** Select if the fixed image or moving image gradient is used for
   * computing the demon forces. The fixed image gradient is used
   * by default. */
  /** @ITKStartGrouping */
  virtual void
  SetUseMovingImageGradient(bool flag)
  {
    m_UseMovingImageGradient = flag;
  }
  virtual bool
  GetUseMovingImageGradient() const
  {
    return m_UseMovingImageGradient;
  }
  /** @ITKEndGrouping */
  /** Set/Get the threshold below which the absolute difference of
   * intensity yields a match. When the intensities match between a
   * moving and fixed image pixel, the update vector (for that
   * iteration) will be the zero vector. Default is 0.001. */
  virtual void
  SetIntensityDifferenceThreshold(double);

  virtual double
  GetIntensityDifferenceThreshold() const;

protected:
  DemonsRegistrationFunction();
  ~DemonsRegistrationFunction() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** FixedImage image neighborhood iterator type. */
  using FixedImageNeighborhoodIteratorType = ConstNeighborhoodIterator<FixedImageType>;

  /** A global data type for this class of equation. Used to store
   * information for computing the metric. */
  struct GlobalDataStruct
  {
    double        m_SumOfSquaredDifference;
    SizeValueType m_NumberOfPixelsProcessed;
    double        m_SumOfSquaredChange;
  };

private:
  /** Cache fixed image information. */
  // SpacingType                  m_FixedImageSpacing;
  // PointType                    m_FixedImageOrigin;
  PixelType m_ZeroUpdateReturn{};
  double    m_Normalizer{};

  /** Function to compute derivatives of the fixed image. */
  GradientCalculatorPointer m_FixedImageGradientCalculator{};

  /** Function to compute derivatives of the moving image. */
  MovingImageGradientCalculatorPointer m_MovingImageGradientCalculator{};
  bool                                 m_UseMovingImageGradient{};

  /** Function to interpolate the moving image. */
  InterpolatorPointer m_MovingImageInterpolator{};

  /** The global timestep. */
  TimeStepType m_TimeStep{};

  /** Threshold below which the denominator term is considered zero. */
  double m_DenominatorThreshold{};

  /** Threshold below which two intensity value are assumed to match. */
  double m_IntensityDifferenceThreshold{};

  /** The metric value is the mean square difference in intensity between
   * the fixed image and transforming moving image computed over the
   * the overlapping region between the two images. */
  mutable double        m_Metric{};
  mutable double        m_SumOfSquaredDifference{};
  mutable SizeValueType m_NumberOfPixelsProcessed{};
  mutable double        m_RMSChange{};
  mutable double        m_SumOfSquaredChange{};

  /** Mutex lock to protect modification to metric. */
  mutable std::mutex m_MetricCalculationMutex{};
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkDemonsRegistrationFunction.hxx"
#endif

#endif
