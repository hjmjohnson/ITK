#ifndef itkMedianImageFilterExplicit_h
#define itkMedianImageFilterExplicit_h

#include "ITKSmoothingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 16 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::MedianImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 21 times
#endif //itkMedianImageFilterExplicit_h
