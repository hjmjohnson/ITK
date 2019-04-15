#ifndef itkHistogramToEntropyImageFilterExplicit_h
#define itkHistogramToEntropyImageFilterExplicit_h

#include "ITKStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::HistogramToEntropyImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<double, 3u> >; //Instantiated 4 times
#endif //itkHistogramToEntropyImageFilterExplicit_h
