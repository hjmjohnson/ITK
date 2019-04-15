#ifndef itkOtsuThresholdCalculatorExplicit_h
#define itkOtsuThresholdCalculatorExplicit_h

#include "ITKThresholdingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, double>; //Instantiated 78 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, float>; //Instantiated 11 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::OtsuThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, short>; //Instantiated 7 times
#endif //itkOtsuThresholdCalculatorExplicit_h
