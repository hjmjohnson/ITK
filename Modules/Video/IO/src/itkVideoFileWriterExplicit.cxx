#include "itkVideoFileWriter.h"

template class itk::VideoFileWriter<itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 9 times
template class itk::VideoFileWriter<itk::VideoStream<itk::Image<itk::RGBPixel<unsigned char>, 2u> > >; //Instantiated 3 times
