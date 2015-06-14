#ifndef itkZeroCrossingImageFilterExplicit_h
#define itkZeroCrossingImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

extern template class ITKImageFeature_EXPORT itk::ZeroCrossingImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 34 times
extern template class ITKImageFeature_EXPORT itk::ZeroCrossingImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 72 times
extern template class ITKImageFeature_EXPORT itk::ZeroCrossingImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 13 times
extern template class ITKImageFeature_EXPORT itk::ZeroCrossingImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 17 times
#endif //itkZeroCrossingImageFilterExplicit_h
