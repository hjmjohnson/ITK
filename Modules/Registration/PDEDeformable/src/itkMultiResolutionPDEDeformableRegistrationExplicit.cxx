#include "itkMultiResolutionPDEDeformableRegistration.h"

template class ITKPDEDeformableRegistration_EXPORT itk::MultiResolutionPDEDeformableRegistration<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, float>; //Instantiated 45 times
template class ITKPDEDeformableRegistration_EXPORT itk::MultiResolutionPDEDeformableRegistration<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, float>; //Instantiated 9 times
