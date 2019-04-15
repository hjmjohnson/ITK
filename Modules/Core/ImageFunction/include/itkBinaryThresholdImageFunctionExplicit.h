#ifndef itkBinaryThresholdImageFunctionExplicit_h
#define itkBinaryThresholdImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryThresholdImageFunction<itk::Image<float, 2u>, float>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryThresholdImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryThresholdImageFunction<itk::Image<float, 2u>, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryThresholdImageFunction<itk::Image<unsigned char, 2u>, float>; //Instantiated 10 times
#endif //itkBinaryThresholdImageFunctionExplicit_h
