#ifndef itkVectorResampleImageFilterExplicit_h
#define itkVectorResampleImageFilterExplicit_h

#include "ITKImageGridExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, double>; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u>, double>; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u>, double>; //Instantiated 21 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 3u>, double>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u>, double>; //Instantiated 39 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 4u>, double>; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorResampleImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, double>; //Instantiated 48 times
#endif //itkVectorResampleImageFilterExplicit_h
