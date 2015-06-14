#ifndef itkMetaImageConverterExplicit_h
#define itkMetaImageConverterExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkImageSpatialObject.h"
#include "itkImageMaskSpatialObject.h"

extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageSpatialObject<2u, unsigned char> >;
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageMaskSpatialObject<2u> >;
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageSpatialObject<3u, unsigned char> >;
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageMaskSpatialObject<3u> >;
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned short, itk::ImageSpatialObject<3u, unsigned short> >;
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, float, itk::ImageSpatialObject<3u, float> >;

#endif //itkMetaImageConverterExplicit_h
