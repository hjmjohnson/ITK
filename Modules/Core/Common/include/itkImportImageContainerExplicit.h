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
#ifndef itkImportImageContainerExplicit_h
#define itkImportImageContainerExplicit_h
#include "itkDiffusionTensor3D.h"
#include "itkRGBPixel.h"
#include "itkRGBAPixel.h"
#include "itkVariableLengthVector.h"
#include "itkOffset.h"
#include "itkIndex.h"
#include "itkImage.h"
#include <list>
#include <complex>
//exclude LabelObjectLine
//exclude NormalBandNode
//exclude watershed
//exclude fem
//exclude TileImageFilter
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::DiffusionTensor3D<float> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::RGBPixel<unsigned short> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, unsigned int>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, unsigned char>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, char>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::FixedArray<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 6u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::RGBAPixel<unsigned char> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 1u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::RGBPixel<unsigned char> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, long>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, double>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Offset<3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::CovariantVector<float, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::CovariantVector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::FixedArray<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, signed char>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, std::complex<float> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::VariableLengthVector<float> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Index<3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::CovariantVector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, std::list<unsigned long, std::allocator<unsigned long> > >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::RGBPixel<float> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<double, 1u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::FixedArray<unsigned long, 8u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, int>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<int, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 5u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<double, 4u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::SymmetricSecondRankTensor<double, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 7u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Offset<2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, short>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, std::complex<double> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, float>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::SymmetricSecondRankTensor<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::CovariantVector<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::SymmetricSecondRankTensor<double, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, unsigned long>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::SymmetricSecondRankTensor<float, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, bool>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 3u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, std::list<unsigned int, std::allocator<unsigned int> > >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::CovariantVector<float, 4u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<unsigned short, 5u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, unsigned short>;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<unsigned char, 2u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::Vector<float, 4u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::FixedArray<unsigned char, 4u> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::DiffusionTensor3D<double> >;
extern template class ITKCommon_EXPORT itk::ImportImageContainer<unsigned long, itk::FixedArray<float, 3u> >;
#endif //itkImportImageContainerExplicit_h
