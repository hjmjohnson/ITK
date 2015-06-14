#include "itkBinaryThresholdImageFunction.h"

template class ITKImageFunction_EXPORT itk::BinaryThresholdImageFunction<itk::Image<float, 2u>, float>; //Instantiated 6 times
template class ITKImageFunction_EXPORT itk::BinaryThresholdImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 4 times
template class ITKImageFunction_EXPORT itk::BinaryThresholdImageFunction<itk::Image<float, 2u>, double>; //Instantiated 6 times
template class ITKImageFunction_EXPORT itk::BinaryThresholdImageFunction<itk::Image<unsigned char, 2u>, float>; //Instantiated 10 times
