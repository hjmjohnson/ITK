#ifndef itkDemonsRegistrationFunctionExplicit_h
#define itkDemonsRegistrationFunctionExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFunction<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 48 times
extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFunction<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 6 times
extern template class ITKPDEDeformableRegistration_EXPORT itk::DemonsRegistrationFunction<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 21 times
#endif //itkDemonsRegistrationFunctionExplicit_h
