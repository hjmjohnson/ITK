#ifndef itkMaximumProjectionImageFilterExplicit_h
#define itkMaximumProjectionImageFilterExplicit_h

#include "ITKImageStatisticsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumProjectionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumProjectionImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MaximumProjectionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
#endif //itkMaximumProjectionImageFilterExplicit_h
