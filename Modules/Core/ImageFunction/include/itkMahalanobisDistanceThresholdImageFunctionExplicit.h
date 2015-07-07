#ifndef itkMahalanobisDistanceThresholdImageFunctionExplicit_h
#define itkMahalanobisDistanceThresholdImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::MahalanobisDistanceThresholdImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 3u>, float>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::MahalanobisDistanceThresholdImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, float>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::MahalanobisDistanceThresholdImageFunction<itk::VectorImage<unsigned char, 2u>, float>; //Instantiated 3 times
#endif //itkMahalanobisDistanceThresholdImageFunctionExplicit_h
