#include "itkBSplineDecompositionImageFilter.h"

template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 1u>, itk::Image<double, 1u> >; //Instantiated 4 times
template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >; //Instantiated 4 times
template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 10 times
template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<double, 2u> >; //Instantiated 8 times
template class ITKImageFunction_EXPORT itk::BSplineDecompositionImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
