#ifndef itkWindowedSincInterpolateImageFunctionExplicit_h
#define itkWindowedSincInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::WindowedSincInterpolateImageFunction<itk::Image<unsigned char, 2u>, 5u, itk::Function::HammingWindowFunction<5u, double, double>, itk::ConstantBoundaryCondition<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >, double>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::WindowedSincInterpolateImageFunction<itk::Image<unsigned char, 3u>, 2u, itk::Function::HammingWindowFunction<2u, double, double>, itk::ConstantBoundaryCondition<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >, double>; //Instantiated 3 times
#endif //itkWindowedSincInterpolateImageFunctionExplicit_h
