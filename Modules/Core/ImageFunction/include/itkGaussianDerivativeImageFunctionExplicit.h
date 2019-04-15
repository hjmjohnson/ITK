#ifndef itkGaussianDerivativeImageFunctionExplicit_h
#define itkGaussianDerivativeImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GaussianDerivativeImageFunction<itk::Image<double, 2u>, double>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GaussianDerivativeImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GaussianDerivativeImageFunction<itk::Image<float, 2u>, double>; //Instantiated 3 times
#endif //itkGaussianDerivativeImageFunctionExplicit_h
