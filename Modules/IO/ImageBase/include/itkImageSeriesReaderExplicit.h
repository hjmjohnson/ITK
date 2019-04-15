#ifndef itkImageSeriesReaderExplicit_h
#define itkImageSeriesReaderExplicit_h

#include "ITKIOImageBaseExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::VectorImage<unsigned short, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<itk::RGBPixel<unsigned char>, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<short, 3u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<unsigned short, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<short, 5u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<unsigned char, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<short, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageSeriesReader<itk::Image<short, 4u> >; //Instantiated 3 times
#endif //itkImageSeriesReaderExplicit_h
