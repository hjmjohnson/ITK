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
#ifndef itkVanHerkGilWermanErodeDilateImageFilter_h
#define itkVanHerkGilWermanErodeDilateImageFilter_h

#include "itkKernelImageFilter.h"
#include "itkProgressReporter.h"
#include "itkBresenhamLine.h"

namespace itk
{

template <typename TInputImage, typename TOutputImage, typename TKernel>
class KernelImageFilter;

/**
 * \class VanHerkGilWermanErodeDilateImageFilter
 * \brief class to implement erosions and dilations using anchor
 * methods. This is the base class that must be instantiated with
 * appropriate definitions of greater, less and so on.
 * The SetBoundary facility isn't necessary for operation of the
 * anchor method but is included for compatibility with other
 * morphology classes in itk.
 * \ingroup ITKMathematicalMorphology
 */
template <typename TImage, typename TKernel, typename TFunction1>
class ITK_TEMPLATE_EXPORT VanHerkGilWermanErodeDilateImageFilter : public KernelImageFilter<TImage, TImage, TKernel>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(VanHerkGilWermanErodeDilateImageFilter);

  /** Standard class type aliases. */
  using Self = VanHerkGilWermanErodeDilateImageFilter;
  using Superclass = KernelImageFilter<TImage, TImage, TKernel>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Some convenient type alias. */

  /** Kernel type alias. */
  using KernelType = TKernel;

  using InputImageType = TImage;
  using InputImagePointer = typename InputImageType::Pointer;
  using InputImageConstPointer = typename InputImageType::ConstPointer;
  using InputImageRegionType = typename InputImageType::RegionType;
  using InputImagePixelType = typename InputImageType::PixelType;
  using IndexType = typename TImage::IndexType;
  using SizeType = typename TImage::SizeType;

  /** ImageDimension constants */
  static constexpr unsigned int InputImageDimension = TImage::ImageDimension;
  static constexpr unsigned int OutputImageDimension = TImage::ImageDimension;

  /** Standard New method. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(VanHerkGilWermanErodeDilateImageFilter);

  /** Set/Get the boundary value. */
  /** @ITKStartGrouping */
  itkSetMacro(Boundary, InputImagePixelType);
  itkGetConstMacro(Boundary, InputImagePixelType);
  /** @ITKEndGrouping */
protected:
  VanHerkGilWermanErodeDilateImageFilter();
  ~VanHerkGilWermanErodeDilateImageFilter() override = default;
  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** Multi-thread version GenerateData. */
  void
  DynamicThreadedGenerateData(const InputImageRegionType & outputRegionForThread) override;


  // should be set by the meta filter
  InputImagePixelType m_Boundary{};

private:
  using BresType = BresenhamLine<Self::InputImageDimension>;

}; // end of class
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkVanHerkGilWermanErodeDilateImageFilter.hxx"
#endif

#endif
