#ifndef itkVectorCastImageFilterExplicit_h
#define itkVectorCastImageFilterExplicit_h

#include "ITKImageFilterBaseExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorCastImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 14 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorCastImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 53 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::VectorCastImageFilter<itk::Image<itk::CovariantVector<float, 2u>, 2u>, itk::Image<itk::FixedArray<float, 2u>, 2u> >; //Instantiated 25 times
#endif //itkVectorCastImageFilterExplicit_h
