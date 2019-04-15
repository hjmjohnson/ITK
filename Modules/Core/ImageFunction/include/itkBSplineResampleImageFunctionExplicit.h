#ifndef itkBSplineResampleImageFunctionExplicit_h
#define itkBSplineResampleImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineResampleImageFunction<itk::Image<double, 2u>, double>; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineResampleImageFunction<itk::Image<double, 3u>, double>; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineResampleImageFunction<itk::Image<float, 2u>, double>; //Instantiated 4 times
#endif //itkBSplineResampleImageFunctionExplicit_h
