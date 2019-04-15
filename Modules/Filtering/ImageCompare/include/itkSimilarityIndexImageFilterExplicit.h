#ifndef itkSimilarityIndexImageFilterExplicit_h
#define itkSimilarityIndexImageFilterExplicit_h

#include "ITKImageCompareExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 30 times
#endif //itkSimilarityIndexImageFilterExplicit_h
