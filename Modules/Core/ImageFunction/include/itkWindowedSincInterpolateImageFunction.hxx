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
#ifndef itkWindowedSincInterpolateImageFunction_hxx
#define itkWindowedSincInterpolateImageFunction_hxx


#include "itkMath.h"

namespace itk
{

// Constant definitions for functions
namespace Function
{
template <unsigned int VRadius, typename TInput, typename TOutput>
const double CosineWindowFunction<VRadius, TInput, TOutput>::m_Factor = itk::Math::pi / (2 * VRadius);

template <unsigned int VRadius, typename TInput, typename TOutput>
const double HammingWindowFunction<VRadius, TInput, TOutput>::m_Factor = itk::Math::pi / VRadius;

template <unsigned int VRadius, typename TInput, typename TOutput>
const double WelchWindowFunction<VRadius, TInput, TOutput>::m_Factor = 1.0 / (VRadius * VRadius);

template <unsigned int VRadius, typename TInput, typename TOutput>
const double LanczosWindowFunction<VRadius, TInput, TOutput>::m_Factor = itk::Math::pi / VRadius;

template <unsigned int VRadius, typename TInput, typename TOutput>
const double BlackmanWindowFunction<VRadius, TInput, TOutput>::m_Factor1 = itk::Math::pi / VRadius;

template <unsigned int VRadius, typename TInput, typename TOutput>
const double BlackmanWindowFunction<VRadius, TInput, TOutput>::m_Factor2 = 2.0 * itk::Math::pi / VRadius;
} // end namespace Function

template <typename TInputImage,
          unsigned int VRadius,
          typename TWindowFunction,
          typename TBoundaryCondition,
          typename TCoordinate>
void
WindowedSincInterpolateImageFunction<TInputImage, VRadius, TWindowFunction, TBoundaryCondition, TCoordinate>::
  SetInputImage(const ImageType * image)
{
  // Call the parent implementation
  Superclass::SetInputImage(image);

  if (image == nullptr)
  {
    return;
  }

  // Set the radius for the neighborhood
  constexpr auto radius = Size<ImageDimension>::Filled(VRadius);

  // Initialize the neighborhood
  IteratorType const it(radius, image, image->GetBufferedRegion());

  // Compute the offset tables (we ignore all the zero indices
  // in the neighborhood)
  unsigned int iOffset = 0;
  int const    empty = VRadius;
  for (unsigned int iPos = 0; iPos < it.Size(); ++iPos)
  {
    // Get the offset (index)
    typename IteratorType::OffsetType off = it.GetOffset(iPos);

    // Check if the offset has zero weights
    bool nonzero = true;
    for (unsigned int dim = 0; dim < ImageDimension; ++dim)
    {
      if (off[dim] == -empty)
      {
        nonzero = false;
        break;
      }
    }

    // Only use offsets with non-zero indices
    if (nonzero)
    {
      // Set the offset index
      m_OffsetTable[iOffset] = iPos;

      // Set the weight table indices
      for (unsigned int dim = 0; dim < ImageDimension; ++dim)
      {
        m_WeightOffsetTable[iOffset][dim] = off[dim] + VRadius - 1;
      }

      // Increment the index
      ++iOffset;
    }
  }
}

template <typename TInputImage,
          unsigned int VRadius,
          typename TWindowFunction,
          typename TBoundaryCondition,
          typename TCoordinate>
void
WindowedSincInterpolateImageFunction<TInputImage, VRadius, TWindowFunction, TBoundaryCondition, TCoordinate>::PrintSelf(
  std::ostream & os,
  Indent         indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "OffsetTable: " << m_OffsetTable << std::endl;
  os << indent << "WeightOffsetTable: " << m_WeightOffsetTable << std::endl;
}

template <typename TInputImage,
          unsigned int VRadius,
          typename TWindowFunction,
          typename TBoundaryCondition,
          typename TCoordinate>
auto
WindowedSincInterpolateImageFunction<TInputImage, VRadius, TWindowFunction, TBoundaryCondition, TCoordinate>::
  EvaluateAtContinuousIndex(const ContinuousIndexType & index) const -> OutputType
{
  IndexType baseIndex;
  double    distance[ImageDimension];

  // Compute the integer index based on the continuous one by
  // 'flooring' the index
  for (unsigned int dim = 0; dim < ImageDimension; ++dim)
  {
    baseIndex[dim] = Math::Floor<IndexValueType>(index[dim]);
    distance[dim] = index[dim] - static_cast<double>(baseIndex[dim]);
  }

  // Position the neighborhood at the index of interest
  auto         radius = Size<ImageDimension>::Filled(VRadius);
  IteratorType nit(radius, this->GetInputImage(), this->GetInputImage()->GetBufferedRegion());
  nit.SetLocation(baseIndex);

  // Compute the sinc function for each dimension
  double xWeight[ImageDimension][2 * VRadius];
  for (unsigned int dim = 0; dim < ImageDimension; ++dim)
  {
    // x is the offset, hence the parameter of the kernel
    double x = distance[dim] + VRadius;

    // If distance is zero, i.e. the index falls precisely on the
    // pixel boundary, the weights form a delta function.
    if (distance[dim] == 0.0)
    {
      for (unsigned int i = 0; i < m_WindowSize; ++i)
      {
        xWeight[dim][i] = static_cast<int>(i) == VRadius - 1 ? 1 : 0;
      }
    }
    else
    {
      // i is the relative offset in dimension dim.
      for (unsigned int i = 0; i < m_WindowSize; ++i)
      {
        // Increment the offset, taking it through the range
        // (dist + rad - 1, ..., dist - rad), i.e. all x
        // such that itk::Math::abs(x) <= rad
        x -= 1.0;

        // Compute the weight for this m
        xWeight[dim][i] = m_WindowFunction(x) * Sinc(x);
      }
    }
  }

  // Iterate over the neighborhood, taking the correct set
  // of weights in each dimension
  using PixelType = typename NumericTraits<typename TInputImage::PixelType>::RealType;
  PixelType xPixelValue{};
  for (unsigned int j = 0; j < m_OffsetTableSize; ++j)
  {
    // Get the offset for this neighbor
    unsigned int const off = m_OffsetTable[j];

    // Get the intensity value at the pixel
    PixelType xVal = nit.GetPixel(off);

    // Multiply the intensity by each of the weights. Gotta hope
    // that the compiler will unwrap this loop and pipeline this!
    for (unsigned int dim = 0; dim < ImageDimension; ++dim)
    {
      xVal *= xWeight[dim][m_WeightOffsetTable[j][dim]];
    }

    // Increment the pixel value
    xPixelValue += xVal;
  }

  // Return the interpolated value
  return static_cast<OutputType>(xPixelValue);
}
} // namespace itk

#endif
