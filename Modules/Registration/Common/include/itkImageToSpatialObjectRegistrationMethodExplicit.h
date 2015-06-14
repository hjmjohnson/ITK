#ifndef itkImageToSpatialObjectRegistrationMethodExplicit_h
#define itkImageToSpatialObjectRegistrationMethodExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkGroupSpatialObject.h"

extern template class ITKRegistrationCommon_EXPORT itk::ImageToSpatialObjectRegistrationMethod<itk::Image<float, 2u>, itk::GroupSpatialObject<2u> >; //Instantiated 6 times
#endif //itkImageToSpatialObjectRegistrationMethodExplicit_h
