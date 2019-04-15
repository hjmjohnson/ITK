#ifndef itkMultiResolutionPDEDeformableRegistrationExplicit_h
#define itkMultiResolutionPDEDeformableRegistrationExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MultiResolutionPDEDeformableRegistration<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, float>; //Instantiated 45 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MultiResolutionPDEDeformableRegistration<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, float>; //Instantiated 9 times
#endif //itkMultiResolutionPDEDeformableRegistrationExplicit_h
