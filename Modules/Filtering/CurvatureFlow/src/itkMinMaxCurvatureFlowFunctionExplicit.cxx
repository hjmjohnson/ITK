#include "itkMinMaxCurvatureFlowFunction.h"

template class itk::MinMaxCurvatureFlowFunction<itk::Image<double, 3u> >; //Instantiated 6 times
template class itk::MinMaxCurvatureFlowFunction<itk::Image<float, 2u> >; //Instantiated 18 times
template class itk::MinMaxCurvatureFlowFunction<itk::Image<double, 2u> >; //Instantiated 6 times
template class itk::MinMaxCurvatureFlowFunction<itk::Image<float, 3u> >; //Instantiated 8 times
