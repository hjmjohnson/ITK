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
#ifndef itkImageRegionConstIteratorWithIndexExplicit_h
#define itkImageRegionConstIteratorWithIndexExplicit_h
#include "itkVectorImage.h"
//exclude TileImageFilter
//exclude VectorImageToImageAdaptor
//exclude NthElementImageAdaptor
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned char, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 1u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<long, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 1u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 2u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::VariableLengthVector<float>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 6u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned long, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 7u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::SymmetricSecondRankTensor<float, 3u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<double, 3u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::list<unsigned int, std::allocator<unsigned int> >, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<signed char, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::CovariantVector<float, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 1u>, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned short, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 4u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<float, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<int, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::complex<float>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<short, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::complex<float>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::list<unsigned int, std::allocator<unsigned int> >, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 1u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned char, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<signed char, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<double, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::complex<double>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::FixedArray<float, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<bool, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned int, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<double, 6u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<signed char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned int, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<float, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<double, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<double, 1u>, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<int, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<long, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::list<unsigned long, std::allocator<unsigned long> >, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<bool, 1u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<float, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 6u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<short, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<short, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned long, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 3u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned short, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<int, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<double, 2u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 6u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 7u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::VariableLengthVector<float>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Offset<2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned int, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 2u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<long, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::FixedArray<float, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<double, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<int, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Offset<3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned long, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<std::complex<double>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<double, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned short, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<bool, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned int, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::Vector<float, 3u>, 4u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<signed char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<char, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<float, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<short, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned int, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::CovariantVector<float, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned short, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::SymmetricSecondRankTensor<float, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<long, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::VectorImage<unsigned long, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::CovariantVector<double, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<unsigned char, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::DiffusionTensor3D<double>, 3u> >;
extern template class ITKCommon_EXPORT itk::ImageRegionConstIteratorWithIndex<itk::Image<itk::CovariantVector<double, 2u>, 2u> >;
#endif //itkImageRegionConstIteratorWithIndexExplicit_h
