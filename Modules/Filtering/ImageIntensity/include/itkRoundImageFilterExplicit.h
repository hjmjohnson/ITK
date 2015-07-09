#ifndef itkRoundImageFilterExplicit_h
#define itkRoundImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

extern template class ITKImageIntensity_EXPORT itk::RoundImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 10 times
extern template class ITKImageIntensity_EXPORT itk::RoundImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
#endif //itkRoundImageFilterExplicit_h
