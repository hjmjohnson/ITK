#ifndef itkSquaredDifferenceImageFilterExplicit_h
#define itkSquaredDifferenceImageFilterExplicit_h

#include "ITKImageCompareExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SquaredDifferenceImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SquaredDifferenceImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 9 times
#endif //itkSquaredDifferenceImageFilterExplicit_h
