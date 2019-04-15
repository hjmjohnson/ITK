#ifndef itkMahalanobisDistanceThresholdImageFunctionExplicit_h
#define itkMahalanobisDistanceThresholdImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MahalanobisDistanceThresholdImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 3u>, float>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MahalanobisDistanceThresholdImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, float>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MahalanobisDistanceThresholdImageFunction<itk::VectorImage<unsigned char, 2u>, float>; //Instantiated 3 times
#endif //itkMahalanobisDistanceThresholdImageFunctionExplicit_h
