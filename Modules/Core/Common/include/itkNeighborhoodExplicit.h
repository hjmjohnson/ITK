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
#ifndef itkNeighborhoodExplicit_h
#define itkNeighborhoodExplicit_h
#include "itkFixedArray.h"
//exclude LabelObjectLine
//exclude NormalBandNode
//exclude Index
//exclude Vector
//exclude RGBAPixel
//exclude RGBPixel
//exclude VariableLengthVector
extern template class ITKCommon_EXPORT itk::Neighborhood<signed char, 2u, itk::NeighborhoodAllocator<signed char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<int*, 2u, itk::NeighborhoodAllocator<int*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned long*, 2u, itk::NeighborhoodAllocator<unsigned long*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char*, 3u, itk::NeighborhoodAllocator<unsigned char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned short*, 2u, itk::NeighborhoodAllocator<unsigned short*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float, 1u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool, 1u, itk::NeighborhoodAllocator<bool> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned long, 2u, itk::NeighborhoodAllocator<unsigned long> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool, 4u, itk::NeighborhoodAllocator<bool> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long*, 1u, itk::NeighborhoodAllocator<long*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int*, 2u, itk::NeighborhoodAllocator<unsigned int*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char, 3u, itk::NeighborhoodAllocator<unsigned char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double*, 4u, itk::NeighborhoodAllocator<double*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int, 4u, itk::NeighborhoodAllocator<unsigned int> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int, 2u, itk::NeighborhoodAllocator<unsigned int> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float*, 3u, itk::NeighborhoodAllocator<float*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double, 4u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool, 2u, itk::NeighborhoodAllocator<bool> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<int, 3u, itk::NeighborhoodAllocator<int> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double, 2u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned long*, 3u, itk::NeighborhoodAllocator<unsigned long*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double*, 6u, itk::NeighborhoodAllocator<double*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long, 1u, itk::NeighborhoodAllocator<long> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float, 2u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int*, 3u, itk::NeighborhoodAllocator<unsigned int*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float, 3u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned short, 2u, itk::NeighborhoodAllocator<unsigned short> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<itk::FixedArray<unsigned char, 4u>*, 3u, itk::NeighborhoodAllocator<itk::FixedArray<unsigned char, 4u>*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int*, 4u, itk::NeighborhoodAllocator<unsigned int*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<signed char, 3u, itk::NeighborhoodAllocator<signed char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char, 2u, itk::NeighborhoodAllocator<unsigned char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<char*, 2u, itk::NeighborhoodAllocator<char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long, 3u, itk::NeighborhoodAllocator<long> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned short*, 3u, itk::NeighborhoodAllocator<unsigned short*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<signed char*, 2u, itk::NeighborhoodAllocator<signed char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<char, 2u, itk::NeighborhoodAllocator<char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double, 6u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float*, 2u, itk::NeighborhoodAllocator<float*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double*, 2u, itk::NeighborhoodAllocator<double*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool*, 3u, itk::NeighborhoodAllocator<bool*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<short, 3u, itk::NeighborhoodAllocator<short> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<int*, 3u, itk::NeighborhoodAllocator<int*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<short*, 2u, itk::NeighborhoodAllocator<short*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool*, 2u, itk::NeighborhoodAllocator<bool*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned long, 3u, itk::NeighborhoodAllocator<unsigned long> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<signed char*, 3u, itk::NeighborhoodAllocator<signed char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long, 2u, itk::NeighborhoodAllocator<long> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool*, 1u, itk::NeighborhoodAllocator<bool*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<bool, 3u, itk::NeighborhoodAllocator<bool> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char*, 1u, itk::NeighborhoodAllocator<unsigned char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<itk::FixedArray<unsigned char, 4u>, 3u, itk::NeighborhoodAllocator<itk::FixedArray<unsigned char, 4u> > >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned short, 3u, itk::NeighborhoodAllocator<unsigned short> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long*, 3u, itk::NeighborhoodAllocator<long*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float*, 4u, itk::NeighborhoodAllocator<float*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char*, 2u, itk::NeighborhoodAllocator<unsigned char*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<long*, 2u, itk::NeighborhoodAllocator<long*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned int, 3u, itk::NeighborhoodAllocator<unsigned int> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double, 3u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<unsigned char, 1u, itk::NeighborhoodAllocator<unsigned char> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<short*, 3u, itk::NeighborhoodAllocator<short*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<float, 4u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<short, 2u, itk::NeighborhoodAllocator<short> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<double*, 3u, itk::NeighborhoodAllocator<double*> >;
extern template class ITKCommon_EXPORT itk::Neighborhood<int, 2u, itk::NeighborhoodAllocator<int> >;
#endif //itkNeighborhoodExplicit_h
