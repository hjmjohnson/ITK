#ifndef itkMaximumProjectionImageFilterExplicit_h
#define itkMaximumProjectionImageFilterExplicit_h

#include "ITKImageStatisticsExport.h"

extern template class ITKImageStatistics_EXPORT itk::MaximumProjectionImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
extern template class ITKImageStatistics_EXPORT itk::MaximumProjectionImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 7 times
extern template class ITKImageStatistics_EXPORT itk::MaximumProjectionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
#endif //itkMaximumProjectionImageFilterExplicit_h
