#ifndef itkHistogramImageToImageMetricExplicit_h
#define itkHistogramImageToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 18 times
extern template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
#endif //itkHistogramImageToImageMetricExplicit_h
