#ifndef itkMetaMeshConverterExplicit_h
#define itkMetaMeshConverterExplicit_h

#include "ITKSpatialObjectsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaMeshConverter<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaMeshConverter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaMeshConverter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaMeshConverter<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >;

#endif //itkMetaMeshConverterExplicit_h
