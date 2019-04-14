#include "itkMaximumProjectionImageFilter.h"

template class itk::MaximumProjectionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
template class itk::MaximumProjectionImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 7 times
template class itk::MaximumProjectionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
