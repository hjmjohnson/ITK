#include "itkVectorResampleImageFilter.h"

template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, double>; //Instantiated 15 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u>, double>; //Instantiated 9 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u>, double>; //Instantiated 21 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 3u>, double>; //Instantiated 6 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u>, double>; //Instantiated 39 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 4u>, double>; //Instantiated 9 times
template class ITKImageGrid_EXPORT itk::VectorResampleImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, double>; //Instantiated 48 times
