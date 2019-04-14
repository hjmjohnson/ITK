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
#ifndef itkMetaDataObjectExplicit_h
#define itkMetaDataObjectExplicit_h

#include "itkArray.h"
#include "itkMatrix.h"
#include <vector>
//subs std:: std::
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<unsigned long>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<float>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<unsigned short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<itk::Array<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<bool>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<itk::Array<char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<itk::Array<int> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<unsigned int>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<itk::Array<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<double>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<unsigned char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaDataObject<long>;
#endif //itkMetaDataObjectExplicit_h
