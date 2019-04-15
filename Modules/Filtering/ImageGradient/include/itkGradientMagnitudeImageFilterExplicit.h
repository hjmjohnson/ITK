#ifndef itkGradientMagnitudeImageFilterExplicit_h
#define itkGradientMagnitudeImageFilterExplicit_h

#include "ITKImageGradientExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientMagnitudeImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientMagnitudeImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientMagnitudeImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 11 times
#endif //itkGradientMagnitudeImageFilterExplicit_h
