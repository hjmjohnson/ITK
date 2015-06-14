#ifndef itkHistogramThresholdCalculatorExplicit_h
#define itkHistogramThresholdCalculatorExplicit_h

#include "ITKThresholdingExport.h"

#include "itkDenseFrequencyContainer2.h"
#include "itkHistogram.h"

extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, int>; //Instantiated 36 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, double>; //Instantiated 111 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, unsigned short>; //Instantiated 36 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, signed char>; //Instantiated 36 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, short>; //Instantiated 84 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, float>; //Instantiated 44 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, unsigned char>; //Instantiated 38 times
extern template class ITKThresholding_EXPORT itk::HistogramThresholdCalculator<itk::Statistics::Histogram<double, itk::Statistics::DenseFrequencyContainer2>, unsigned int>; //Instantiated 36 times
#endif //itkHistogramThresholdCalculatorExplicit_h
