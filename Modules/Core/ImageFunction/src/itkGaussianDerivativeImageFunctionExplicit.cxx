#include "itkGaussianDerivativeImageFunction.h"

template class itk::GaussianDerivativeImageFunction<itk::Image<double, 2u>, double>; //Instantiated 3 times
template class itk::GaussianDerivativeImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
template class itk::GaussianDerivativeImageFunction<itk::Image<float, 2u>, double>; //Instantiated 3 times
