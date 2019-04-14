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
#ifndef itkConditionalConstIteratorExplicit_h
#define itkConditionalConstIteratorExplicit_h
#include "itkImage.h"
#include "itkVectorImage.h"
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<bool, 1u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned short, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned int, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned short, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<signed char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned int, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<bool, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<int, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<signed char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<short, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<signed char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<unsigned char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<bool, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<int, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<bool, 4u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<int, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<signed char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::VectorImage<short, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ConditionalConstIterator<itk::Image<short, 3u> >;
#endif //itkConditionalConstIteratorExplicit_h
