#ifndef itkDemonsRegistrationFunctionExplicit_h
#define itkDemonsRegistrationFunctionExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFunction<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 48 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFunction<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DemonsRegistrationFunction<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 21 times
#endif //itkDemonsRegistrationFunctionExplicit_h
