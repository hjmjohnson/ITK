#ifndef itkSmoothingRecursiveGaussianImageFilterExplicit_h
#define itkSmoothingRecursiveGaussianImageFilterExplicit_h

#include "ITKSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SmoothingRecursiveGaussianImageFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> >; //Instantiated 6 times
#endif //itkSmoothingRecursiveGaussianImageFilterExplicit_h
