#ifndef itkAnisotropicDiffusionImageFilterExplicit_h
#define itkAnisotropicDiffusionImageFilterExplicit_h

#include "ITKAnisotropicSmoothingExport.h"

extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 43 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
extern template class ITKAnisotropicSmoothing_EXPORT itk::AnisotropicDiffusionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
#endif //itkAnisotropicDiffusionImageFilterExplicit_h
