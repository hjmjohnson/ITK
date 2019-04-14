#include "itkContourDirectedMeanDistanceImageFilter.h"

template class itk::ContourDirectedMeanDistanceImageFilter<itk::Image<float, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 6 times
template class itk::ContourDirectedMeanDistanceImageFilter<itk::Image<unsigned int, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
