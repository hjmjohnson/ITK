#ifndef itkMeanSquaresImageToImageMetricExplicit_h
#define itkMeanSquaresImageToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 42 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<int, 2u>, itk::Image<int, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<short, 2u>, itk::Image<short, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MeanSquaresImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
#endif //itkMeanSquaresImageToImageMetricExplicit_h
