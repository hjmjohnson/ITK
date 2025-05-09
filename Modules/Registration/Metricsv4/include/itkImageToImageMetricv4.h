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
#ifndef itkImageToImageMetricv4_h
#define itkImageToImageMetricv4_h

#include "itkCovariantVector.h"
#include "itkImageFunction.h"
#include "itkObjectToObjectMetric.h"
#include "itkInterpolateImageFunction.h"
#include "itkSpatialObject.h"
#include "itkResampleImageFilter.h"
#include "itkThreadedIndexedContainerPartitioner.h"
#include "itkThreadedImageRegionPartitioner.h"
#include "itkImageToImageFilter.h"
#include "itkImageToImageMetricv4GetValueAndDerivativeThreader.h"
#include "itkPointSet.h"
#include "itkDefaultConvertPixelTraits.h"
#include "itkDefaultImageToImageMetricTraitsv4.h"

namespace itk
{
/** \class ImageToImageMetricv4
 *
 * Computes similarity between regions of two images, using two
 * user-supplied transforms, a 'fixed' transform and a 'moving' transform.
 *
 * \warning Integer-type images are not yet supported. See concept-checking
 * in DefaultImageToImageMetricTraitsv4.
 *
 * Templated over the fixed and moving image types, as well as an optional
 * VirtualImage type to define the virtual domain. The VirtualImage type
 * defaults to TFixedImage.
 * \note If TFixedImage is type VectorImage, then TVirtualImage must be set
 * separately to a non-VectorImage type, e.g. Image<unsigned char, dimension>.
 *
 * If the user does not set the virtual domain explicitly,
 * then it is created during the call to \c Initialize from
 * the fixed image by copying its information.
 * See ObjectToObjectMetric for more discussion on the virtual domain.
 *
 * At a minimum, the user must:
 *  1) Set images using SetFixedImage and SetMovingImage.
 *  2) Call Initialize.
 *
 * Image gradient calculations
 *
 * Image gradients can be calculated in one of two ways:
 * 1) Using a gradient image filter, by setting
 *  \c Use[Fixed|Moving]ImageGradientFilter to true. By default this is set
 *  as an itkGradientRecursiveGaussianImageFilter, a
 *  smoothed gradient filter. A filter uses more memory, because it
 *  calculates all gradients at once and stores them in an image. The advantage
 *  of pre-calculation is for the fixed image gradients, since they only need be
 *  calculated once, and for metrics that need to access image gradients more
 *  than once for a particular point. The fixed image gradients are only
 *  calculated once when this option is set, during \c Initialize.
 * 2) Otherwise, an image gradient calculator based on ImageFunction is used.
 *  By default the CentralDifferenceImageFunction is used. This calculation
 *  is not smoothed and gives different results than
 *  GradientRecursiveGaussianImageFilter. The advantage is that less memory is
 *  used. However for the fixed image, it means needlessly computing the image
 *  gradients at each iteration of a registration instead of just computing
 *  once at the beginning. The user can supply a different function by calling
 *  SetFixedImageGradientCalculator and/or SetMovingImageGradientCalculator.
 *
 * Both image gradient calculation methods are threaded.
 * Generally it is not recommended to use different image gradient methods for
 * the fixed and moving images because the methods return different results.
 *
 * Image Masks
 *
 * Image masks are supported using SetMovingImageMask or SetFixedImageMask.
 * If the image mask is sparse, see the comments for use of sparse point sets.
 *
 * Sparse Sampling
 *
 * Sparse sampling is performed by supplying an arbitrary point list over
 * which to evaluate the
 * metric. It's presumed that the user will be working in terms of the fixed
 * image domain, and thus the point list is expected to be in the fixed domain.
 * Internally, the points are transformed into the virtual domain as needed.
 * \note The attributes/data of each point in the set are not used, but rather
 * the point's geometric coordinates.
 * Point sets are enabled by calling UseSampledPointSet, then the
 * SetFixedSampledPointSet is called or SetVirtualSampledPointSet
 * along with SetUseVirtualSampledPointSet.
 * \note If the point set is sparse, the option SetUse[Fixed|Moving]ImageGradientFilter
 * typically should be disabled to avoid excessive computation. However,
 * the gradient values of the fixed image are not cached
 * when using a point set (there are plans for this in the future), so
 * depending on the number of iterations (when used during optimization)
 * and the level of sparsity, it may be more efficient to
 * use a gradient image filter for it because it will only be
 * calculated once.
 *
 * Vector Images
 *
 * To support vector images, the class must be declared using the
 * VectorImageToImageMetricTraitsv4 class in the template declaration,
 * as described above.
 * Derived classes must provide special handling for vector pixel
 * types. MeanSquaresImageToImageMetricv4 can be used as an example.
 *
 * Threading
 *
 * This class is threaded. Threading is handled by friend classes
 * ImageToImageMetricv4GetValueAndDerivativeThreaderBase and
 * ImageToImageMetricv4GetValueAndDerivativeThreader. Dense and sparse
 * evaluation are handled by template specialization of the
 * ImageToImageMetricv4GetValueAndDerivativeThreader::ThreadedExecution
 * method, in order to iterate over either all points in the virtual space in
 * the case of dense evaluation, or a list of points in the sparse case.
 *
 * Methods and members of ImageToImageMetricv4 are accessed by
 * the threading class using its m_Associate member, which points
 * to the containing instance of ImageToImageMetricv4.
 *
 * Pre- and post-processing for threaded operation is handled in
 *  ImageToImageMetricv4GetValueAndDerivativeThreaderBase::BeforeThreadedExecution, and
 * ImageToImageMetricv4GetValueAndDerivativeThreaderBase::AfterThreadedExecution,
 * respectively.
 *
 * Derived classes:
 *
 *  The GetValue method may be overridden to provide better-optimized or
 *  otherwise different behavior as needed. Otherwise, the m_ComputeDerivative
 *  member should be checked to avoid computing derivatives when the caller
 *  has called GetValue(). See GetComputeDerivative() in this class and in
 *  this metric's threader class.
 *
 *  Derived classes must derive a threader class from
 *  ImageToImageMetricv4GetValueAndDerivativeThreader, from which
 *  a DenseGetValueAndDerivativeThreader and SparseGetValueAndDerivativeThreader
 *  must be defined. Then,
    \code
      this->m_DenseGetValueAndDerivativeThreader   = DenseDerivedClassGetValueAndDerivativeThreader::New();
      this->m_SparseGetValueAndDerivativeThreader  = SparseDerivedClassGetValueAndDerivativeThreader::New();
    \endcode
 *  must be called in the constructor.
 *
 *  The ProcessPoint method of the derived threader must be overridden to
 *  provide the metric-specific evaluation.
 *
 *  To access methods and members within the derived metric class from the
 *  derived threader class, the user must cast m_Associate to the type of the
 *  derived metric class.
 *
 *  See \c ImageToImageMetricv4Test for a clear example of what a
 *  derived class must implement and do.
 *
 * \ingroup ITKMetricsv4
 */
template <typename TFixedImage,
          typename TMovingImage,
          typename TVirtualImage = TFixedImage,
          typename TInternalComputationValueType = double,
          typename TMetricTraits =
            DefaultImageToImageMetricTraitsv4<TFixedImage, TMovingImage, TVirtualImage, TInternalComputationValueType>>
class ITK_TEMPLATE_EXPORT ImageToImageMetricv4
  : public ObjectToObjectMetric<TFixedImage::ImageDimension,
                                TMovingImage::ImageDimension,
                                TVirtualImage,
                                TInternalComputationValueType>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ImageToImageMetricv4);

  /** Standard class type aliases. */
  using Self = ImageToImageMetricv4;
  using Superclass = ObjectToObjectMetric<TFixedImage::ImageDimension,
                                          TMovingImage::ImageDimension,
                                          TVirtualImage,
                                          TInternalComputationValueType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ImageToImageMetricv4);

  /** Type used internally for computations */

  /** It should be possible to derive the internal computation type from the class object. */
  using InternalComputationValueType = TInternalComputationValueType;

  /** Type used for representing parameter values  */
  using typename Superclass::CoordinateRepresentationType;

  /**  Type of the parameters. */
  using typename Superclass::ParametersType;
  using typename Superclass::ParametersValueType;

  /** Gradient source type */
  using typename Superclass::GradientSourceEnum;

  /** Dimension type */
  using typename Superclass::DimensionType;
  using ImageDimensionType = typename Superclass::DimensionType;

  /** Transform types from Superclass*/
  using typename Superclass::FixedTransformType;
  using typename Superclass::FixedTransformPointer;
  using typename Superclass::FixedInputPointType;
  using typename Superclass::FixedOutputPointType;
  using typename Superclass::FixedTransformParametersType;

  using typename Superclass::MovingTransformType;
  using typename Superclass::MovingTransformPointer;
  using typename Superclass::MovingInputPointType;
  using typename Superclass::MovingOutputPointType;
  using typename Superclass::MovingTransformParametersType;

  using typename Superclass::JacobianType;
  using typename Superclass::FixedTransformJacobianType;
  using typename Superclass::MovingTransformJacobianType;

  using ObjectType = typename Superclass::ObjectType;

  /** Image-accessor type alias */
  using FixedImageType = TFixedImage;
  using FixedImagePixelType = typename FixedImageType::PixelType;
  using FixedPixelType = FixedImagePixelType;
  using FixedImagePointer = typename FixedImageType::Pointer;
  using FixedImageConstPointer = typename FixedImageType::ConstPointer;
  using FixedImagePointType = typename FixedImageType::PointType;
  using FixedImageIndexType = typename FixedImageType::IndexType;
  using MovingImageType = TMovingImage;
  using MovingImagePixelType = typename MovingImageType::PixelType;
  using MovingPixelType = MovingImagePixelType;
  using MovingImagePointer = typename MovingImageType::Pointer;
  using MovingImageConstPointer = typename MovingImageType::ConstPointer;
  using MovingImagePointType = typename MovingImageType::PointType;
  using MovingImageRegionType = typename MovingImageType::RegionType;
  using MovingImageIndexType = typename MovingImageType::IndexType;

  /** Types for the virtual domain */
  using VirtualImageType = typename Superclass::VirtualImageType;
  using typename Superclass::VirtualImagePointer;
  using typename Superclass::VirtualPixelType;
  using typename Superclass::VirtualRegionType;
  using typename Superclass::VirtualSizeType;
  using typename Superclass::VirtualSpacingType;
  using VirtualOriginType = typename Superclass::VirtualPointType;
  using typename Superclass::VirtualPointType;
  using typename Superclass::VirtualDirectionType;
  using VirtualRadiusType = typename Superclass::VirtualSizeType;
  using typename Superclass::VirtualIndexType;
  using typename Superclass::VirtualPointSetType;
  using typename Superclass::VirtualPointSetPointer;

  /** Typedef for traits class */
  using MetricTraits = TMetricTraits;

  /* Image dimension accessors */
  static constexpr DimensionType FixedImageDimension = Superclass::FixedDimension;
  static constexpr DimensionType MovingImageDimension = Superclass::MovingDimension;
  static constexpr DimensionType VirtualImageDimension = Superclass::VirtualDimension;

  /**  Type for the mask of the fixed image. Only pixels that are "inside"
       this mask will be considered for the computation of the metric */
  using FixedImageMaskType = SpatialObject<Self::FixedImageDimension>;
  using FixedImageMaskPointer = typename FixedImageMaskType::Pointer;
  using FixedImageMaskConstPointer = typename FixedImageMaskType::ConstPointer;

  /**  Type for the mask of the moving image. Only pixels that are "inside"
       this mask will be considered for the computation of the metric */
  using MovingImageMaskType = SpatialObject<Self::MovingImageDimension>;
  using MovingImageMaskPointer = typename MovingImageMaskType::Pointer;
  using MovingImageMaskConstPointer = typename MovingImageMaskType::ConstPointer;

  /** Type of the point set used for sparse sampling. */
  using FixedSampledPointSetType = PointSet<typename FixedImageType::PixelType, Self::FixedImageDimension>;
  using FixedSampledPointSetPointer = typename FixedSampledPointSetType::Pointer;
  using FixedSampledPointSetConstPointer = typename FixedSampledPointSetType::ConstPointer;

  /**  Type of the Interpolator Base class */
  using FixedInterpolatorType = InterpolateImageFunction<FixedImageType, CoordinateRepresentationType>;
  using MovingInterpolatorType = InterpolateImageFunction<MovingImageType, CoordinateRepresentationType>;
  using FixedInterpolatorPointer = typename FixedInterpolatorType::Pointer;
  using MovingInterpolatorPointer = typename MovingInterpolatorType::Pointer;

  /** Image derivatives types */
  using FixedImageGradientType = typename MetricTraits::FixedImageGradientType;
  using MovingImageGradientType = typename MetricTraits::MovingImageGradientType;
  using VirtualImageGradientType = typename MetricTraits::VirtualImageGradientType;

  using FixedImageComponentGradientType =
    CovariantVector<typename FixedImageGradientType::ValueType, FixedImageDimension>;

  using MovingImageComponentGradientType =
    CovariantVector<typename MovingImageGradientType::ValueType, MovingImageDimension>;

  using VirtualImageComponentGradientType =
    CovariantVector<typename VirtualImageGradientType::ValueType, VirtualImageDimension>;

  /** Type of the filter used to calculate the gradients.
   * Note that RealType is always double (or long double for
   * long double pixel-type).*/
  using FixedRealType = typename MetricTraits::FixedRealType;
  using MovingRealType = typename MetricTraits::MovingRealType;

  using FixedScalarRealType = typename NumericTraits<FixedRealType>::ScalarRealType;
  using MovingScalarRealType = typename NumericTraits<MovingRealType>::ScalarRealType;

  using FixedGradientPixelType = typename MetricTraits::FixedGradientPixelType;
  using MovingGradientPixelType = typename MetricTraits::MovingGradientPixelType;

  using FixedImageGradientImageType = typename MetricTraits::FixedImageGradientImageType;
  using MovingImageGradientImageType = typename MetricTraits::MovingImageGradientImageType;

  using FixedImageGradientImagePointer = typename FixedImageGradientImageType::Pointer;
  using MovingImageGradientImagePointer = typename MovingImageGradientImageType::Pointer;

  using FixedImageGradientFilterType = typename MetricTraits::FixedImageGradientFilterType;
  using MovingImageGradientFilterType = typename MetricTraits::MovingImageGradientFilterType;

  using FixedImageGradientFilterPointer = typename FixedImageGradientFilterType::Pointer;
  using MovingImageGradientFilterPointer = typename MovingImageGradientFilterType::Pointer;


  /** Default image gradient filter types */
  using DefaultFixedImageGradientFilter = typename MetricTraits::DefaultFixedImageGradientFilter;
  using DefaultMovingImageGradientFilter = typename MetricTraits::DefaultMovingImageGradientFilter;

  /** Image gradient calculator types. The TOutput template parameter
   * is chosen to match that of CentralDifferenceImageFunction. */
  using FixedImageGradientCalculatorType = typename MetricTraits::FixedImageGradientCalculatorType;
  using MovingImageGradientCalculatorType = typename MetricTraits::MovingImageGradientCalculatorType;

  using FixedImageGradientCalculatorPointer = typename FixedImageGradientCalculatorType::Pointer;
  using MovingImageGradientCalculatorPointer = typename MovingImageGradientCalculatorType::Pointer;

  /** Default image gradient calculator types */
  using DefaultFixedImageGradientCalculator = typename MetricTraits::DefaultFixedImageGradientCalculator;
  using DefaultMovingImageGradientCalculator = typename MetricTraits::DefaultMovingImageGradientCalculator;

  /**  Type of the measure. */
  using typename Superclass::MeasureType;

  /**  Type of the metric derivative. */
  using typename Superclass::DerivativeType;
  using DerivativeValueType = typename DerivativeType::ValueType;

  /** Type to represent the number of parameters that are being optimized at
   * any given iteration of the optimizer. */
  using typename Superclass::NumberOfParametersType;

  /** Set fixed image*/
  void
  SetFixedObject(const ObjectType * object) override
  {
    auto * image = dynamic_cast<FixedImageType *>(const_cast<ObjectType *>(object));
    if (image != nullptr)
    {
      this->SetFixedImage(image);
    }
    else
    {
      itkExceptionMacro("Incorrect object type.  Should be an image.");
    }
  }

  /** Set moving image*/
  void
  SetMovingObject(const ObjectType * object) override
  {
    auto * image = dynamic_cast<MovingImageType *>(const_cast<ObjectType *>(object));
    if (image != nullptr)
    {
      this->SetMovingImage(image);
    }
    else
    {
      itkExceptionMacro("Incorrect object type.  Should be an image.");
    }
  }

  /* Get/Set the Fixed Image.  */
  /** @ITKStartGrouping */
  itkSetConstObjectMacro(FixedImage, FixedImageType);
  itkGetConstObjectMacro(FixedImage, FixedImageType);
  /** @ITKEndGrouping */

  /** Get/Set the Moving Image.  */
  /** @ITKStartGrouping */
  itkSetConstObjectMacro(MovingImage, MovingImageType);
  itkGetConstObjectMacro(MovingImage, MovingImageType);
  /** @ITKEndGrouping */

  /** Connect the fixed interpolator. */
  itkSetObjectMacro(FixedInterpolator, FixedInterpolatorType);

  /** Get a pointer to the fixed interpolator.  */
  itkGetModifiableObjectMacro(FixedInterpolator, FixedInterpolatorType);

  /** Connect the Moving interpolator. */
  itkSetObjectMacro(MovingInterpolator, MovingInterpolatorType);

  /** Get a pointer to the Moving interpolator.  */
  itkGetModifiableObjectMacro(MovingInterpolator, MovingInterpolatorType);

  /** Set/Get the moving image mask. */
  /** @ITKStartGrouping */
#ifndef ITK_FUTURE_LEGACY_REMOVE
  virtual void
  SetMovingImageMask(MovingImageMaskType * const arg)
  {
    const auto * const constArg = arg;
    // Call the overload defined by itkSetConstObjectMacro, or an override.
    this->SetMovingImageMask(constArg);
  }
#endif
  itkSetConstObjectMacro(MovingImageMask, MovingImageMaskType);
  itkGetConstObjectMacro(MovingImageMask, MovingImageMaskType);
  /** @ITKEndGrouping */
  /** Set/Get the fixed image mask. */
  /** @ITKStartGrouping */
#ifndef ITK_FUTURE_LEGACY_REMOVE
  virtual void
  SetFixedImageMask(FixedImageMaskType * const arg)
  {
    const auto * const constArg = arg;
    // Call the overload defined by itkSetConstObjectMacro, or an override.
    this->SetFixedImageMask(constArg);
  }
#endif
  itkSetConstObjectMacro(FixedImageMask, FixedImageMaskType);
  itkGetConstObjectMacro(FixedImageMask, FixedImageMaskType);
  /** @ITKEndGrouping */
  /** Set/Get the fixed image domain sampling point set
   * See main documentation regarding using fixed vs virtual domain
   * for the point set. */
  /** @ITKStartGrouping */
#ifndef ITK_FUTURE_LEGACY_REMOVE
  virtual void
  SetFixedSampledPointSet(FixedSampledPointSetType * const arg)
  {
    const auto * const constArg = arg;
    // Call the overload defined by itkSetConstObjectMacro, or an override.
    this->SetFixedSampledPointSet(constArg);
  }
#endif
  itkSetConstObjectMacro(FixedSampledPointSet, FixedSampledPointSetType);
  itkGetConstObjectMacro(FixedSampledPointSet, FixedSampledPointSetType);
  /** @ITKEndGrouping */
  /** Set/Get the virtual image domain sampling point set */
  /** @ITKStartGrouping */
  itkSetObjectMacro(VirtualSampledPointSet, VirtualPointSetType);
  itkGetConstObjectMacro(VirtualSampledPointSet, VirtualPointSetType);
  /** @ITKEndGrouping */
  /** Set/Get flag to use a domain sampling point set */
  /** @ITKStartGrouping */
  itkSetMacro(UseSampledPointSet, bool);
  itkGetConstReferenceMacro(UseSampledPointSet, bool);
  itkBooleanMacro(UseSampledPointSet);
  /** @ITKEndGrouping */
  /** Set/Get flag to indicate of the VirtualSampledPointSet is set
   * over the FixedSampledPointSet*/
  /** @ITKStartGrouping */
  itkSetMacro(UseVirtualSampledPointSet, bool);
  itkGetConstReferenceMacro(UseVirtualSampledPointSet, bool);
  itkBooleanMacro(UseVirtualSampledPointSet);
  /** @ITKEndGrouping */
#if !defined(ITK_LEGACY_REMOVE)
  /** UseFixedSampledPointSet is deprecated and has been replaced
   * with UseSampledPointsSet. */
  /** @ITKStartGrouping */
  itkLegacyMacro(virtual void SetUseFixedSampledPointSet(bool v))
  {
    this->SetUseSampledPointSet(v);
  }
  itkLegacyMacro(virtual bool GetUseFixedSampledPointSet() const)
  {
    return this->GetUseSampledPointSet();
  }
  itkLegacyMacro(virtual void UseFixedSampledPointSetOn())
  {
    return this->UseSampledPointSetOn();
  }
  itkLegacyMacro(virtual void UseFixedSampledPointSetOff())
  {
    return this->UseSampledPointSetOff();
  }
  /** @ITKEndGrouping */
#endif

  /** Set/Get the gradient filter */
  /** @ITKStartGrouping */
  itkSetObjectMacro(FixedImageGradientFilter, FixedImageGradientFilterType);
  itkGetModifiableObjectMacro(FixedImageGradientFilter, FixedImageGradientFilterType);
  itkSetObjectMacro(MovingImageGradientFilter, MovingImageGradientFilterType);
  itkGetModifiableObjectMacro(MovingImageGradientFilter, MovingImageGradientFilterType);
  /** @ITKEndGrouping */
  /** Set/Get gradient calculators */
  /** @ITKStartGrouping */
  itkSetObjectMacro(FixedImageGradientCalculator, FixedImageGradientCalculatorType);
  itkGetModifiableObjectMacro(FixedImageGradientCalculator, FixedImageGradientCalculatorType);
  itkSetObjectMacro(MovingImageGradientCalculator, MovingImageGradientCalculatorType);
  itkGetModifiableObjectMacro(MovingImageGradientCalculator, MovingImageGradientCalculatorType);
  /** @ITKEndGrouping */
  /** Set/Get gradient computation via an image filter,
   * for fixed image. */
  /** @ITKStartGrouping */
  itkSetMacro(UseFixedImageGradientFilter, bool);
  itkGetConstReferenceMacro(UseFixedImageGradientFilter, bool);
  itkBooleanMacro(UseFixedImageGradientFilter);
  /** @ITKEndGrouping */
  /** Set/Get gradient computation via an image filter. */
  /** @ITKStartGrouping */
  itkSetMacro(UseMovingImageGradientFilter, bool);
  itkGetConstReferenceMacro(UseMovingImageGradientFilter, bool);
  itkBooleanMacro(UseMovingImageGradientFilter);
  /** @ITKEndGrouping */
  /** Get number of work units to used in the most recent
   * evaluation.  Only valid after GetValueAndDerivative() or
   * GetValue() has been called. */
  virtual ThreadIdType
  GetNumberOfWorkUnitsUsed() const;

  /** Set number of work units to use. This the maximum number of work units to use
   * when multithreaded.  The actual number of work units used (may be less than
   * this value) can be obtained with \c GetNumberOfWorkUnitsUsed. */
  /** @ITKStartGrouping */
  virtual void
  SetMaximumNumberOfWorkUnits(const ThreadIdType number);
  virtual ThreadIdType
  GetMaximumNumberOfWorkUnits() const;
  /** @ITKEndGrouping */
#if !defined(ITK_LEGACY_REMOVE)
  /** Get number of threads to used in the most recent
   * evaluation.  Only valid after GetValueAndDerivative() or
   * GetValue() has been called.
   *
   * NOTE: deprecated. Use GetNumberOfWorkUnitsUsed() */
  itkLegacyMacro(virtual ThreadIdType GetNumberOfThreadsUsed() const)
  {
    return this->GetNumberOfWorkUnitsUsed();
  }

  /** Set number of threads to use. This the maximum number of threads to use
   * when multithreaded.  The actual number of threads used (may be less than
   * this value) can be obtained with \c GetNumberOfWorkUnitsUsed.
   *
   * NOTE: deprecated. Use SetMaximumNumberOfWorkUnits() and
   * GetMaximumNumberOfWorkUnits() */
  /** @ITKStartGrouping */
  itkLegacyMacro(virtual void SetMaximumNumberOfThreads(const ThreadIdType count))
  {
    this->SetMaximumNumberOfWorkUnits(count);
  }
  itkLegacyMacro(virtual ThreadIdType GetMaximumNumberOfThreads() const)
  {
    return this->GetMaximumNumberOfWorkUnits();
  }
  /** @ITKEndGrouping */
#endif // !ITK_LEGACY_REMOVE

  /**
   * Finalize the per-thread components for computing
   * metric.  Some threads can accumulate their data
   * as the thread finishes rather than waiting
   * for all threads to finish before the accumulation
   * occurs.
   */
  virtual void
  FinalizeThread(const ThreadIdType /*threadId*/)
  { /*Do nothing by default */
  }

  /** Get Fixed Gradient Image. */
  itkGetModifiableObjectMacro(FixedImageGradientImage, FixedImageGradientImageType);

  /** Get Moving Gradient Image. */
  itkGetModifiableObjectMacro(MovingImageGradientImage, MovingImageGradientImageType);

  /** Get the number of points in the domain used to evaluate
   * the metric. This will differ depending on whether a sampled
   * point set or dense sampling is used, and will be greater than
   * or equal to GetNumberOfValidPoints(). */
  SizeValueType
  GetNumberOfDomainPoints() const;

  /** Set/Get the option for applying floating point resolution truncation
   * to derivative calculations in global support cases. False by default. It is only
   * applied in global support cases (i.e. with global-support transforms) because
   * in these cases, the per-point derivative values are added cumulatively,
   * which can lead to loss of precision when the sum becomes much larger than
   * the values being added.
   * The goal is more consistent results across the number of threads used for an evaluation.
   * The resolution can be changed using SetFloatingPointCorrectionResolution().
   * \note The metric always sums derivative values using a CompensatedSummation object,
   * but empirically this provides only a slight improvement in precision across number
   * of threads during registration.
   * \warning The metric does not perform any normalization so the results
   * of this truncation are highly dependent on the derivative magnitudes. */
  /** @ITKStartGrouping */
  itkSetMacro(UseFloatingPointCorrection, bool);
  itkGetConstReferenceMacro(UseFloatingPointCorrection, bool);
  itkBooleanMacro(UseFloatingPointCorrection);
  /** @ITKEndGrouping */
  /** Set/Get the floating point resolution used optionally by the derivatives.
   * If this is set, for example to 1e5, then the derivative will have precision up to 5
   * points beyond the decimal point. And precision beyond that will be
   * truncated. */
  /** @ITKStartGrouping */
  itkSetMacro(FloatingPointCorrectionResolution, DerivativeValueType);
  itkGetConstMacro(FloatingPointCorrectionResolution, DerivativeValueType);
  /** @ITKEndGrouping */
  /* Initialize the metric before calling GetValue or GetDerivative.
   * Derived classes must call this Superclass version if they override
   * this to perform their own initialization.
   * \note This is meant to be called once for a particular metric setup.
   * That is, when used in registration, this method would be called once
   * before entering the registration loop, during which GetValue or
   * GetDerivative will be called repeatedly. It must be called again if
   * metric settings are changed before beginning a new registration. */
  void
  Initialize() override;

  MeasureType
  GetValue() const override;

  void
  GetDerivative(DerivativeType &) const override;

  /** Calculate and return both the value for the metric and its derivative.
   * This calls the SparseGetValueAndDerivativeThreader if \c UsedFixedSampledPointSet
   * is true, and DenseGetValueAndDerivativeThreader otherwise.  The threaders
   * in turn call \c ProcessPoint on each point in the
   * domain to be examined. */
  void
  GetValueAndDerivative(MeasureType & value, DerivativeType & derivative) const override;

  /** Get the number of sampled fixed sampled points that are
   * deemed invalid during conversion to virtual domain in Initialize().
   * For informational purposes. */
  itkGetConstReferenceMacro(NumberOfSkippedFixedSampledPoints, SizeValueType);

  bool
  SupportsArbitraryVirtualDomainSamples() const override
  {
    return true;
  }

  using typename Superclass::MetricCategoryType;

  /** Get metric category */
  MetricCategoryType
  GetMetricCategory() const override
  {
    return MetricCategoryType::IMAGE_METRIC;
  }

protected:
  /* Interpolators for image gradient filters. */
  using FixedImageGradientInterpolatorType =
    LinearInterpolateImageFunction<FixedImageGradientImageType, CoordinateRepresentationType>;
  using MovingImageGradientInterpolatorType =
    LinearInterpolateImageFunction<MovingImageGradientImageType, CoordinateRepresentationType>;

  friend class ImageToImageMetricv4GetValueAndDerivativeThreaderBase<
    ThreadedImageRegionPartitioner<VirtualImageDimension>,
    Self>;
  friend class ImageToImageMetricv4GetValueAndDerivativeThreaderBase<ThreadedIndexedContainerPartitioner, Self>;
  friend class ImageToImageMetricv4GetValueAndDerivativeThreader<ThreadedImageRegionPartitioner<VirtualImageDimension>,
                                                                 Self>;
  friend class ImageToImageMetricv4GetValueAndDerivativeThreader<ThreadedIndexedContainerPartitioner, Self>;

  /* A DenseGetValueAndDerivativeThreader
   * Derived classes must define this class and assign it in their constructor
   * if threaded processing in GetValueAndDerivative is performed. */
  typename ImageToImageMetricv4GetValueAndDerivativeThreader<ThreadedImageRegionPartitioner<VirtualImageDimension>,
                                                             Self>::Pointer m_DenseGetValueAndDerivativeThreader;
  /* A SparseGetValueAndDerivativeThreader
   * Derived classes must define this class and assign it in their constructor
   * if threaded processing in GetValueAndDerivative is performed. */
  typename ImageToImageMetricv4GetValueAndDerivativeThreader<ThreadedIndexedContainerPartitioner, Self>::Pointer
    m_SparseGetValueAndDerivativeThreader;

  /** Perform any initialization required before each evaluation of
   * \c GetValueAndDerivative. This is distinct from Initialize, which
   * is called only once before a number of iterations, e.g. before
   * a registration loop. */
  virtual void
  InitializeForIteration() const;

  /**
   * Transform a point from VirtualImage domain to FixedImage domain and evaluate.
   * This function also checks if mapped point is within the mask if
   * one is set, and that is within the fixed image buffer, in which
   * case the return value will be true.
   * Parameters \c mappedFixedPoint and \c mappedFixedPixelValue are  returned.
   */
  bool
  TransformAndEvaluateFixedPoint(const VirtualPointType & virtualPoint,
                                 FixedImagePointType &    mappedFixedPoint,
                                 FixedImagePixelType &    mappedFixedPixelValue) const;

  /** Transform and evaluate a point from VirtualImage domain to MovingImage domain. */
  bool
  TransformAndEvaluateMovingPoint(const VirtualPointType & virtualPoint,
                                  MovingImagePointType &   mappedMovingPoint,
                                  MovingImagePixelType &   mappedMovingPixelValue) const;

  /** Compute image derivatives for a Fixed point. */
  virtual void
  ComputeFixedImageGradientAtPoint(const FixedImagePointType & mappedPoint, FixedImageGradientType & gradient) const;

  /** Compute image derivatives for a moving point. */
  virtual void
  ComputeMovingImageGradientAtPoint(const MovingImagePointType & mappedPoint, MovingImageGradientType & gradient) const;

  /** Computes the gradients of the fixed image, using the
   * GradientFilter, assigning the output to
   * to m_FixedImageGradientImage. */
  virtual void
  ComputeFixedImageGradientFilterImage();

  /** Computes the gradients of the moving image, using the
   * GradientFilter, assigning the output to
   * to m_MovingImageGradientImage. */
  virtual void
  ComputeMovingImageGradientFilterImage() const;

  /** Perform the actual threaded processing, using the appropriate
   * GetValueAndDerivativeThreader. Results get written to
   * member vars. This is available as a separate method so it
   * can be used by derived classes that implement their own
   * GetValueAndDerivative, and/or need to run the processing loop
   * more than once.*/
  virtual void
  GetValueAndDerivativeExecute() const;

  /** Initialize the default image gradient filters. This must only
   * be called once the fixed and moving images have been set. */
  /** @ITKStartGrouping */
  virtual void
  InitializeDefaultFixedImageGradientFilter();
  virtual void
  InitializeDefaultMovingImageGradientFilter();
  /** @ITKEndGrouping */
  /** Get accessor for flag to calculate derivative. */
  itkGetConstMacro(ComputeDerivative, bool);

  FixedImageConstPointer  m_FixedImage{};
  MovingImageConstPointer m_MovingImage{};

  /** Pointers to interpolators */
  FixedInterpolatorPointer                              m_FixedInterpolator{};
  MovingInterpolatorPointer                             m_MovingInterpolator{};
  typename FixedImageGradientInterpolatorType::Pointer  m_FixedImageGradientInterpolator{};
  typename MovingImageGradientInterpolatorType::Pointer m_MovingImageGradientInterpolator{};

  /** Flag to control use of precomputed gradient filter image or gradient
   * calculator for image gradient calculations. */
  bool m_UseFixedImageGradientFilter{};
  bool m_UseMovingImageGradientFilter{};

  /** Gradient filters */
  FixedImageGradientFilterPointer  m_FixedImageGradientFilter{};
  MovingImageGradientFilterPointer m_MovingImageGradientFilter{};

  /** Pointer to default gradient filter. Used for easier
   * initialization of the default filter. */
  typename DefaultFixedImageGradientFilter::Pointer  m_DefaultFixedImageGradientFilter{};
  typename DefaultMovingImageGradientFilter::Pointer m_DefaultMovingImageGradientFilter{};

  /** Pointer to default gradient calculators. Used for easier
   * initialization of the default filter. */
  typename DefaultFixedImageGradientCalculator::Pointer  m_DefaultFixedImageGradientCalculator{};
  typename DefaultMovingImageGradientCalculator::Pointer m_DefaultMovingImageGradientCalculator{};

  /** Gradient images to store gradient filter output. */
  mutable FixedImageGradientImagePointer  m_FixedImageGradientImage{};
  mutable MovingImageGradientImagePointer m_MovingImageGradientImage{};

  /** Image gradient calculators */
  FixedImageGradientCalculatorPointer  m_FixedImageGradientCalculator{};
  MovingImageGradientCalculatorPointer m_MovingImageGradientCalculator{};

  /** Derivative results holder. Uses a raw pointer so we can point it
   * to a user-provided object. This is used in internal methods so
   * the user-provided variable does not have to be passed around. It also enables
   * safely sharing a derivative object between metrics during multi-variate
   * analysis, for memory efficiency.
   * Will be nullptr if not set. */
  mutable DerivativeType * m_DerivativeResult{};

  /** Masks */
  FixedImageMaskConstPointer  m_FixedImageMask{};
  MovingImageMaskConstPointer m_MovingImageMask{};

  /** Sampled point sets */
  FixedSampledPointSetConstPointer m_FixedSampledPointSet{};
  VirtualPointSetPointer           m_VirtualSampledPointSet{};

  /** Flag to use a SampledPointSet, i.e. Sparse sampling. */
  bool m_UseSampledPointSet{};

  /** Flag to indicate the user set VirtualSampledPointSet over
  FixedSampledPointSet */
  bool m_UseVirtualSampledPointSet{};

  ImageToImageMetricv4();
  ~ImageToImageMetricv4() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  /** Map the fixed point set samples to the virtual domain */
  void
  MapFixedSampledPointSetToVirtual();

  /** Transform a point. Avoid cast if possible */
  void
  LocalTransformPoint(const typename FixedTransformType::OutputPointType & virtualPoint,
                      typename FixedTransformType::OutputPointType &       mappedFixedPoint) const
  {
    mappedFixedPoint = this->m_FixedTransform->TransformPoint(virtualPoint);
  }
  // cast the virtual point
  template <typename TVirtualPoint>
  void
  LocalTransformPoint(const TVirtualPoint &                          virtualPoint,
                      typename FixedTransformType::OutputPointType & mappedFixedPoint) const
  {
    typename FixedTransformType::OutputPointType localVirtualPoint;

    localVirtualPoint.CastFrom(virtualPoint);

    mappedFixedPoint = this->m_FixedTransform->TransformPoint(localVirtualPoint);
  }
  // cast the mapped Fixed Point
  template <typename TFixedImagePoint>
  void
  LocalTransformPoint(const typename FixedTransformType::OutputPointType & virtualPoint,
                      TFixedImagePoint &                                   mappedFixedPoint) const
  {
    typename FixedTransformType::OutputPointType localMappedFixedPoint;
    localMappedFixedPoint.CastFrom(mappedFixedPoint);
    localMappedFixedPoint = this->m_FixedTransform->TransformPoint(virtualPoint);
    mappedFixedPoint.CastFrom(localMappedFixedPoint);
  }
  // cast both mapped and fixed point.
  template <typename TVirtualPoint, typename TFixedImagePoint>
  void
  LocalTransformPoint(const TVirtualPoint & virtualPoint, TFixedImagePoint & mappedFixedPoint) const
  {
    typename FixedTransformType::OutputPointType localVirtualPoint;
    typename FixedTransformType::OutputPointType localMappedFixedPoint;

    localVirtualPoint.CastFrom(virtualPoint);
    localMappedFixedPoint.CastFrom(mappedFixedPoint);

    localMappedFixedPoint = this->m_FixedTransform->TransformPoint(localVirtualPoint);
    mappedFixedPoint.CastFrom(localMappedFixedPoint);
  }

  /** Flag for warning about use of GetValue. Will be removed when
   *  GetValue implementation is improved. */
  mutable bool m_HaveMadeGetValueWarning{};

  /** Keep track of the number of sampled fixed points that are
   * deemed invalid during conversion to virtual domain.
   * For informational purposes. */
  SizeValueType m_NumberOfSkippedFixedSampledPoints{};

  bool                m_UseFloatingPointCorrection{};
  DerivativeValueType m_FloatingPointCorrectionResolution{};

  MetricTraits m_MetricTraits{};

  /** Flag to know if derivative should be calculated */
  mutable bool m_ComputeDerivative{};

  /** Only floating-point images are currently supported. To support integer images,
   * several small changes must be made */
  /** @ITKStartGrouping */
  using FixedImagePixelValueType = typename PixelTraits<FixedImagePixelType>::ValueType;
  using MovingImagePixelValueType = typename PixelTraits<MovingImagePixelType>::ValueType;
  itkConceptMacro(OnlyDefinedForFloatingPointTypes0, (itk::Concept::IsFloatingPoint<FixedImagePixelValueType>));
  itkConceptMacro(OnlyDefinedForFloatingPointTypes1, (itk::Concept::IsFloatingPoint<MovingImagePixelValueType>));
  /** @ITKEndGrouping */
};
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkImageToImageMetricv4.hxx"
#endif

#endif
