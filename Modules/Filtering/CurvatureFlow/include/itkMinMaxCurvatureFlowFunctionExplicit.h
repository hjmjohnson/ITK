#ifndef itkMinMaxCurvatureFlowFunctionExplicit_h
#define itkMinMaxCurvatureFlowFunctionExplicit_h

#include "ITKCurvatureFlowExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowFunction<itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowFunction<itk::Image<float, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowFunction<itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MinMaxCurvatureFlowFunction<itk::Image<float, 3u> >; //Instantiated 8 times
#endif //itkMinMaxCurvatureFlowFunctionExplicit_h
