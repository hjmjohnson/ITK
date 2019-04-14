#include "itkLaplacianImageFilter.h"

template class itk::LaplacianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 24 times
template class itk::LaplacianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 18 times
template class itk::LaplacianImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 11 times
template class itk::LaplacianImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 17 times
