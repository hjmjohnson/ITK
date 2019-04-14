#include "itkBSplineResampleImageFunction.h"

template class itk::BSplineResampleImageFunction<itk::Image<double, 2u>, double>; //Instantiated 4 times
template class itk::BSplineResampleImageFunction<itk::Image<double, 3u>, double>; //Instantiated 8 times
template class itk::BSplineResampleImageFunction<itk::Image<float, 2u>, double>; //Instantiated 4 times
