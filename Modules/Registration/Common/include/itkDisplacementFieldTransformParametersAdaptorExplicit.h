#ifndef itkDisplacementFieldTransformParametersAdaptorExplicit_h
#define itkDisplacementFieldTransformParametersAdaptorExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 10 times
extern template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
extern template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
extern template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
extern template class ITKRegistrationCommon_EXPORT itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
#endif //itkDisplacementFieldTransformParametersAdaptorExplicit_h
