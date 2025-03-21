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
#ifndef itkXorImageFilter_h
#define itkXorImageFilter_h

#include "itkBinaryGeneratorImageFilter.h"
#include "itkBitwiseOpsFunctors.h"
#include "itkNumericTraits.h"

namespace itk
{
/**
 * \class XorImageFilter
 * \brief Computes the XOR bitwise operator pixel-wise between two images.
 *
 * This class is templated over the types of the two
 * input images and the type of the output image.
 * Numeric conversions (castings) are done by the C++ defaults.
 *
 * Since the bitwise XOR operation is only defined in C++ for integer
 * types, the images passed to this filter must comply with the requirement
 * of using integer pixel type.
 *
 * The total operation over one pixel will be
 *
   \code
    output_pixel = static_cast<OutputPixelType>( input1_pixel ^ input2_pixel )
   \endcode
 *
 * Where "^" is the boolean XOR operator in C++.
 *
 * \ingroup IntensityImageFilters
 * \ingroup MultiThreaded
 * \ingroup ITKImageIntensity
 *
 * \sphinx
 * \sphinxexample{Filtering/ImageIntensity/BinaryXORTwoImages,Binary XOR Two Images}
 * \endsphinx
 */
template <typename TInputImage1, typename TInputImage2 = TInputImage1, typename TOutputImage = TInputImage1>
class ITK_TEMPLATE_EXPORT XorImageFilter : public BinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(XorImageFilter);

  /** Standard class type aliases. */
  using Self = XorImageFilter;
  using Superclass = BinaryGeneratorImageFilter<TInputImage1, TInputImage2, TOutputImage>;

  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;
  using FunctorType =
    Functor::XOR<typename TInputImage1::PixelType, typename TInputImage2::PixelType, typename TOutputImage::PixelType>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(XorImageFilter);

  itkConceptMacro(Input1Input2OutputBitwiseOperatorsCheck,
                  (Concept::BitwiseOperators<typename TInputImage1::PixelType,
                                             typename TInputImage2::PixelType,
                                             typename TOutputImage::PixelType>));

protected:
  XorImageFilter()
  {
#if !defined(ITK_WRAPPING_PARSER)
    Superclass::SetFunctor(FunctorType());
#endif
  }

  ~XorImageFilter() override = default;
};
} // end namespace itk

#endif
