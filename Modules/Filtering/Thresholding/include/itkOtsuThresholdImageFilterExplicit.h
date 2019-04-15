#ifndef itkOtsuThresholdImageFilterExplicit_h
#define itkOtsuThresholdImageFilterExplicit_h

#include "ITKThresholdingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdImageFilter<itk::Image<float, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdImageFilter<itk::Image<float, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 8 times
#endif //itkOtsuThresholdImageFilterExplicit_h
