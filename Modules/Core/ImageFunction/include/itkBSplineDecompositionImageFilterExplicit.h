#ifndef itkBSplineDecompositionImageFilterExplicit_h
#define itkBSplineDecompositionImageFilterExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<double, 1u>, itk::Image<double, 1u> >; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >; //Instantiated 4 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<double, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
#endif //itkBSplineDecompositionImageFilterExplicit_h
