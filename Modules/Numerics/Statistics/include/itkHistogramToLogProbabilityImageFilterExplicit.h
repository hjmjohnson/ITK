#ifndef itkHistogramToLogProbabilityImageFilterExplicit_h
#define itkHistogramToLogProbabilityImageFilterExplicit_h

#include "ITKStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::HistogramToLogProbabilityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<double, 3u> >; //Instantiated 4 times
#endif //itkHistogramToLogProbabilityImageFilterExplicit_h
