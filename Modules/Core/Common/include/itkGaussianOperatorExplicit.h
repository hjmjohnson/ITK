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
#ifndef itkGaussianOperatorExplicit_h
#define itkGaussianOperatorExplicit_h
extern template class ITKCommon_EXPORT itk::GaussianOperator<int, 3u, itk::NeighborhoodAllocator<int> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<short, 2u, itk::NeighborhoodAllocator<short> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned short, 3u, itk::NeighborhoodAllocator<unsigned short> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned int, 3u, itk::NeighborhoodAllocator<unsigned int> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned int, 2u, itk::NeighborhoodAllocator<unsigned int> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<float, 3u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<float, 2u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<double, 4u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<double, 2u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned char, 3u, itk::NeighborhoodAllocator<unsigned char> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<double, 3u, itk::NeighborhoodAllocator<double> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned short, 2u, itk::NeighborhoodAllocator<unsigned short> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<signed char, 2u, itk::NeighborhoodAllocator<signed char> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<float, 4u, itk::NeighborhoodAllocator<float> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<short, 3u, itk::NeighborhoodAllocator<short> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<int, 2u, itk::NeighborhoodAllocator<int> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<unsigned char, 2u, itk::NeighborhoodAllocator<unsigned char> >;
extern template class ITKCommon_EXPORT itk::GaussianOperator<signed char, 3u, itk::NeighborhoodAllocator<signed char> >;
#endif //itkGaussianOperatorExplicit_h
