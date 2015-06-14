#ifndef itkHessianRecursiveGaussianImageFilterExplicit_h
#define itkHessianRecursiveGaussianImageFilterExplicit_h

#include "ITKImageFeatureExport.h"

extern template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::DiffusionTensor3D<double>, 3u> >; //Instantiated 6 times
extern template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::SymmetricSecondRankTensor<double, 3u>, 3u> >; //Instantiated 6 times
extern template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<double, 3u>, itk::Image<itk::SymmetricSecondRankTensor<double, 3u>, 3u> >; //Instantiated 6 times
#endif //itkHessianRecursiveGaussianImageFilterExplicit_h
