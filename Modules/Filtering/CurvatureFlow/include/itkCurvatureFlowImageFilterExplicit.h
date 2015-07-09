#ifndef itkCurvatureFlowImageFilterExplicit_h
#define itkCurvatureFlowImageFilterExplicit_h

#include "ITKCurvatureFlowExport.h"

extern template class ITKCurvatureFlow_EXPORT itk::CurvatureFlowImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 13 times
extern template class ITKCurvatureFlow_EXPORT itk::CurvatureFlowImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 30 times
extern template class ITKCurvatureFlow_EXPORT itk::CurvatureFlowImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
extern template class ITKCurvatureFlow_EXPORT itk::CurvatureFlowImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
#endif //itkCurvatureFlowImageFilterExplicit_h
