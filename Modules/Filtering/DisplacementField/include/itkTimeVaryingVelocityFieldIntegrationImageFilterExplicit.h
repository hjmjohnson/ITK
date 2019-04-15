#ifndef itkTimeVaryingVelocityFieldIntegrationImageFilterExplicit_h
#define itkTimeVaryingVelocityFieldIntegrationImageFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<float, 2u>, 3u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<float, 3u>, 4u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 15 times
#endif //itkTimeVaryingVelocityFieldIntegrationImageFilterExplicit_h
