#ifndef itkVideoFileWriterExplicit_h
#define itkVideoFileWriterExplicit_h

#include "ITKVideoIOExport.h"

#include "itkVideoStream.h"

extern template class ITKVideoIO_EXPORT itk::VideoFileWriter<itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 9 times
extern template class ITKVideoIO_EXPORT itk::VideoFileWriter<itk::VideoStream<itk::Image<itk::RGBPixel<unsigned char>, 2u> > >; //Instantiated 3 times
#endif //itkVideoFileWriterExplicit_h
