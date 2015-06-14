#ifndef itkGaussianDerivativeImageFunctionExplicit_h
#define itkGaussianDerivativeImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::GaussianDerivativeImageFunction<itk::Image<double, 2u>, double>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::GaussianDerivativeImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::GaussianDerivativeImageFunction<itk::Image<float, 2u>, double>; //Instantiated 3 times
#endif //itkGaussianDerivativeImageFunctionExplicit_h
