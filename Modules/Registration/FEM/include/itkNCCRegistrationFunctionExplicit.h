#ifndef itkNCCRegistrationFunctionExplicit_h
#define itkNCCRegistrationFunctionExplicit_h

#include "ITKFEMRegistrationExport.h"

extern template class ITKFEMRegistration_EXPORT itk::NCCRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
#endif //itkNCCRegistrationFunctionExplicit_h
