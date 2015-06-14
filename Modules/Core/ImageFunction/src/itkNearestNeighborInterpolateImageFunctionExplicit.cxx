#include "itkNearestNeighborInterpolateImageFunction.h"

template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, double>; //Instantiated 10 times
template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 70 times
template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned short, 3u>, double>; //Instantiated 12 times
template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, float>; //Instantiated 4 times
template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 3u>, double>; //Instantiated 40 times
template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 3u>, double>; //Instantiated 4 times
