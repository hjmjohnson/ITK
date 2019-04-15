#ifndef itkGradientAnisotropicDiffusionImageFilterExplicit_h
#define itkGradientAnisotropicDiffusionImageFilterExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientAnisotropicDiffusionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 26 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientAnisotropicDiffusionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientAnisotropicDiffusionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientAnisotropicDiffusionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
#endif //itkGradientAnisotropicDiffusionImageFilterExplicit_h
