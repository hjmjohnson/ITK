#ifndef itkNearestNeighborInterpolateImageFunctionExplicit_h
#define itkNearestNeighborInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, double>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 70 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned short, 3u>, double>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<unsigned char, 3u>, double>; //Instantiated 40 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborInterpolateImageFunction<itk::Image<float, 3u>, double>; //Instantiated 4 times
#endif //itkNearestNeighborInterpolateImageFunctionExplicit_h
