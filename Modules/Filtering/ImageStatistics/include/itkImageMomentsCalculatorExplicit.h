#ifndef itkImageMomentsCalculatorExplicit_h
#define itkImageMomentsCalculatorExplicit_h

#include "ITKImageStatisticsExport.h"

extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<unsigned char, 3u> >; //Instantiated 27 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<unsigned char, 2u> >; //Instantiated 6 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<float, 2u> >; //Instantiated 36 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<double, 3u> >; //Instantiated 9 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<short, 3u> >; //Instantiated 24 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<double, 2u> >; //Instantiated 9 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<float, 3u> >; //Instantiated 27 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<double, 4u> >; //Instantiated 6 times
extern template class ITKImageStatistics_EXPORT itk::ImageMomentsCalculator<itk::Image<float, 4u> >; //Instantiated 9 times
#endif //itkImageMomentsCalculatorExplicit_h
