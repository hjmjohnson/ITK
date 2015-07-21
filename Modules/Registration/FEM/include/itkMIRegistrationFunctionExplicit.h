#ifndef itkMIRegistrationFunctionExplicit_h
#define itkMIRegistrationFunctionExplicit_h

#include "ITKFEMRegistrationExport.h"

extern template class ITKFEMRegistration_EXPORT itk::MIRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
#endif //itkMIRegistrationFunctionExplicit_h
