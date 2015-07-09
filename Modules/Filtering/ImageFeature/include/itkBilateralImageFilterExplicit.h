#ifndef itkBilateralImageFilterExplicit_h
#define itkBilateralImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

extern template class ITKImageFeature_EXPORT itk::BilateralImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
extern template class ITKImageFeature_EXPORT itk::BilateralImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
#endif //itkBilateralImageFilterExplicit_h
