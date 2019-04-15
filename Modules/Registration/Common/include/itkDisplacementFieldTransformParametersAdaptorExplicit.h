#ifndef itkDisplacementFieldTransformParametersAdaptorExplicit_h
#define itkDisplacementFieldTransformParametersAdaptorExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldTransformParametersAdaptor<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldTransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldTransformParametersAdaptor<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
#endif //itkDisplacementFieldTransformParametersAdaptorExplicit_h
