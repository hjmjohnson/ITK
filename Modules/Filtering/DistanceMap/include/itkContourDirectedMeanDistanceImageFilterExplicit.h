#ifndef itkContourDirectedMeanDistanceImageFilterExplicit_h
#define itkContourDirectedMeanDistanceImageFilterExplicit_h

#include "ITKDistanceMapExport.h"

extern template class ITKDistanceMap_EXPORT itk::ContourDirectedMeanDistanceImageFilter<itk::Image<float, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 6 times
extern template class ITKDistanceMap_EXPORT itk::ContourDirectedMeanDistanceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
#endif //itkContourDirectedMeanDistanceImageFilterExplicit_h
