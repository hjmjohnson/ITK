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
#ifndef itkAzimuthElevationToCartesianTransform_h
#define itkAzimuthElevationToCartesianTransform_h

#include "itkAffineTransform.h"
#include "itkMath.h"

namespace itk
{
/** \class AzimuthElevationToCartesianTransform
 *
 * \brief Transforms from an azimuth, elevation, radius coordinate system to
 * a Cartesian coordinate system, or vice versa.
 *
 * The three coordinate axis are azimuth, elevation, and range.
 *
 * The azimuth elevation coordinate system is defined similarly to spherical
 * coordinates but is slightly different in that the azimuth and elevation are
 * measured in degrees between the r-axis (i.e z axis) and the projection on
 * the x-z and y-z planes, respectively.  Range, or r, is the distance from
 * the origin.
 *
 * The equations form performing the conversion from azimuth-elevation
 * coordinates to cartesian coordinates are as follows:
\code
z = std::sqrt((r^2*(cos(azimuth))^2)/(1 + (cos(azimuth))^2 * (tan(elevation))^2);
x = z * std::tan(azimuth)
y = z * std::tan(elevation)
\endcode
 *
 * The reversed transforms are:
\code
azimuth = arctan(x/y)
elevation = arctan(y/z)
r = std::sqrt(x^2 + y^2 + z^2)
\endcode
 *
 * In this class, we can also set what a "forward" transform means.  If we call
 * SetForwardAzimuthElevationToCartesian(), a forward transform will return
 * cartesian coordinates when passed azimuth,elevation,r coordinates.  Calling
 * SetForwardCartesianToAzimuthElevation() will cause the forward transform
 * to return azimuth,elevation,r coordinates from cartesian coordinates.
 *
 * Setting the FirstSampleDistance to a non-zero value means that a r value
 * of 12 is actually (12 + FirstSampleDistance) distance from the origin.
 *
 * There are two template parameters for this class:
 *
 * TParametersValueType  The type to be used for scalar numeric
 *                       values.  Either float or double.
 *
 * VDimension   The number of dimensions of the vector space (must be >=3).
 *
 * \todo Is there any real value in allowing the user to template
 * over the scalar type?  Perhaps it should always be double, unless
 * there's a compatibility problem with the Point class.
 *
 * \todo Derive this class from TransformBase class.
 * Currently, this class derives from AffineTransform, although
 * it is not an affine transform.
 *
 * \todo Add a figure in the documentation that informs the formulas used in this class
 * that are used to transform Cartesian to azimuth-elevation-radius
 *
 * \ingroup ITKTransform
 *
 * \sphinx
 * \sphinxexample{Core/Transform/CartesianToAzimuthElevation,Cartesian To Azimuth Elevation}
 * \endsphinx
 */
template <typename TParametersValueType = double, unsigned int VDimension = 3>
class ITK_TEMPLATE_EXPORT AzimuthElevationToCartesianTransform
  : public AffineTransform<TParametersValueType, VDimension>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(AzimuthElevationToCartesianTransform);

  /** Standard class type aliases.   */
  using Self = AzimuthElevationToCartesianTransform;
  using Superclass = AffineTransform<TParametersValueType, VDimension>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Dimension of the domain space. */
  static constexpr unsigned int SpaceDimension = VDimension;
  static constexpr unsigned int ParametersDimension = VDimension * (VDimension + 1);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(AzimuthElevationToCartesianTransform);

  /** New macro for creation of through a Smart Pointer.   */
  itkNewMacro(Self);

  /** Parameters type.   */
  using typename Superclass::ParametersType;
  using typename Superclass::FixedParametersType;
  using typename Superclass::TransformCategoryEnum;

  /** Jacobian type.   */
  using typename Superclass::JacobianType;
  using typename Superclass::JacobianPositionType;
  using typename Superclass::InverseJacobianPositionType;

  /** Standard scalar type for this class. */
  using typename Superclass::ScalarType;

  /** Standard coordinate point type for this class */
  using typename Superclass::InputPointType;
  using typename Superclass::OutputPointType;

  /** Standard matrix type for this class.   */
  using MatrixType = Matrix<TParametersValueType, Self::SpaceDimension, Self::SpaceDimension>;

  /** Set the transformation parameters. */
  void
  SetAzimuthElevationToCartesianParameters(const double sampleSize,
                                           const double firstSampleDistance,
                                           const long   maxAzimuth,
                                           const long   maxElevation,
                                           const double azimuthAngleSeparation,
                                           const double elevationAngleSeparation);

  void
  SetAzimuthElevationToCartesianParameters(const double sampleSize,
                                           const double firstSampleDistance,
                                           const long   maxAzimuth,
                                           const long   maxElevation);

  /** Transform from azimuth-elevation to cartesian. */
  OutputPointType
  TransformPoint(const InputPointType & point) const override;

  /** Back transform from cartesian to azimuth-elevation.  */
  inline InputPointType
  BackTransform(const OutputPointType & point) const
  {
    InputPointType result;

    if (m_ForwardAzimuthElevationToPhysical)
    {
      result = static_cast<InputPointType>(TransformCartesianToAzEl(point));
    }
    else
    {
      result = static_cast<InputPointType>(TransformAzElToCartesian(point));
    }
    return result;
  }

  inline InputPointType
  BackTransformPoint(const OutputPointType & point) const
  {
    return BackTransform(point);
  }


  /** Overrides the TransformCategoryEnum to  UnknownTransformCategory. Even though
  this class derives from AffineTransform, its not a linear transform */
  TransformCategoryEnum
  GetTransformCategory() const override
  {
    return Self::TransformCategoryEnum::UnknownTransformCategory;
  }

  /** Defines that the forward transform goes from azimuth,elevation to
   *  cartesian. */
  void
  SetForwardAzimuthElevationToCartesian();

  /** Defines that the forward transform goes from cartesian to azimuth,
   *  elevation.  */
  void
  SetForwardCartesianToAzimuthElevation();

  /** Transform a point from azimuth-elevation coordinates to Cartesian coordinates. */
  OutputPointType
  TransformAzElToCartesian(const InputPointType & point) const;

  /** Transform a point from Cartesian coordinates to azimuth-elevation coordinates. */
  OutputPointType
  TransformCartesianToAzEl(const OutputPointType & point) const;

  /**  Set the maximum azimuth.
   *  The maximum azimuth and elevation can be set so that the resulting
   *  cartesian space is symmetric about the z axis.  Therefore, the line
   *  defined by azimuth/2,elevation/2 = z-axis. */
  /** @ITKStartGrouping */
  itkSetMacro(MaxAzimuth, long);
  itkGetConstMacro(MaxAzimuth, long);
  /** @ITKEndGrouping */
  /**  Set the maximum elevation
   *  The maximum azimuth and elevation can be set so that the resulting
   *  cartesian space is symmetric about the z axis.  Therefore, the line
   *  defined by azimuth/2,elevation/2 = z-axis. */
  /** @ITKStartGrouping */
  itkSetMacro(MaxElevation, long);
  itkGetConstMacro(MaxElevation, long);
  /** @ITKEndGrouping */
  /**  Set the number of cartesian units between each unit along the R . */
  /** @ITKStartGrouping */
  itkSetMacro(RadiusSampleSize, double);
  itkGetConstMacro(RadiusSampleSize, double);
  /** @ITKEndGrouping */
  /**  Set the number of degrees between each azimuth unit. */
  /** @ITKStartGrouping */
  itkSetMacro(AzimuthAngularSeparation, double);
  itkGetConstMacro(AzimuthAngularSeparation, double);
  /** @ITKEndGrouping */
  /**  Set the number of degrees between each elevation unit. */
  /** @ITKStartGrouping */
  itkSetMacro(ElevationAngularSeparation, double);
  itkGetConstMacro(ElevationAngularSeparation, double);
  /** @ITKEndGrouping */
  /**  Set the distance to add to the radius. */
  /** @ITKStartGrouping */
  itkSetMacro(FirstSampleDistance, double);
  itkGetConstMacro(FirstSampleDistance, double);
  /** @ITKEndGrouping */
protected:
  /** Create an AzimuthElevationToCartesianTransform object. */
  AzimuthElevationToCartesianTransform();

  /** Destroy an AzimuthElevationToCartesianTransform object. */
  ~AzimuthElevationToCartesianTransform() override = default;

  /** Print contents of an AzimuthElevationTransform. */
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  long   m_MaxAzimuth{};
  long   m_MaxElevation{};
  double m_RadiusSampleSize{};
  double m_AzimuthAngularSeparation{};
  double m_ElevationAngularSeparation{};
  double m_FirstSampleDistance{};
  bool   m_ForwardAzimuthElevationToPhysical{};
}; // class AzimuthElevationToCartesianTransform
} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkAzimuthElevationToCartesianTransform.hxx"
#endif

#endif /* itkAzimuthElevationToCartesianTransform_h */
