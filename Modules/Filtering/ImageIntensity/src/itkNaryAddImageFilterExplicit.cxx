#include "itkNaryAddImageFilter.h"

template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 8 times
template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
