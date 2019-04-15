#ifndef itkDisplacementFieldJacobianDeterminantFilterExplicit_h
#define itkDisplacementFieldJacobianDeterminantFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldJacobianDeterminantFilter<itk::Image<itk::Vector<float, 2u>, 2u>, float, itk::Image<float, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::DisplacementFieldJacobianDeterminantFilter<itk::Image<itk::Vector<float, 3u>, 3u>, float, itk::Image<float, 3u> >; //Instantiated 53 times
#endif //itkDisplacementFieldJacobianDeterminantFilterExplicit_h
