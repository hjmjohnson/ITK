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
#ifndef itkSimpleDataObjectDecoratorExplicit_h
#define itkSimpleDataObjectDecoratorExplicit_h
#include "itkArray.h"
#include "itkFixedArray.h"
#include "itkVector.h"
#include "itkVariableSizeMatrix.h"
#include "itkPoint.h"
#include "itkVariableLengthVector.h"
#include <complex>
//exclude Statistics::
//subs std:: std::
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<unsigned long>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<bool>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<std::vector<unsigned long, std::allocator<unsigned long> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<std::complex<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<short> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<unsigned char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<unsigned long> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Point<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<unsigned short> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<double>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Array<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::FixedArray<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<double, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<float, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::CovariantVector<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::FixedArray<double, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<int> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<std::complex<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<signed char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<unsigned int> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<long> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Array<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<signed char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<float, 1u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableLengthVector<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<float>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Array<unsigned long> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::VariableSizeMatrix<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<unsigned int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<float, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<itk::Vector<double, 1u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<unsigned short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimpleDataObjectDecorator<long>;
#endif //itkSimpleDataObjectDecoratorExplicit_h
