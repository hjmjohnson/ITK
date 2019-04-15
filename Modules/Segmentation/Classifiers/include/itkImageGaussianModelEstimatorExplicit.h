#ifndef itkImageGaussianModelEstimatorExplicit_h
#define itkImageGaussianModelEstimatorExplicit_h

#include "ITKClassifiersExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageGaussianModelEstimator<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<double, 2u> >, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageGaussianModelEstimator<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<unsigned short, 1u> >, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
#endif //itkImageGaussianModelEstimatorExplicit_h
