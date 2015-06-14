#ifndef itkBSplineDecompositionImageFilterExplicit_h
#define itkBSplineDecompositionImageFilterExplicit_h

#include "ITKImageFunctionExport.h"

extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 1u>, itk::Image<double, 1u> >; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >; //Instantiated 4 times
extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 10 times
extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<double, 2u> >; //Instantiated 8 times
extern template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
#endif //itkBSplineDecompositionImageFilterExplicit_h
