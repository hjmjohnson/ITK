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
#ifndef itkCurvesLevelSetFunction_h
#define itkCurvesLevelSetFunction_h

#include "itkSegmentationLevelSetFunction.h"

namespace itk
{
/** \class CurvesLevelSetFunction
 *
 * \brief This function is used in CurvesLevelSetImageFilter to
 * segment structures in images based on user supplied edge potential map.
 *
 * \par CurvesLevelSetFunction is a subclass of the generic LevelSetFunction.
 * It is useful for segmentations based on a user supplied edge potential map which
 * has values close to zero in regions near edges (or high image gradient) and values
 * close to one in regions with relatively constant intensity. Typically, the edge
 * potential map is a function of the gradient, for example:
 *
 * \f[ g(I) = 1 / ( 1 + | (\nabla * G)(I)| ) \f]
 * \f[ g(I) = \exp^{-|(\nabla * G)(I)|} \f]
 *
 * where \f$ I \f$ is image intensity and
 * \f$ (\nabla * G) \f$ is the derivative of Gaussian operator.
 *
 * \par In this function both the propagation term \f$ P(\mathbf{x}) \f$
 * and the curvature spatial modifier term $\f$ Z(\mathbf{x}) \f$ are taken directly
 * from the edge potential image. The edge potential image is set via the
 * SetFeatureImage() method. An advection term \f$ A(\mathbf{x}) \f$ is constructed
 * from the negative gradient of the edge potential image. This term behaves like
 * a doublet attracting the contour to the edges.
 *
 * \par Reference:
 * This implementation is based on \cite lorigo2001.
 *
 * \sa LevelSetFunction
 * \sa SegmentationLevelSetImageFunction
 * \sa GeodesicActiveContourLevelSetImageFilter
 *
 * \ingroup FiniteDifferenceFunctions
 * \ingroup ITKLevelSets
 */
template <typename TImageType, typename TFeatureImageType = TImageType>
class ITK_TEMPLATE_EXPORT CurvesLevelSetFunction : public SegmentationLevelSetFunction<TImageType, TFeatureImageType>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(CurvesLevelSetFunction);

  /** Standard class type aliases. */
  using Self = CurvesLevelSetFunction;
  using Superclass = SegmentationLevelSetFunction<TImageType, TFeatureImageType>;
  using SuperSuperclass = LevelSetFunction<TImageType>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using FeatureImageType = TFeatureImageType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(CurvesLevelSetFunction);

  /** Extract some parameters from the superclass. */
  using PixelType = typename SuperSuperclass::PixelType;
  using typename Superclass::ImageType;
  using typename Superclass::NeighborhoodType;
  using typename Superclass::ScalarValueType;
  using typename Superclass::FeatureScalarType;
  using typename Superclass::RadiusType;
  using FloatOffsetType = typename SuperSuperclass::FloatOffsetType;
  using GlobalDataStruct = typename SuperSuperclass::GlobalDataStruct;
  using typename Superclass::VectorImageType;

  /** Extract some parameters from the superclass. */
  static constexpr unsigned int ImageDimension = Superclass::ImageDimension;

  /** Compute speed image from feature image. */
  void
  CalculateSpeedImage() override;

  /** Compute the advection field from feature image. */
  void
  CalculateAdvectionImage() override;

  /** The curvature speed is same as the propagation speed. */
  ScalarValueType
  CurvatureSpeed(const NeighborhoodType & neighborhood,
                 const FloatOffsetType &  offset,
                 GlobalDataStruct *       gd) const override
  {
    return this->PropagationSpeed(neighborhood, offset, gd);
  }

  /** Set/Get the sigma for the Gaussian kernel used to compute the gradient
   * of the feature image needed for the advection term of the equation. */
  /** @ITKStartGrouping */
  void
  SetDerivativeSigma(const double v)
  {
    m_DerivativeSigma = v;
  }
  double
  GetDerivativeSigma()
  {
    return m_DerivativeSigma;
  }
  /** @ITKEndGrouping */
  void
  Initialize(const RadiusType & r) override;

protected:
  CurvesLevelSetFunction()

  {
    // Curvature term is the minimal curvature.
    this->UseMinimalCurvatureOn();
    this->SetAdvectionWeight(NumericTraits<ScalarValueType>::OneValue());
    this->SetPropagationWeight(NumericTraits<ScalarValueType>::OneValue());
    this->SetCurvatureWeight(NumericTraits<ScalarValueType>::OneValue());
  }

  ~CurvesLevelSetFunction() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override
  {
    Superclass::PrintSelf(os, indent);
    os << indent << "DerivativeSigma: " << m_DerivativeSigma << std::endl;
  }

private:
  /** Slices for the ND neighborhood. */
  std::slice x_slice[ImageDimension];

  /** The offset of the center pixel in the neighborhood. */
  OffsetValueType m_Center{ 0 };

  /** Stride length along the y-dimension. */
  OffsetValueType m_xStride[ImageDimension]{};

  double m_DerivativeSigma{ 1.0 };
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkCurvesLevelSetFunction.hxx"
#endif

#endif
