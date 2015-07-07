#ifndef itkMetaMeshConverterExplicit_h
#define itkMetaMeshConverterExplicit_h

#include "ITKSpatialObjectsExport.h"

extern template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 6 times
extern template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 54 times
extern template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 24 times
extern template class ITKSpatialObjects_EXPORT itk::MetaMeshConverter<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >; //Instantiated 6 times
#endif //itkMetaMeshConverterExplicit_h
