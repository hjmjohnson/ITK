#ifndef itkVideoFileWriterExplicit_h
#define itkVideoFileWriterExplicit_h

#include "ITKVideoIOExport.h"

#include "itkVideoStream.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VideoFileWriter<itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VideoFileWriter<itk::VideoStream<itk::Image<itk::RGBPixel<unsigned char>, 2u> > >; //Instantiated 3 times
#endif //itkVideoFileWriterExplicit_h
