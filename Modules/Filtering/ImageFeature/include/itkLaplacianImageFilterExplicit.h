#ifndef itkLaplacianImageFilterExplicit_h
#define itkLaplacianImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 11 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 17 times
#endif //itkLaplacianImageFilterExplicit_h
