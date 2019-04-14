#include "itkScalarImageKmeansImageFilter.h"

template class itk::ScalarImageKmeansImageFilter<itk::Image<short, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
template class itk::ScalarImageKmeansImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
template class itk::ScalarImageKmeansImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
