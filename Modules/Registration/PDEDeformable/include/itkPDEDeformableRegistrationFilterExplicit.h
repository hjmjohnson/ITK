#ifndef itkPDEDeformableRegistrationFilterExplicit_h
#define itkPDEDeformableRegistrationFilterExplicit_h

#include "ITKPDEDeformableRegistrationExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::PDEDeformableRegistrationFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 45 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::PDEDeformableRegistrationFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::PDEDeformableRegistrationFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 24 times
#endif //itkPDEDeformableRegistrationFilterExplicit_h
