#ifndef itkMutualInformationImageToImageMetricExplicit_h
#define itkMutualInformationImageToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::MutualInformationImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::MutualInformationImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::MutualInformationImageToImageMetric<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
#endif //itkMutualInformationImageToImageMetricExplicit_h
