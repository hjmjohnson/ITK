#include "itkOtsuThresholdCalculator.h"

template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, double>; //Instantiated 78 times
template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, float>; //Instantiated 11 times
template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, short>; //Instantiated 7 times
