#ifndef itkHistogramToIntensityImageFilterExplicit_h
#define itkHistogramToIntensityImageFilterExplicit_h

#include "ITKStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::HistogramToIntensityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<unsigned long, 3u> >; //Instantiated 4 times
#endif //itkHistogramToIntensityImageFilterExplicit_h
