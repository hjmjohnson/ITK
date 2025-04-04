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
#ifndef itkMedianImageFunction_h
#define itkMedianImageFunction_h

#include "itkImageFunction.h"
#include "itkImageNeighborhoodOffsets.h"
#include "itkNumericTraits.h"
#include "itkOffset.h"

namespace itk
{
/**
 * \class MedianImageFunction
 * \brief Calculate the median value in the neighborhood of a pixel
 *
 * Calculate the median pixel value over the standard 8, 26, etc. connected
 * neighborhood.  This calculation uses a ZeroFluxNeumannBoundaryCondition.
 *
 * If called with a ContinuousIndex or Point, the calculation is performed
 * at the nearest neighbor.
 *
 * This class is templated over the input image type and the
 * coordinate representation type (e.g. float or double ).
 *
 * \ingroup ImageFunctions
 * \ingroup ITKImageFunction
 *
 * \sphinx
 * \sphinxexample{Core/ImageFunction/ComputeMedianOfImageAtPixel,Compute Median Of Image At Pixel}
 * \endsphinx
 */
template <typename TInputImage, typename TCoordinate = float>
class ITK_TEMPLATE_EXPORT MedianImageFunction
  : public ImageFunction<TInputImage, typename TInputImage::PixelType, TCoordinate>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(MedianImageFunction);

  /** Standard class type aliases. */
  using Self = MedianImageFunction;
  using Superclass = ImageFunction<TInputImage, typename TInputImage::PixelType, TCoordinate>;

  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(MedianImageFunction);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** InputImageType type alias support */
  using InputImageType = TInputImage;
  using typename Superclass::InputPixelType;

  /** OutputType type alias support */
  using typename Superclass::OutputType;

  /** Index type alias support */
  using typename Superclass::IndexType;

  /** ContinuousIndex type alias support */
  using typename Superclass::ContinuousIndexType;

  /** Point type alias support */
  using typename Superclass::PointType;

  /** Size type of the underlying image. */
  using ImageSizeType = typename InputImageType::SizeType;

  /** Dimension of the underlying image. */
  static constexpr unsigned int ImageDimension = InputImageType::ImageDimension;

  /** Evaluate the function at specified index */
  OutputType
  EvaluateAtIndex(const IndexType & index) const override;

  /** Evaluate the function at non-integer positions */
  OutputType
  Evaluate(const PointType & point) const override
  {
    IndexType index;

    this->ConvertPointToNearestIndex(point, index);
    return this->EvaluateAtIndex(index);
  }

  OutputType
  EvaluateAtContinuousIndex(const ContinuousIndexType & cindex) const override
  {
    IndexType index;

    this->ConvertContinuousIndexToNearestIndex(cindex, index);
    return this->EvaluateAtIndex(index);
  }

  /** Get/Set the radius of the neighborhood over which the
      statistics are evaluated */
  /** @ITKStartGrouping */
  void
  SetNeighborhoodRadius(unsigned int);
  itkGetConstReferenceMacro(NeighborhoodRadius, unsigned int);
  /** @ITKEndGrouping */
protected:
  MedianImageFunction();
  ~MedianImageFunction() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

private:
  unsigned int m_NeighborhoodRadius{ 1 };

  std::vector<Offset<ImageDimension>> m_NeighborhoodOffsets{ GenerateRectangularImageNeighborhoodOffsets(
    ImageSizeType::Filled(1)) };
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkMedianImageFunction.hxx"
#endif

#endif
