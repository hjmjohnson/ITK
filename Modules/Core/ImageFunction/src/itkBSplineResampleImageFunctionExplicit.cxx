#include "itkBSplineResampleImageFunction.h"

template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<double, 2u>, double>; //Instantiated 4 times
template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<double, 3u>, double>; //Instantiated 8 times
template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<float, 2u>, double>; //Instantiated 4 times
