#include "itkSimilarityIndexImageFilter.h"

template class itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
template class itk::SimilarityIndexImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 30 times
