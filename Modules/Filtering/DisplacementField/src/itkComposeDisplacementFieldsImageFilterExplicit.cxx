#include "itkComposeDisplacementFieldsImageFilter.h"

template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 17 times
template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 6 times
template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 10 times
template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 14 times
