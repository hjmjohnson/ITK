#include "itkHistogramToIntensityImageFilter.h"

template class ITKStatistics_EXPORT itk::HistogramToIntensityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<unsigned long, 3u> >; //Instantiated 4 times
