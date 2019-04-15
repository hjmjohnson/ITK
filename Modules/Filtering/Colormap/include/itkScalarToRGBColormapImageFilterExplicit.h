#ifndef itkScalarToRGBColormapImageFilterExplicit_h
#define itkScalarToRGBColormapImageFilterExplicit_h

#include "ITKColormapExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<double, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned int, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned short, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<int, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<int, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<double, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<float, 3u>, itk::Image<itk::RGBPixel<unsigned char>, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned int, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 5 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<short, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<short, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned short, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<float, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<signed char, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<unsigned char, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<signed char, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<float, 3u>, itk::VectorImage<unsigned char, 3u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ScalarToRGBColormapImageFilter<itk::Image<float, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 3 times
#endif //itkScalarToRGBColormapImageFilterExplicit_h
