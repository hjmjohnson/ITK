#ifndef itkSpatialObjectToImageStatisticsCalculatorExplicit_h
#define itkSpatialObjectToImageStatisticsCalculatorExplicit_h

#include "itkEllipseSpatialObject.h"
#include "itkImage.h"
#include "ITKSpatialObjectsExport.h"

extern template class ITKSpatialObjects_EXPORT itk::SpatialObjectToImageStatisticsCalculator<itk::Image<unsigned char, 2u>, itk::EllipseSpatialObject<2u>, 1u>;

#endif //itkSpatialObjectToImageStatisticsCalculatorExplicit_h
