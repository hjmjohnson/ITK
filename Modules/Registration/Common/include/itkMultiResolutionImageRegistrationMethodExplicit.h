#ifndef itkMultiResolutionImageRegistrationMethodExplicit_h
#define itkMultiResolutionImageRegistrationMethodExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkMultiResolutionImageRegistrationMethodExplicit_h
