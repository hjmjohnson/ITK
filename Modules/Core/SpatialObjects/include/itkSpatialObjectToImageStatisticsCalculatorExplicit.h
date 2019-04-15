#ifndef itkSpatialObjectToImageStatisticsCalculatorExplicit_h
#define itkSpatialObjectToImageStatisticsCalculatorExplicit_h

#include "itkEllipseSpatialObject.h"
#include "itkImage.h"
#include "ITKSpatialObjectsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SpatialObjectToImageStatisticsCalculator<itk::Image<unsigned char, 2u>, itk::EllipseSpatialObject<2u>, 1u>;

#endif //itkSpatialObjectToImageStatisticsCalculatorExplicit_h
