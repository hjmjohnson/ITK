#include "itkDisplacementFieldTransformParametersAdaptor.h"

template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 10 times
template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
