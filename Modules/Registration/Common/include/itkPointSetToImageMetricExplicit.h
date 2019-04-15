#ifndef itkPointSetToImageMetricExplicit_h
#define itkPointSetToImageMetricExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkPointSet.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::PointSetToImageMetric<itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >, itk::Image<float, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::PointSetToImageMetric<itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >, itk::Image<double, 2u> >; //Instantiated 12 times
#endif //itkPointSetToImageMetricExplicit_h
