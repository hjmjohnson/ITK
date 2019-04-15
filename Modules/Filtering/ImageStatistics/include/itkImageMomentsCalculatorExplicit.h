#ifndef itkImageMomentsCalculatorExplicit_h
#define itkImageMomentsCalculatorExplicit_h

#include "ITKImageStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<unsigned char, 3u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<unsigned char, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<float, 2u> >; //Instantiated 36 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<short, 3u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<double, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<float, 3u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<double, 4u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageMomentsCalculator<itk::Image<float, 4u> >; //Instantiated 9 times
#endif //itkImageMomentsCalculatorExplicit_h
