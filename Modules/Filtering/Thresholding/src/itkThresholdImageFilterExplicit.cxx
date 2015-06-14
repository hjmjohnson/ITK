#include "itkThresholdImageFilter.h"

template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<float, 2u> >; //Instantiated 9 times
template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<float, 3u> >; //Instantiated 9 times
template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<short, 3u> >; //Instantiated 14 times
template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<unsigned char, 3u> >; //Instantiated 15 times
template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<double, 2u> >; //Instantiated 24 times
template class ITKThresholding_EXPORT itk::ThresholdImageFilter<itk::Image<double, 3u> >; //Instantiated 12 times
