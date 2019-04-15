#ifndef itkCannyEdgeDetectionImageFilterExplicit_h
#define itkCannyEdgeDetectionImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CannyEdgeDetectionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CannyEdgeDetectionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CannyEdgeDetectionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CannyEdgeDetectionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 12 times
#endif //itkCannyEdgeDetectionImageFilterExplicit_h
