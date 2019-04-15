#ifndef itkGradientImageFilterExplicit_h
#define itkGradientImageFilterExplicit_h

#include "ITKImageGradientExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientImageFilter<itk::Image<float, 2u>, float, float, itk::Image<itk::CovariantVector<float, 2u>, 2u> >; //Instantiated 33 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::VectorImage<float, 3u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientImageFilter<itk::Image<float, 3u>, float, float, itk::Image<itk::CovariantVector<float, 3u>, 3u> >; //Instantiated 13 times
#endif //itkGradientImageFilterExplicit_h
