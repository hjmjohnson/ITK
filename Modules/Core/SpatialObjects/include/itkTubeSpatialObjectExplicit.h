#ifndef itkTubeSpatialObjectExplicit_h
#define itkTubeSpatialObjectExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkVesselTubeSpatialObjectPoint.h"
#include "itkDTITubeSpatialObjectPoint.h"

extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<3u, itk::TubeSpatialObjectPoint<3u> >; //Instantiated 48 times
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<3u, itk::VesselTubeSpatialObjectPoint<3u> >; //Instantiated 39 times
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<2u, itk::VesselTubeSpatialObjectPoint<2u> >; //Instantiated 54 times
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<2u, itk::TubeSpatialObjectPoint<2u> >; //Instantiated 57 times
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<2u, itk::DTITubeSpatialObjectPoint<2u> >; //Instantiated 54 times
extern template class ITKSpatialObjects_EXPORT itk::TubeSpatialObject<3u, itk::DTITubeSpatialObjectPoint<3u> >; //Instantiated 48 times
#endif //itkTubeSpatialObjectExplicit_h
