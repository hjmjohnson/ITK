#ifndef itkImageSeriesWriterExplicit_h
#define itkImageSeriesWriterExplicit_h

#include "ITKIOImageBaseExport.h"

extern template class ITKIOImageBase_EXPORT itk::ImageSeriesWriter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 2u> >; //Instantiated 9 times
extern template class ITKIOImageBase_EXPORT itk::ImageSeriesWriter<itk::Image<short, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
extern template class ITKIOImageBase_EXPORT itk::ImageSeriesWriter<itk::Image<short, 3u>, itk::Image<short, 2u> >; //Instantiated 9 times
extern template class ITKIOImageBase_EXPORT itk::ImageSeriesWriter<itk::Image<itk::RGBPixel<unsigned char>, 3u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 6 times
#endif //itkImageSeriesWriterExplicit_h
