#include "itkMaximumImageFilter.h"

template class ITKImageIntensity_EXPORT itk::MaximumImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
template class ITKImageIntensity_EXPORT itk::MaximumImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
template class ITKImageIntensity_EXPORT itk::MaximumImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
template class ITKImageIntensity_EXPORT itk::MaximumImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
