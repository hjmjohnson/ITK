#include "itkLabelContourImageFilter.h"

template class itk::LabelContourImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 9 times
template class itk::LabelContourImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
template class itk::LabelContourImageFilter<itk::Image<long, 3u>, itk::Image<long, 3u> >; //Instantiated 6 times
