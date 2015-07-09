#ifndef itkLaplacianImageFilterExplicit_h
#define itkLaplacianImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

extern template class ITKImageFeature_EXPORT itk::LaplacianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 24 times
extern template class ITKImageFeature_EXPORT itk::LaplacianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 18 times
extern template class ITKImageFeature_EXPORT itk::LaplacianImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 11 times
extern template class ITKImageFeature_EXPORT itk::LaplacianImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 17 times
#endif //itkLaplacianImageFilterExplicit_h
