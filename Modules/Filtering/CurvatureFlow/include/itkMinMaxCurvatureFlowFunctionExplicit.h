#ifndef itkMinMaxCurvatureFlowFunctionExplicit_h
#define itkMinMaxCurvatureFlowFunctionExplicit_h

#include "ITKCurvatureFlowExport.h"

extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowFunction<itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowFunction<itk::Image<float, 2u> >; //Instantiated 18 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowFunction<itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowFunction<itk::Image<float, 3u> >; //Instantiated 8 times
#endif //itkMinMaxCurvatureFlowFunctionExplicit_h
