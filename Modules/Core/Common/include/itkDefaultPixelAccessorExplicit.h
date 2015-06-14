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
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<unsigned short>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<unsigned long>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 1u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<std::complex<double> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::FixedArray<float, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Index<3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<float, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<double>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<double, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::DiffusionTensor3D<float> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::SymmetricSecondRankTensor<float, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::RGBPixel<unsigned char> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<int>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<unsigned int>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<bool>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<float, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::RGBPixel<float> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<short>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 6u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Offset<2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<std::complex<float> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::FixedArray<float, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 4u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 5u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::RGBAPixel<unsigned char> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::VariableLengthVector<float> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<unsigned char, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::FixedArray<double, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 7u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<unsigned char>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<signed char>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::DiffusionTensor3D<double> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<unsigned short, 5u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::CovariantVector<float, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<char>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<float>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<float, 2u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<std::list<unsigned long, std::allocator<unsigned long> > >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::RGBPixel<unsigned short> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<long>;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 1u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::FixedArray<unsigned long, 8u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<double, 4u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<std::list<unsigned int, std::allocator<unsigned int> > >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Vector<int, 3u> >;
extern template class ITKCommon_EXPORT itk::DefaultPixelAccessor<itk::Offset<3u> >;
#endif //itkDefaultPixelAccessorExplicit_h
