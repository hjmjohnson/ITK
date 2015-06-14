#include "itkSyNImageRegistrationMethod.h"

template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 9 times
template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 9 times
template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 12 times
template class ITKRegistrationMethodsv4_EXPORT itk::SyNImageRegistrationMethod<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 6 times
