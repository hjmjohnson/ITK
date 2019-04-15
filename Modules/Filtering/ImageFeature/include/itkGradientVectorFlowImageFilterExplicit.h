#ifndef itkGradientVectorFlowImageFilterExplicit_h
#define itkGradientVectorFlowImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientVectorFlowImageFilter<itk::Image<itk::CovariantVector<double, 2u>, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u>, double>; //Instantiated 6 times
#endif //itkGradientVectorFlowImageFilterExplicit_h
