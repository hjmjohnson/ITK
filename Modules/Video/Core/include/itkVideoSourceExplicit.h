#ifndef itkVideoSourceExplicit_h
#define itkVideoSourceExplicit_h

#include "ITKVideoCoreExport.h"

extern template class ITKVideoCore_EXPORT itk::VideoSource<itk::VideoStream<itk::Image<unsigned char, 2u> > >; //Instantiated 10 times
#endif //itkVideoSourceExplicit_h
