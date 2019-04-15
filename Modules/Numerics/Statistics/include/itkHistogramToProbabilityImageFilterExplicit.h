#ifndef itkHistogramToProbabilityImageFilterExplicit_h
#define itkHistogramToProbabilityImageFilterExplicit_h

#include "ITKStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::HistogramToProbabilityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<float, 3u> >; //Instantiated 4 times
#endif //itkHistogramToProbabilityImageFilterExplicit_h
