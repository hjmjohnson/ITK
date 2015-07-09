#ifndef itkSimilarityIndexImageFilterExplicit_h
#define itkSimilarityIndexImageFilterExplicit_h

#include "ITKImageCompareExport.h"

extern template class ITKImageCompare_EXPORT itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
extern template class ITKImageCompare_EXPORT itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 30 times
#endif //itkSimilarityIndexImageFilterExplicit_h
