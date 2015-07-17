#ifndef itkSpatialObjectWriterExplicit_h
#define itkSpatialObjectWriterExplicit_h

#include "ITKIOSpatialObjectsExport.h"

extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 18 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, unsigned short, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >; //Instantiated 3 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 45 times
extern template class ITKIOSpatialObjects_EXPORT itk::SpatialObjectWriter<3u, float, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >; //Instantiated 6 times
#endif //itkSpatialObjectWriterExplicit_h
