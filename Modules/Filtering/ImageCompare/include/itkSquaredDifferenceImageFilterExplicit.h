#ifndef itkSquaredDifferenceImageFilterExplicit_h
#define itkSquaredDifferenceImageFilterExplicit_h

#include "ITKImageCompareExport.h"

extern template class ITKImageCompare_EXPORT itk::SquaredDifferenceImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
extern template class ITKImageCompare_EXPORT itk::SquaredDifferenceImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 9 times
#endif //itkSquaredDifferenceImageFilterExplicit_h
