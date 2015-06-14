#ifndef itkSqrtImageFilterExplicit_h
#define itkSqrtImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

extern template class ITKImageIntensity_EXPORT itk::SqrtImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
extern template class ITKImageIntensity_EXPORT itk::SqrtImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 24 times
extern template class ITKImageIntensity_EXPORT itk::SqrtImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 46 times
extern template class ITKImageIntensity_EXPORT itk::SqrtImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 16 times
#endif //itkSqrtImageFilterExplicit_h
