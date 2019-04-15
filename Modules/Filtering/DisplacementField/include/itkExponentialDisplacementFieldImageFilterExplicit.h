#ifndef itkExponentialDisplacementFieldImageFilterExplicit_h
#define itkExponentialDisplacementFieldImageFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 57 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 30 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkExponentialDisplacementFieldImageFilterExplicit_h
