#ifndef itkSpatialObjectToImageStatisticsCalculatorExplicit_h
#define itkSpatialObjectToImageStatisticsCalculatorExplicit_h

#include "ITKSpatialObjectsExport.h"

#include "itkEllipseSpatialObject.h"

extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageStatisticsCalculator<itk::Image<unsigned char, 2u>, itk::EllipseSpatialObject<2u>, 1u>; //Instantiated 6 times
#endif //itkSpatialObjectToImageStatisticsCalculatorExplicit_h
