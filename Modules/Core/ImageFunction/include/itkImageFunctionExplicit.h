#ifndef itkImageFunctionExplicit_h
#define itkImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

#include "itkImage.h"
#include "itkVectorImage.h"

extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Vector<double, 2u>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 1u>, 2u>, itk::Matrix<double, 1u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::FixedArray<float, 2u>, 2u>, itk::FixedArray<double, 2u>, double>; //Instantiated 40 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::FixedArray<float, 3u>, 3u>, itk::FixedArray<double, 3u>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 4u>, double, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 4u>, 2u>, itk::Matrix<double, 4u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 3u>, double, double>; //Instantiated 60 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 2u>, double, double>; //Instantiated 108 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Vector<double, 2u>, float>; //Instantiated 14 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Matrix<double, 2u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 3u>, 2u>, itk::Vector<double, 3u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, bool, float>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 3u>, float, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 5u>, 2u>, itk::Vector<double, 5u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::FixedArray<unsigned char, 4u>, 3u>, vnl_matrix<double>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::VectorImage<float, 2u>, itk::VariableLengthVector<double>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned int, 2u>, double, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<unsigned short, 3u>, 3u>, itk::Vector<double, 3u>, double>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 1u>, double, double>; //Instantiated 18 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned int, 2u>, double, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::CovariantVector<double, 2u>, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 68 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, bool, double>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<short, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned short, 2u>, double, double>; //Instantiated 26 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned int, 2u>, itk::CovariantVector<double, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, float, float>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 24 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::RGBPixel<double>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<double, 1u>, 1u>, itk::Vector<double, 1u>, double>; //Instantiated 80 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Vector<double, 3u>, double>; //Instantiated 48 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<char, 3u>, double, double>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::RGBPixel<double>, double>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, double, float>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 2u>, double, float>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 3u>, double, float>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, bool, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 6u>, 2u>, itk::Matrix<double, 6u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 3u>, itk::CovariantVector<double, 3u>, float>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Vector<double, 3u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 4u>, 2u>, itk::Vector<double, 4u>, float>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<short, 2u>, double, double>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 3u>, double, double>; //Instantiated 62 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, itk::CovariantVector<double, 2u>, float>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned int, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::CovariantVector<double, 3u>, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 36 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Vector<double, 2u>, double>; //Instantiated 32 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 82 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 6u>, 2u>, itk::Vector<double, 6u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 3u>, double, float>; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, double, double>; //Instantiated 142 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 70 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, double, double>; //Instantiated 138 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::RGBPixel<unsigned char>, 2u>, vnl_matrix<double>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, bool, float>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 1u>, double, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned short, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned short, 3u>, double, double>; //Instantiated 14 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Vector<double, 2u>, double>; //Instantiated 62 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<unsigned char, 2u>, itk::CovariantVector<double, 2u>, double>; //Instantiated 42 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 3u>, double, double>; //Instantiated 44 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 3u>, 2u>, itk::Matrix<double, 3u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<short, 3u>, double, double>; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Vector<double, 3u>, double>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, double, float>; //Instantiated 34 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, bool, double>; //Instantiated 6 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 1u>, 2u>, itk::Vector<double, 1u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<float, 5u>, 2u>, itk::Matrix<double, 5u, 2u>, float>; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<double, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 34 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<float, 2u>, itk::CovariantVector<double, 2u>, float>; //Instantiated 20 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Vector<double, 3u>, double>; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::ImageFunction<itk::Image<char, 3u>, itk::CovariantVector<double, 3u>, double>; //Instantiated 4 times
#endif //itkImageFunctionExplicit_h
