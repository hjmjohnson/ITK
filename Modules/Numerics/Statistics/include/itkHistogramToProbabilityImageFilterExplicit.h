#ifndef itkHistogramToProbabilityImageFilterExplicit_h
#define itkHistogramToProbabilityImageFilterExplicit_h

#include "ITKStatisticsExport.h"

extern template class ITKStatistics_EXPORT itk::HistogramToProbabilityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<float, 3u> >; //Instantiated 4 times
#endif //itkHistogramToProbabilityImageFilterExplicit_h
