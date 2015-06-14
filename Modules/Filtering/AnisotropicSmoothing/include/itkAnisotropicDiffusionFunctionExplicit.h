#ifndef itkAnisotropicDiffusionFunctionExplicit_h
#define itkAnisotropicDiffusionFunctionExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionFunction<itk::Image<double, 2u> >; //Instantiated 9 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionFunction<itk::Image<float, 3u> >; //Instantiated 9 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionFunction<itk::Image<double, 3u> >; //Instantiated 9 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionFunction<itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkAnisotropicDiffusionFunctionExplicit_h
