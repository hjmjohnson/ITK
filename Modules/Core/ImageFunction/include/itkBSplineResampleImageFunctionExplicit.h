#ifndef itkBSplineResampleImageFunctionExplicit_h
#define itkBSplineResampleImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<double, 2u>, double>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<double, 3u>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::BSplineResampleImageFunction<itk::Image<float, 2u>, double>; //Instantiated 4 times
#endif //itkBSplineResampleImageFunctionExplicit_h
