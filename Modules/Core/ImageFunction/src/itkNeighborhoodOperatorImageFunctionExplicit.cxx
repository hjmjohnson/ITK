#include "itkNeighborhoodOperatorImageFunction.h"

template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, double>; //Instantiated 9 times
template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<double, 2u>, double>; //Instantiated 9 times
template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 3u>, float>; //Instantiated 6 times
template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, float>; //Instantiated 6 times
