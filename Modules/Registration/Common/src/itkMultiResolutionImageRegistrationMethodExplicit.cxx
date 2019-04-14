#include "itkMultiResolutionImageRegistrationMethod.h"

template class itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
template class itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
