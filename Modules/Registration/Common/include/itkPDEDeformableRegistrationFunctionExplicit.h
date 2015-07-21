#ifndef itkPDEDeformableRegistrationFunctionExplicit_h
#define itkPDEDeformableRegistrationFunctionExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::PDEDeformableRegistrationFunction<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 57 times
extern template class ITKRegistrationCommon_EXPORT itk::PDEDeformableRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::PDEDeformableRegistrationFunction<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 9 times
extern template class ITKRegistrationCommon_EXPORT itk::PDEDeformableRegistrationFunction<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 39 times
extern template class ITKRegistrationCommon_EXPORT itk::PDEDeformableRegistrationFunction<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 24 times
#endif //itkPDEDeformableRegistrationFunctionExplicit_h
