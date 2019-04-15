#ifndef itkFEMSpatialObjectWriterExplicit_h
#define itkFEMSpatialObjectWriterExplicit_h

#include "ITKFEMExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FEMSpatialObjectWriter<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 45 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FEMSpatialObjectWriter<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 15 times
#endif //itkFEMSpatialObjectWriterExplicit_h
