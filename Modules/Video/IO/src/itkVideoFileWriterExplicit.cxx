#include "itkVideoFileWriter.h"

template class ITKVideoIO_EXPORT itk::VideoFileWriter<itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 9 times
template class ITKVideoIO_EXPORT itk::VideoFileWriter<itk::VideoStream<itk::Image<itk::RGBPixel<unsigned char>, 2u> > >; //Instantiated 3 times
