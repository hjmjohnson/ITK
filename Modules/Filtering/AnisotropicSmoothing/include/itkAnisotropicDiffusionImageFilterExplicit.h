#ifndef itkAnisotropicDiffusionImageFilterExplicit_h
#define itkAnisotropicDiffusionImageFilterExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 43 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
#endif //itkAnisotropicDiffusionImageFilterExplicit_h
