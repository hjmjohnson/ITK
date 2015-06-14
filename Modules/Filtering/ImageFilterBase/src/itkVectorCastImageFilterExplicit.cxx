#include "itkVectorCastImageFilter.h"

template class ITKImageFilterBase_EXPORT itk::VectorCastImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 14 times
template class ITKImageFilterBase_EXPORT itk::VectorCastImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 53 times
template class ITKImageFilterBase_EXPORT itk::VectorCastImageFilter<itk::Image<itk::CovariantVector<float, 2u>, 2u>, itk::Image<itk::FixedArray<float, 2u>, 2u> >; //Instantiated 25 times
