#include "itkOtsuThresholdImageFilter.h"

template class ITKThresholding_EXPORT itk::OtsuThresholdImageFilter<itk::Image<float, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
template class ITKThresholding_EXPORT itk::OtsuThresholdImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 7 times
template class ITKThresholding_EXPORT itk::OtsuThresholdImageFilter<itk::Image<float, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 8 times
