#include "itkHistogramToProbabilityImageFilter.h"

template class itk::HistogramToProbabilityImageFilter<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, itk::Image<float, 3u> >; //Instantiated 4 times
