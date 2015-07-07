#ifndef itkMetaImageConverterExplicit_h
#define itkMetaImageConverterExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkImageMaskSpatialObject.h"

extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageSpatialObject<3u, unsigned char> >; //Instantiated 24 times
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageMaskSpatialObject<2u> >; //Instantiated 54 times
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned char, itk::ImageMaskSpatialObject<3u> >; //Instantiated 36 times
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, unsigned short, itk::ImageSpatialObject<3u, unsigned short> >; //Instantiated 6 times
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<2u, unsigned char, itk::ImageSpatialObject<2u, unsigned char> >; //Instantiated 54 times
extern template class ITKSpatialObjects_EXPORT itk::MetaImageConverter<3u, float, itk::ImageSpatialObject<3u, float> >; //Instantiated 6 times
#endif //itkMetaImageConverterExplicit_h
