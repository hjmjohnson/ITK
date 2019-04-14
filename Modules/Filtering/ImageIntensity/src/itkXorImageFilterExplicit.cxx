#include "itkXorImageFilter.h"

template class itk::XorImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 8 times
template class itk::XorImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 7 times
