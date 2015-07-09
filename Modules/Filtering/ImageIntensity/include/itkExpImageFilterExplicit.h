#ifndef itkExpImageFilterExplicit_h
#define itkExpImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

extern template class ITKImageIntensity_EXPORT itk::ExpImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 16 times
extern template class ITKImageIntensity_EXPORT itk::ExpImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 16 times
#endif //itkExpImageFilterExplicit_h
