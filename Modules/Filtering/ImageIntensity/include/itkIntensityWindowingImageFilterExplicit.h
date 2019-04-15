#ifndef itkIntensityWindowingImageFilterExplicit_h
#define itkIntensityWindowingImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::IntensityWindowingImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 20 times
#endif //itkIntensityWindowingImageFilterExplicit_h
