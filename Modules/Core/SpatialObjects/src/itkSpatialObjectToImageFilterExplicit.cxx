#include "itkSpatialObjectToImageFilter.h"

template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::GroupSpatialObject<3u>, itk::Image<short, 3u> >; //Instantiated 6 times
template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::BoxSpatialObject<2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
