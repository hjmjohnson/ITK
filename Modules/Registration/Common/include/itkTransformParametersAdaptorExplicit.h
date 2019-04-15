#ifndef itkTransformParametersAdaptorExplicit_h
#define itkTransformParametersAdaptorExplicit_h

#include "ITKRegistrationCommonExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::AffineTransform<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::Euler2DTransform<double> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::BSplineExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::TimeVaryingBSplineVelocityFieldTransform<double, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::BSplineTransform<double, 3u, 3u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateTimeVaryingVelocityFieldTransform<double, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::Euler3DTransform<double> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::AffineTransform<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::GaussianExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::Similarity3DTransform<double> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 13 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TransformParametersAdaptor<itk::TranslationTransform<double, 3u> >; //Instantiated 6 times
#endif //itkTransformParametersAdaptorExplicit_h
