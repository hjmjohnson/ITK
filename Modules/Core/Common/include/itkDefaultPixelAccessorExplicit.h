/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkDefaultPixelAccessorExplicit_h
#define itkDefaultPixelAccessorExplicit_h
#include "itkDiffusionTensor3D.h"
#include "itkRGBPixel.h"
#include "itkRGBAPixel.h"
#include "itkVariableLengthVector.h"
#include "itkIndex.h"
#include <list>
#include <complex>
//exclude watershed
//exclude fem
//exclude TileImageFilter
//subs std:: std::
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<unsigned short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<unsigned long>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 1u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<std::complex<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::FixedArray<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Index<3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<double>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::CovariantVector<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::DiffusionTensor3D<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::RGBPixel<unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<unsigned int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<bool>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::CovariantVector<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::RGBPixel<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 6u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Offset<2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<std::complex<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::FixedArray<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 4u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 5u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::CovariantVector<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::RGBAPixel<unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::VariableLengthVector<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<unsigned char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::FixedArray<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 7u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<unsigned char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<signed char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::DiffusionTensor3D<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<unsigned short, 5u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::CovariantVector<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<float>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<std::list<unsigned long, std::allocator<unsigned long> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::RGBPixel<unsigned short> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<long>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<double, 1u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::FixedArray<unsigned long, 8u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<double, 4u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<std::list<unsigned int, std::allocator<unsigned int> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Vector<int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DefaultPixelAccessor<itk::Offset<3u> >;
#endif //itkDefaultPixelAccessorExplicit_h
