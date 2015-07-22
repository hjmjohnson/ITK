#include "itkImageGaussianModelEstimator.h"

template class ITKClassifiers_EXPORT itk::ImageGaussianModelEstimator<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<double, 2u> >, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
template class ITKClassifiers_EXPORT itk::ImageGaussianModelEstimator<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<unsigned short, 1u> >, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
