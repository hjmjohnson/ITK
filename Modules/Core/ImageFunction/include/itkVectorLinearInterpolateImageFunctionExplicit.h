#ifndef itkVectorLinearInterpolateImageFunctionExplicit_h
#define itkVectorLinearInterpolateImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, double>; //Instantiated 30 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 3u>, 3u>, double>; //Instantiated 46 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 2u>, 3u>, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 2u>, 2u>, double>; //Instantiated 62 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::FixedArray<float, 3u>, 3u>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<double, 3u>, 4u>, double>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, double>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::FixedArray<float, 2u>, 2u>, double>; //Instantiated 40 times
extern template class ITKImageFunction_EXPORT itk::VectorLinearInterpolateImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, float>; //Instantiated 10 times
#endif //itkVectorLinearInterpolateImageFunctionExplicit_h
