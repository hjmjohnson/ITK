#ifndef itkAnisotropicDiffusionFunctionExplicit_h
#define itkAnisotropicDiffusionFunctionExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionFunction<itk::Image<double, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionFunction<itk::Image<float, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionFunction<itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::AnisotropicDiffusionFunction<itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkAnisotropicDiffusionFunctionExplicit_h
