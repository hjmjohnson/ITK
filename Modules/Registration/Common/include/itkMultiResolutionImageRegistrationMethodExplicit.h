#ifndef itkMultiResolutionImageRegistrationMethodExplicit_h
#define itkMultiResolutionImageRegistrationMethodExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
extern template class ITKRegistrationCommon_EXPORT itk::MultiResolutionImageRegistrationMethod<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkMultiResolutionImageRegistrationMethodExplicit_h
