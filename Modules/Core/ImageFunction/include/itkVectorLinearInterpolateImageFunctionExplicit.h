#ifndef itkVectorLinearInterpolateImageFunctionExplicit_h
#define itkVectorLinearInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, double>; //Instantiated 30 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 3u>, 3u>, double>; //Instantiated 46 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 2u>, 3u>, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, float>; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 2u>, 2u>, double>; //Instantiated 62 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::FixedArray<float, 3u>, 3u>, double>; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 3u>, 4u>, double>; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, double>; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::FixedArray<float, 2u>, 2u>, double>; //Instantiated 40 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, float>; //Instantiated 10 times
#endif //itkVectorLinearInterpolateImageFunctionExplicit_h
