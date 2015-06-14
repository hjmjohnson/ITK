#include "itkMinMaxCurvatureFlowImageFilter.h"

template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 18 times
template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
template class ITKCurvatureFlow_EXPORT itk::MinMaxCurvatureFlowImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
