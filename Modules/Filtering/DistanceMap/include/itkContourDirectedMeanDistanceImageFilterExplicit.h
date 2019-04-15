#ifndef itkContourDirectedMeanDistanceImageFilterExplicit_h
#define itkContourDirectedMeanDistanceImageFilterExplicit_h

#include "ITKDistanceMapExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ContourDirectedMeanDistanceImageFilter<itk::Image<float, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ContourDirectedMeanDistanceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
#endif //itkContourDirectedMeanDistanceImageFilterExplicit_h
