#include "itkGradientMagnitudeImageFilter.h"

template class itk::GradientMagnitudeImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
template class itk::GradientMagnitudeImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 7 times
template class itk::GradientMagnitudeImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 11 times
