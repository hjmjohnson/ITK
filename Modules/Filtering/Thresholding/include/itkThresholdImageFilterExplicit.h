#ifndef itkThresholdImageFilterExplicit_h
#define itkThresholdImageFilterExplicit_h

#include "ITKThresholdingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<float, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<short, 3u> >; //Instantiated 14 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<unsigned char, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<double, 2u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ThresholdImageFilter<itk::Image<double, 3u> >; //Instantiated 12 times
#endif //itkThresholdImageFilterExplicit_h
