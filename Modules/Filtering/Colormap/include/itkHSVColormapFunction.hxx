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
#ifndef itkHSVColormapFunction_hxx
#define itkHSVColormapFunction_hxx


namespace itk
{
namespace Function
{
template <typename TScalar, typename TRGBPixel>
auto
HSVColormapFunction<TScalar, TRGBPixel>::operator()(const TScalar & v) const -> RGBPixelType
{
  // Map the input scalar between [0, 1].
  RealType const value = this->RescaleInputValue(v);

  // Apply the color mapping.
  // Apply the color mapping.
  RealType red = itk::Math::abs(5.0 * (value - 0.5)) - 5.0 / 6.0;
  red = std::clamp(red, 0.0, 1.0);

  RealType green = -itk::Math::abs(5.0 * (value - 11.0 / 30.0)) + 11.0 / 6.0;
  green = std::clamp(green, 0.0, 1.0);

  RealType blue = -itk::Math::abs(5.0 * (value - 19.0 / 30.0)) + 11.0 / 6.0;
  blue = std::clamp(blue, 0.0, 1.0);

  // Set the rgb components after rescaling the values.
  RGBPixelType pixel;
  NumericTraits<TRGBPixel>::SetLength(pixel, 3);

  pixel[0] = this->RescaleRGBComponentValue(red);
  pixel[1] = this->RescaleRGBComponentValue(green);
  pixel[2] = this->RescaleRGBComponentValue(blue);

  return pixel;
}
} // end namespace Function
} // end namespace itk

#endif
