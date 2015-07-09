#ifndef itkPermuteAxesImageFilterExplicit_h
#define itkPermuteAxesImageFilterExplicit_h

#include "ITKImageGridExport.h"

extern template class ITKImageGrid_EXPORT itk::PermuteAxesImageFilter<itk::Image<float, 2u> >; //Instantiated 9 times
extern template class ITKImageGrid_EXPORT itk::PermuteAxesImageFilter<itk::Image<short, 3u> >; //Instantiated 15 times
extern template class ITKImageGrid_EXPORT itk::PermuteAxesImageFilter<itk::Image<float, 3u> >; //Instantiated 12 times
#endif //itkPermuteAxesImageFilterExplicit_h
