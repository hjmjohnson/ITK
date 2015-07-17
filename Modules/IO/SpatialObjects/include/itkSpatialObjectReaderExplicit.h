#ifndef itkSpatialObjectReaderExplicit_h
#define itkSpatialObjectReaderExplicit_h

#include "ITKIOSpatialObjectsExport.h"

extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectReader<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 51 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectReader<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 6 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectReader<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 24 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectReader<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >; //Instantiated 3 times
#endif //itkSpatialObjectReaderExplicit_h
