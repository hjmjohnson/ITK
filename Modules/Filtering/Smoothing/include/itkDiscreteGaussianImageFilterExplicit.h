#ifndef itkDiscreteGaussianImageFilterExplicit_h
#define itkDiscreteGaussianImageFilterExplicit_h

#include "ITKSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<float, 4u>, itk::Image<float, 4u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 44 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 98 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<short, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 113 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DiscreteGaussianImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 67 times
#endif //itkDiscreteGaussianImageFilterExplicit_h
