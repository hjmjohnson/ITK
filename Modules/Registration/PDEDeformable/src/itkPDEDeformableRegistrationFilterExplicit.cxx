#include "itkPDEDeformableRegistrationFilter.h"

template class ITKPDEDeformableRegistration_EXPORT itk::PDEDeformableRegistrationFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 45 times
template class ITKPDEDeformableRegistration_EXPORT itk::PDEDeformableRegistrationFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 18 times
template class ITKPDEDeformableRegistration_EXPORT itk::PDEDeformableRegistrationFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 24 times
