#ifndef itkSmoothingRecursiveGaussianImageFilterExplicit_h
#define itkSmoothingRecursiveGaussianImageFilterExplicit_h

#include "ITKSmoothingExport.h"

extern template class ITKSmoothing_EXPORT itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 15 times
extern template class ITKSmoothing_EXPORT itk::SmoothingRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 9 times
extern template class ITKSmoothing_EXPORT itk::SmoothingRecursiveGaussianImageFilter<itk::VectorImage<float, 3u>, itk::VectorImage<float, 3u> >; //Instantiated 6 times
#endif //itkSmoothingRecursiveGaussianImageFilterExplicit_h
