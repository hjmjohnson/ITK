#ifndef itkSyNImageRegistrationMethodExplicit_h
#define itkSyNImageRegistrationMethodExplicit_h

#include "ITKRegistrationMethodsv4Export.h"

extern template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 9 times
extern template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 12 times
extern template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 6 times
#endif //itkSyNImageRegistrationMethodExplicit_h
