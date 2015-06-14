#include "itkHistogramImageToImageMetric.h"

template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 18 times
template class ITKRegistrationCommon_EXPORT itk::HistogramImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
