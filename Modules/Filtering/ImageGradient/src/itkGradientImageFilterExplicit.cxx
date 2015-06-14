#include "itkGradientImageFilter.h"

template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 2u>, float, float, itk::Image<itk::CovariantVector<float, 2u>, 2u> >; //Instantiated 33 times
template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::VectorImage<float, 3u> >; //Instantiated 7 times
template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::Image<itk::CovariantVector<float, 3u>, 3u> >; //Instantiated 13 times
