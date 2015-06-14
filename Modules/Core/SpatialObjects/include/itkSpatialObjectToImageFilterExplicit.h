#ifndef itkSpatialObjectToImageFilterExplicit_h
#define itkSpatialObjectToImageFilterExplicit_h

#include "itkGroupSpatialObject.h"
#include "itkBoxSpatialObject.h"

#include "ITKSpatialObjectsExport.h"

extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::GroupSpatialObject<3u>, itk::Image<short, 3u> >;
extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageFilter<itk::BoxSpatialObject<2u>, itk::Image<unsigned char, 2u> >;

#endif //itkSpatialObjectToImageFilterExplicit_h
