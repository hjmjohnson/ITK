#include "itkTimeVaryingVelocityFieldIntegrationImageFilter.h"

template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<float, 2u>, 3u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<float, 3u>, 4u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 12 times
template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 27 times
template class itk::TimeVaryingVelocityFieldIntegrationImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 15 times
