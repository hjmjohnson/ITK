#include "itkSpatialObjectWriter.h"

template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 18 times
template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >; //Instantiated 3 times
template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 45 times
template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 6 times
