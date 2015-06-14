#include "itkLabelContourImageFilter.h"

template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 9 times
template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<long, 3u>, itk::Image<long, 3u> >; //Instantiated 6 times
