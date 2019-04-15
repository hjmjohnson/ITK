#ifndef itkMetaImageConverterExplicit_h
#define itkMetaImageConverterExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkImageSpatialObject.h"
#include "itkImageMaskSpatialObject.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<2u, unsigned char, itk::ImageSpatialObject<2u, unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<2u, unsigned char, itk::ImageMaskSpatialObject<2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<3u, unsigned char, itk::ImageSpatialObject<3u, unsigned char> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<3u, unsigned char, itk::ImageMaskSpatialObject<3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<3u, unsigned short, itk::ImageSpatialObject<3u, unsigned short> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MetaImageConverter<3u, float, itk::ImageSpatialObject<3u, float> >;

#endif //itkMetaImageConverterExplicit_h
