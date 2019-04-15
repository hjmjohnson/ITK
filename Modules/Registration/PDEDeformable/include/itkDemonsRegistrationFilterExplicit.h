#ifndef itkDemonsRegistrationFilterExplicit_h
#define itkDemonsRegistrationFilterExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 45 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkDemonsRegistrationFilterExplicit_h
