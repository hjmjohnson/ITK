#ifndef itkSliceBySliceImageFilterExplicit_h
#define itkSliceBySliceImageFilterExplicit_h

#include "ITKImageGridExport.h"

extern template class ITKImageGrid_EXPORT itk::SliceBySliceImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::ImageToImageFilter<itk::Image<unsigned char, 1u>, itk::Image<unsigned char, 1u> >, itk::ImageSource<itk::Image<unsigned char, 1u> >, itk::Image<unsigned char, 1u>, itk::Image<unsigned char, 1u> >; //Instantiated 12 times
extern template class ITKImageGrid_EXPORT itk::SliceBySliceImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::ImageToImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >, itk::ImageSource<itk::Image<unsigned char, 2u> >, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
#endif //itkSliceBySliceImageFilterExplicit_h
