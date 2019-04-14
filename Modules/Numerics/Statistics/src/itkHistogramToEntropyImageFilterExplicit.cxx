#include "itkHistogramToEntropyImageFilter.h"

template class itk::HistogramToEntropyImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<double, 3u> >; //Instantiated 4 times
