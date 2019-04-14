#include "itkMutualInformationImageToImageMetric.h"

template class itk::MutualInformationImageToImageMetric<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
template class itk::MutualInformationImageToImageMetric<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
template class itk::MutualInformationImageToImageMetric<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
