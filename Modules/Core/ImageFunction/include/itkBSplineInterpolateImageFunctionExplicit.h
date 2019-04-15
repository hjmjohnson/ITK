#ifndef itkBSplineInterpolateImageFunctionExplicit_h
#define itkBSplineInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<double, 2u>, double, double>; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<float, 2u>, float, float>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<double, 1u>, double, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<float, 3u>, double, double>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<float, 2u>, double, double>; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<unsigned char, 2u>, double, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<float, 2u>, double, float>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<double, 3u>, double, double>; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<unsigned int, 3u>, double, double>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineInterpolateImageFunction<itk::Image<double, 4u>, double, double>; //Instantiated 3 times
#endif //itkBSplineInterpolateImageFunctionExplicit_h
