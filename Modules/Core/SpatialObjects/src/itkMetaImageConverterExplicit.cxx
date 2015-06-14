#include "itkMetaImageConverter.h"

template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageSpatialObject<2u, unsigned char> >;
template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageMaskSpatialObject<2u> >;
template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageSpatialObject<3u, unsigned char> >;
template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageMaskSpatialObject<3u> >;
template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned short, itk::ImageSpatialObject<3u, unsigned short> >;
template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, float, itk::ImageSpatialObject<3u, float> >;
