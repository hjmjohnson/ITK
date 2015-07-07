#ifndef itkSpatialObjectToImageFilterExplicit_h
#define itkSpatialObjectToImageFilterExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkGroupSpatialObject.h"
#include "itkBoxSpatialObject.h"

extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::GroupSpatialObject<3u>, itk::Image<short, 3u> >; //Instantiated 6 times
extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::BoxSpatialObject<2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
#endif //itkSpatialObjectToImageFilterExplicit_h
