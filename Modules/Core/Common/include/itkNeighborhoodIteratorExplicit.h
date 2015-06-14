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
#ifndef itkNeighborhoodIteratorExplicit_h
#define itkNeighborhoodIteratorExplicit_h
#include "itkSparseImage.h"
//exclude deque
//exclude NormalBandNode
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<double, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<double, 3u>, itk::Image<double, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned int, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned char, 1u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned char, 1u>, itk::Image<unsigned char, 1u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<long, 1u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<long, 1u>, itk::Image<long, 1u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned int, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<float, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<float, 3u>, itk::Image<float, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<double, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<double, 2u>, itk::Image<double, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<long, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<long, 3u>, itk::Image<long, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<short, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<short, 3u>, itk::Image<short, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned char, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::VectorImage<double, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::VectorImage<double, 2u>, itk::VectorImage<double, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<bool, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<bool, 2u>, itk::Image<bool, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::VectorImage<float, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::VectorImage<float, 2u>, itk::VectorImage<float, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<float, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<float, 2u>, itk::Image<float, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned short, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<itk::Vector<double, 2u>, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned long, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned long, 2u>, itk::Image<unsigned long, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned short, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned long, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned long, 3u>, itk::Image<unsigned long, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<itk::Vector<float, 3u>, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<signed char, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<signed char, 3u>, itk::Image<signed char, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<short, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<short, 2u>, itk::Image<short, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::VectorImage<float, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<long, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<long, 2u>, itk::Image<long, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<int, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<int, 3u>, itk::Image<int, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::VectorImage<double, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::VectorImage<double, 3u>, itk::VectorImage<double, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<itk::Vector<double, 2u>, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned char, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<bool, 3u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<bool, 3u>, itk::Image<bool, 3u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<int, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<int, 2u>, itk::Image<int, 2u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<unsigned int, 4u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<unsigned int, 4u>, itk::Image<unsigned int, 4u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<bool, 1u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<bool, 1u>, itk::Image<bool, 1u> > >;
extern template class ITKCommon_EXPORT itk::NeighborhoodIterator<itk::Image<signed char, 2u>, itk::ZeroFluxNeumannBoundaryCondition<itk::Image<signed char, 2u>, itk::Image<signed char, 2u> > >;
#endif //itkNeighborhoodIteratorExplicit_h
