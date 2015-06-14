#ifndef itkObjectToObjectMetricExplicit_h
#define itkObjectToObjectMetricExplicit_h

#include "ITKOptimizersv4Export.h"

extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<3u, 3u, itk::Image<itk::Vector<double, 3u>, 3u>, double>; //Instantiated 3 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<2u, 2u, itk::Image<float, 2u>, double>; //Instantiated 12 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<3u, 3u, itk::Image<itk::Vector<double, 2u>, 3u>, double>; //Instantiated 3 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<2u, 2u, itk::Image<itk::Vector<float, 2u>, 2u>, double>; //Instantiated 3 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<3u, 3u, itk::Image<double, 3u>, double>; //Instantiated 66 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<2u, 2u, itk::Image<double, 2u>, double>; //Instantiated 126 times
extern template class ITKOptimizersv4_EXPORT itk::ObjectToObjectMetric<3u, 3u, itk::Image<float, 3u>, double>; //Instantiated 6 times
#endif //itkObjectToObjectMetricExplicit_h
