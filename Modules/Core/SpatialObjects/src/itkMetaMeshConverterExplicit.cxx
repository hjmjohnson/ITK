#include "itkMetaMeshConverter.h"

template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >;
template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >;
template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >;
template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >;
