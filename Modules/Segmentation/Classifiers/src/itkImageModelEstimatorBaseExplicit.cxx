#include "itkImageModelEstimatorBase.h"

template class itk::ImageModelEstimatorBase<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<double, 2u> > >; //Instantiated 6 times
template class itk::ImageModelEstimatorBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<unsigned short, 1u> > >; //Instantiated 6 times
