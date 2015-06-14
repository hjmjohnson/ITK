#ifndef itkTubeSpatialObjectExplicit_h
#define itkTubeSpatialObjectExplicit_h

#include "ITKSpatialObjectsExport.h"
#include "itkTubeSpatialObjectPoint.h"
#include "itkDTITubeSpatialObjectPoint.h"


extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<2u, itk::TubeSpatialObjectPoint<2u> >;
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<2u, itk::DTITubeSpatialObjectPoint<2u> >;
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<3u, itk::TubeSpatialObjectPoint<3u> >;
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<3u, itk::DTITubeSpatialObjectPoint<3u> >;

#endif //itkTubeSpatialObjectExplicit_h
