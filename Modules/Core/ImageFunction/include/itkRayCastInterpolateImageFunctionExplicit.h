#ifndef itkRayCastInterpolateImageFunctionExplicit_h
#define itkRayCastInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::RayCastInterpolateImageFunction<itk::Image<unsigned char, 3u>, double>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::RayCastInterpolateImageFunction<itk::Image<short, 3u>, double>; //Instantiated 3 times
#endif //itkRayCastInterpolateImageFunctionExplicit_h
