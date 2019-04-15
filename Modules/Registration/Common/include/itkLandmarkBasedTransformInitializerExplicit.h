#ifndef itkLandmarkBasedTransformInitializerExplicit_h
#define itkLandmarkBasedTransformInitializerExplicit_h

#include "ITKRegistrationCommonExport.h"

#include "itkImage.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LandmarkBasedTransformInitializer<itk::VersorRigid3DTransform<double>, itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
#endif //itkLandmarkBasedTransformInitializerExplicit_h
