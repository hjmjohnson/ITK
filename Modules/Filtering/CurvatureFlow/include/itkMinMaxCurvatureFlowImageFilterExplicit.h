#ifndef itkMinMaxCurvatureFlowImageFilterExplicit_h
#define itkMinMaxCurvatureFlowImageFilterExplicit_h

#include "ITKCurvatureFlowExport.h"

extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 18 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
#endif //itkMinMaxCurvatureFlowImageFilterExplicit_h
