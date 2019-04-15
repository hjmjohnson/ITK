#ifndef itkMutualInformationImageToImageMetricExplicit_h
#define itkMutualInformationImageToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MutualInformationImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MutualInformationImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MutualInformationImageToImageMetric<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
#endif //itkMutualInformationImageToImageMetricExplicit_h
