#include "itkHessianRecursiveGaussianImageFilter.h"

template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::DiffusionTensor3D<double>, 3u> >; //Instantiated 6 times
template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::SymmetricSecondRankTensor<double, 3u>, 3u> >; //Instantiated 6 times
template class ITKImageFeature_EXPORT itk::HessianRecursiveGaussianImageFilter<itk::Image<double, 3u>, itk::Image<itk::SymmetricSecondRankTensor<double, 3u>, 3u> >; //Instantiated 6 times
