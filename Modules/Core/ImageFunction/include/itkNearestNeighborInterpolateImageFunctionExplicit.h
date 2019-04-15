#ifndef itkNearestNeighborInterpolateImageFunctionExplicit_h
#define itkNearestNeighborInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, double>; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 70 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned short, 3u>, double>; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, float>; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 3u>, double>; //Instantiated 40 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 3u>, double>; //Instantiated 4 times
#endif //itkNearestNeighborInterpolateImageFunctionExplicit_h
