#ifndef itkTransformParametersAdaptorBaseExplicit_h
#define itkTransformParametersAdaptorBaseExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkDisplacementFieldTransform.h"
#include "itkBSplineExponentialDiffeomorphicTransform.h"
#include "itkGaussianExponentialDiffeomorphicTransform.h"
#include "itkGaussianSmoothingOnUpdateTimeVaryingVelocityFieldTransform.h"
#include "itkEuler3DTransform.h"
#include "itkEuler2DTransform.h"
#include "itkGaussianSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkAffineTransform.h"
#include "itkTranslationTransform.h"
#include "itkSimilarity3DTransform.h"
#include "itkTimeVaryingBSplineVelocityFieldTransform.h"
#include "itkBSplineTransform.h"
#include "itkBSplineSmoothingOnUpdateDisplacementFieldTransform.h"


extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::DisplacementFieldTransform<double, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::DisplacementFieldTransform<double, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::Transform<double, 2u, 2u> >; //Instantiated 24 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::BSplineExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::GaussianExponentialDiffeomorphicTransform<double, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::GaussianSmoothingOnUpdateTimeVaryingVelocityFieldTransform<double, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::Euler3DTransform<double> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::Euler2DTransform<double> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::TranslationTransform<double, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::AffineTransform<double, 2u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::TimeVaryingBSplineVelocityFieldTransform<double, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::Similarity3DTransform<double> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::Transform<double, 3u, 3u> >; //Instantiated 45 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::AffineTransform<double, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::BSplineTransform<double, 3u, 3u> >; //Instantiated 6 times
extern template class ITKRegistrationCommon_EXPORT itk::TransformParametersAdaptorBase<itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3u> >; //Instantiated 6 times
#endif //itkTransformParametersAdaptorBaseExplicit_h
