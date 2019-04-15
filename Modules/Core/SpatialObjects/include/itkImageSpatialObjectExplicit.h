#ifndef itkImageSpatialObjectExplicit_h
#define itkImageSpatialObjectExplicit_h

#include "ITKSpatialObjectsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSpatialObject<2u, unsigned char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSpatialObject<3u, unsigned char>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSpatialObject<3u, unsigned short>;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSpatialObject<3u, float>;

#endif //itkImageSpatialObjectExplicit_h
