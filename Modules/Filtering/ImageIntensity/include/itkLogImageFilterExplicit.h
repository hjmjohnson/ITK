#ifndef itkLogImageFilterExplicit_h
#define itkLogImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LogImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LogImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LogImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LogImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
#endif //itkLogImageFilterExplicit_h
