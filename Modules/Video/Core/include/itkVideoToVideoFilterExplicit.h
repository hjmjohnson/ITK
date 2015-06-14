#ifndef itkVideoToVideoFilterExplicit_h
#define itkVideoToVideoFilterExplicit_h

#include "ITKVideoCoreExport.h"

extern template class ITKVideoCore_EXPORT itk::VideoToVideoFilter<itk::VideoStream<itk::Image<unsigned char, 2u> >, itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 8 times
#endif //itkVideoToVideoFilterExplicit_h
