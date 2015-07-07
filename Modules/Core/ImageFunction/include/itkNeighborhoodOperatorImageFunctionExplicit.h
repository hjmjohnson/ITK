#ifndef itkNeighborhoodOperatorImageFunctionExplicit_h
#define itkNeighborhoodOperatorImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
extern template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, double>; //Instantiated 9 times
extern template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<double, 2u>, double>; //Instantiated 9 times
extern template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 3u>, float>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, float>; //Instantiated 6 times
#endif //itkNeighborhoodOperatorImageFunctionExplicit_h
