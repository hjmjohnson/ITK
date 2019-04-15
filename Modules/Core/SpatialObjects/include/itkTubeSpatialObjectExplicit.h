#ifndef itkTubeSpatialObjectExplicit_h
#define itkTubeSpatialObjectExplicit_h

#include "ITKSpatialObjectsExport.h"
#include "itkTubeSpatialObjectPoint.h"
#include "itkDTITubeSpatialObjectPoint.h"


ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TubeSpatialObject<2u, itk::TubeSpatialObjectPoint<2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TubeSpatialObject<2u, itk::DTITubeSpatialObjectPoint<2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TubeSpatialObject<3u, itk::TubeSpatialObjectPoint<3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TubeSpatialObject<3u, itk::DTITubeSpatialObjectPoint<3u> >;

#endif //itkTubeSpatialObjectExplicit_h
