#include "itkPointSetToImageMetric.h"

template class ITKRegistrationCommon_EXPORT itk::PointSetToImageMetric<itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >, itk::Image<float, 2u> >; //Instantiated 6 times
template class ITKRegistrationCommon_EXPORT itk::PointSetToImageMetric<itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >, itk::Image<double, 2u> >; //Instantiated 12 times
