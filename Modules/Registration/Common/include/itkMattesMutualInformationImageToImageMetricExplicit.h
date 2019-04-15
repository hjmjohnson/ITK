#ifndef itkMattesMutualInformationImageToImageMetricExplicit_h
#define itkMattesMutualInformationImageToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MattesMutualInformationImageToImageMetric<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MattesMutualInformationImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MattesMutualInformationImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MattesMutualInformationImageToImageMetric<itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 21 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MattesMutualInformationImageToImageMetric<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 9 times
#endif //itkMattesMutualInformationImageToImageMetricExplicit_h
