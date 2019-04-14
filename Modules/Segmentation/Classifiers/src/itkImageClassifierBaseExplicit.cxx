#include "itkImageClassifierBase.h"

template class itk::ImageClassifierBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
template class itk::ImageClassifierBase<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
