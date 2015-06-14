#ifndef itkDemonsRegistrationFilterExplicit_h
#define itkDemonsRegistrationFilterExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 45 times
extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkDemonsRegistrationFilterExplicit_h
