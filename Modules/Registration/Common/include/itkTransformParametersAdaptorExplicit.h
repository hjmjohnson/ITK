#ifndef itkTransformParametersAdaptorExplicit_h
#define itkTransformParametersAdaptorExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::AffineTransform<double, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::Euler2DTransform<double> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::BSplineExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 10 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::TimeVaryingBSplineVelocityFieldTransform<double, 3u> >; //Instantiated 8 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::BSplineTransform<double, 3u, 3u> >; //Instantiated 10 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateTimeVaryingVelocityFieldTransform<double, 3u> >; //Instantiated 8 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::Euler3DTransform<double> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::AffineTransform<double, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::GaussianExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 10 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::Similarity3DTransform<double> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 10 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptor<itk::TranslationTransform<double, 3u> >; //Instantiated 6 times
#endif //itkTransformParametersAdaptorExplicit_h
