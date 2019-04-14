#include "itkMetaImageConverter.h"

template class itk::MetaImageConverter<2u, unsigned char, itk::ImageSpatialObject<2u, unsigned char> >;
template class itk::MetaImageConverter<2u, unsigned char, itk::ImageMaskSpatialObject<2u> >;
template class itk::MetaImageConverter<3u, unsigned char, itk::ImageSpatialObject<3u, unsigned char> >;
template class itk::MetaImageConverter<3u, unsigned char, itk::ImageMaskSpatialObject<3u> >;
template class itk::MetaImageConverter<3u, unsigned short, itk::ImageSpatialObject<3u, unsigned short> >;
template class itk::MetaImageConverter<3u, float, itk::ImageSpatialObject<3u, float> >;
