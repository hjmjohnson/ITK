#ifndef itkSigmoidImageFilterExplicit_h
#define itkSigmoidImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SigmoidImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 30 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SigmoidImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 10 times
#endif //itkSigmoidImageFilterExplicit_h
