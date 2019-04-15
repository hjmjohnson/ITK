#ifndef itkGradientRecursiveGaussianImageFilterExplicit_h
#define itkGradientRecursiveGaussianImageFilterExplicit_h

#include "ITKImageGradientExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<short, 3u>, itk::Image<itk::CovariantVector<double, 3u>, 3u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<int, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<unsigned int, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<short, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<unsigned char, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 48 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<unsigned short, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 21 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::VectorImage<float, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<double, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 147 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::CovariantVector<double, 3u>, 3u> >; //Instantiated 69 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<itk::FixedArray<float, 2u>, 2u> >; //Instantiated 36 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<itk::CovariantVector<double, 2u>, 2u> >; //Instantiated 105 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<itk::CovariantVector<float, 2u>, 2u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 3u>, itk::Image<itk::CovariantVector<float, 3u>, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<char, 3u>, itk::Image<itk::CovariantVector<double, 3u>, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::GradientRecursiveGaussianImageFilter<itk::Image<double, 3u>, itk::Image<itk::CovariantVector<double, 3u>, 3u> >; //Instantiated 63 times
#endif //itkGradientRecursiveGaussianImageFilterExplicit_h
