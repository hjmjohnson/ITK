#ifndef itkNearestNeighborExtrapolateImageFunctionExplicit_h
#define itkNearestNeighborExtrapolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::NearestNeighborExtrapolateImageFunction<itk::Image<double, 2u>, double>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::NearestNeighborExtrapolateImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 4 times
#endif //itkNearestNeighborExtrapolateImageFunctionExplicit_h
