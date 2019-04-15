#ifndef itkMaximumImageFilterExplicit_h
#define itkMaximumImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
#endif //itkMaximumImageFilterExplicit_h
