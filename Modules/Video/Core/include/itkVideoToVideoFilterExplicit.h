#ifndef itkVideoToVideoFilterExplicit_h
#define itkVideoToVideoFilterExplicit_h

#include "ITKVideoCoreExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VideoToVideoFilter<itk::VideoStream<itk::Image<unsigned char, 2u> >, itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 8 times
#endif //itkVideoToVideoFilterExplicit_h
