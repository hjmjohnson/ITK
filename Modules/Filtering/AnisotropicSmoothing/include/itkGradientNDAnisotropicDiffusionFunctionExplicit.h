#ifndef itkGradientNDAnisotropicDiffusionFunctionExplicit_h
#define itkGradientNDAnisotropicDiffusionFunctionExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

extern template class ITKAnisotropicSmoothing_EXPORT itk::GradientNDAnisotropicDiffusionFunction<itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::GradientNDAnisotropicDiffusionFunction<itk::Image<float, 2u> >; //Instantiated 26 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::GradientNDAnisotropicDiffusionFunction<itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::GradientNDAnisotropicDiffusionFunction<itk::Image<float, 3u> >; //Instantiated 12 times
#endif //itkGradientNDAnisotropicDiffusionFunctionExplicit_h
