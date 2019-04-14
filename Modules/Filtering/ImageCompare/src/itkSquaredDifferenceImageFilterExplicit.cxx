#include "itkSquaredDifferenceImageFilter.h"

template class itk::SquaredDifferenceImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
template class itk::SquaredDifferenceImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 9 times
