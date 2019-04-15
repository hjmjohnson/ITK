#ifndef itkCommandIterationUpdateExplicit_h
#define itkCommandIterationUpdateExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkGradientDescentOptimizer.h"
#include "itkRegularStepGradientDescentOptimizer.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CommandIterationUpdate<itk::GradientDescentOptimizer>; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::CommandIterationUpdate<itk::RegularStepGradientDescentOptimizer>; //Instantiated 14 times
#endif //itkCommandIterationUpdateExplicit_h
