#ifndef itkOtsuThresholdCalculatorExplicit_h
#define itkOtsuThresholdCalculatorExplicit_h

#include "ITKThresholdingExport.h"

extern template class ITKThresholding_EXPORT itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, double>; //Instantiated 78 times
extern template class ITKThresholding_EXPORT itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, float>; //Instantiated 11 times
extern template class ITKThresholding_EXPORT itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, short>; //Instantiated 7 times
#endif //itkOtsuThresholdCalculatorExplicit_h
