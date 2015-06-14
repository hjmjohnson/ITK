#ifndef itkImageModelEstimatorBaseExplicit_h
#define itkImageModelEstimatorBaseExplicit_h

#include "ITKClassifiersExport.h"

#include "itkMahalanobisDistanceThresholdImageFunction.h"

extern template class ITKClassifiers_EXPORT itk::ImageModelEstimatorBase<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<double, 2u> > >; //Instantiated 6 times
extern template class ITKClassifiers_EXPORT itk::ImageModelEstimatorBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Statistics::MahalanobisDistanceMembershipFunction<itk::Vector<unsigned short, 1u> > >; //Instantiated 6 times
#endif //itkImageModelEstimatorBaseExplicit_h
