#ifndef itkXorImageFilterExplicit_h
#define itkXorImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::XorImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::XorImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 7 times
#endif //itkXorImageFilterExplicit_h
