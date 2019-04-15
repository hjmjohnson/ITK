#ifndef itkLaplacianSharpeningImageFilterExplicit_h
#define itkLaplacianSharpeningImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianSharpeningImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianSharpeningImageFilter<itk::Image<float, 4u>, itk::Image<float, 4u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianSharpeningImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 9 times
#endif //itkLaplacianSharpeningImageFilterExplicit_h
