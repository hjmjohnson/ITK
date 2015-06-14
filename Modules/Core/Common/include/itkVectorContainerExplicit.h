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
#ifndef itkVectorContainerExplicit_h
#define itkVectorContainerExplicit_h
#include "itkCellInterface.h"
#include "itkPoint.h"
#include "itkContinuousIndex.h"
#include "itkMatrix.h"
#include "itkVariableSizeMatrix.h"
#include <set>
#include <algorithm>
//exclude LevelSetNode
//exclude NodePair
//exclude fem
//exclude ::Statistics
//subs std:: std::
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, float>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<double, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<float, 1u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<float, 4u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned char, double>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, unsigned int>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<double, 1u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<float, itk::CellTraitsInfo<3, float, float, unsigned long, unsigned long, unsigned long, itk::Point<float, 3u>, itk::VectorContainer<unsigned long, itk::Point<float, 3u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, double>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<double, itk::CellTraitsInfo<3, float, float, unsigned long, unsigned long, unsigned long, itk::Point<float, 3u>, itk::VectorContainer<unsigned long, itk::Point<float, 3u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, vnl_vector<double> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<float, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<double, 4u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<long, itk::Array<unsigned long> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, float>;
extern template class ITKCommon_EXPORT itk::VectorContainer<long, itk::Array<long> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, unsigned long>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<float, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<float, 1u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, itk::Index<2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned char, short>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, double>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<double, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<float, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<double, itk::CellTraitsInfo<3, double, double, unsigned long, unsigned long, unsigned long, itk::Point<double, 3u>, itk::VectorContainer<unsigned long, itk::Point<double, 3u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, unsigned short>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<unsigned char, itk::CellTraitsInfo<3, float, float, unsigned long, unsigned long, unsigned long, itk::Point<float, 3u>, itk::VectorContainer<unsigned long, itk::Point<float, 3u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, itk::Index<3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<int, itk::CellTraitsInfo<3, float, float, unsigned long, unsigned long, unsigned long, itk::Point<float, 3u>, itk::VectorContainer<unsigned long, itk::Point<float, 3u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, int>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, itk::ContinuousIndex<double, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Point<float, 2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned char, itk::Offset<2u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, long>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned int, vnl_vector_fixed<double, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, unsigned char>;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::Matrix<double, 3u, 3u> >;
extern template class ITKCommon_EXPORT itk::VectorContainer<unsigned long, itk::CellInterface<unsigned char, itk::CellTraitsInfo<2, float, float, unsigned long, unsigned long, unsigned long, itk::Point<float, 2u>, itk::VectorContainer<unsigned long, itk::Point<float, 2u> >, std::set<unsigned long, std::less<unsigned long>, std::allocator<unsigned long> > > >*>;
#endif //itkVectorContainerExplicit_h
