#include "itkSigmoidImageFilter.h"

template class itk::SigmoidImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 30 times
template class itk::SigmoidImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 10 times
