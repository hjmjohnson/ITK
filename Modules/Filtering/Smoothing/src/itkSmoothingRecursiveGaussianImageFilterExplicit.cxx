#include "itkSmoothingRecursiveGaussianImageFilter.h"

template class itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 15 times
template class itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 9 times
template class itk::SmoothingRecursiveGaussianImageFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> >; //Instantiated 6 times
