#ifndef itkGradientImageFilterExplicit_h
#define itkGradientImageFilterExplicit_h

#include "ITKImageGradientExport.h"

extern template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 2u>, float, float, itk::Image<itk::CovariantVector<float, 2u>, 2u> >; //Instantiated 33 times
extern template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::VectorImage<float, 3u> >; //Instantiated 7 times
extern template class ITKImageGradient_EXPORT itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::Image<itk::CovariantVector<float, 3u>, 3u> >; //Instantiated 13 times
#endif //itkGradientImageFilterExplicit_h
