#ifndef itkNaryAddImageFilterExplicit_h
#define itkNaryAddImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

extern template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 8 times
extern template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::NaryAddImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
#endif //itkNaryAddImageFilterExplicit_h
