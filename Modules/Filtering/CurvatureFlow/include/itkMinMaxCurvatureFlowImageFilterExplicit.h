#ifndef itkMinMaxCurvatureFlowImageFilterExplicit_h
#define itkMinMaxCurvatureFlowImageFilterExplicit_h

#include "ITKCurvatureFlowExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
#endif //itkMinMaxCurvatureFlowImageFilterExplicit_h
