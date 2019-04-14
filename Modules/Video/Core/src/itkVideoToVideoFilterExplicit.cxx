#include "itkVideoToVideoFilter.h"

template class itk::VideoToVideoFilter<itk::VideoStream<itk::Image<unsigned char, 2u> >, itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 8 times
