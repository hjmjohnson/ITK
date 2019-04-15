#ifndef itkSqrtImageFilterExplicit_h
#define itkSqrtImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SqrtImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SqrtImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SqrtImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 46 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SqrtImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 16 times
#endif //itkSqrtImageFilterExplicit_h
