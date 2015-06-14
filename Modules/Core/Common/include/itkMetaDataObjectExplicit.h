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
extern template class ITKCommon_EXPORT itk::MetaDataObject<unsigned long>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<float>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<unsigned short>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<itk::Array<double> >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<char>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > > >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<bool>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<short>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<itk::Array<char> >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<int>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<itk::Array<int> >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<unsigned int>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<itk::Array<float> >;
extern template class ITKCommon_EXPORT itk::MetaDataObject<double>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<unsigned char>;
extern template class ITKCommon_EXPORT itk::MetaDataObject<long>;
#endif //itkMetaDataObjectExplicit_h
