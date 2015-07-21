#ifndef itkCommandIterationUpdateExplicit_h
#define itkCommandIterationUpdateExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkGradientDescentOptimizer.h"
#include "itkRegularStepGradientDescentOptimizer.h"

extern template class ITKRegistrationCommon_EXPORT itk::CommandIterationUpdate<itk::GradientDescentOptimizer>; //Instantiated 12 times
extern template class ITKRegistrationCommon_EXPORT itk::CommandIterationUpdate<itk::RegularStepGradientDescentOptimizer>; //Instantiated 14 times
#endif //itkCommandIterationUpdateExplicit_h
