#ifndef itkBilateralImageFilterExplicit_h
#define itkBilateralImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BilateralImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BilateralImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
#endif //itkBilateralImageFilterExplicit_h
