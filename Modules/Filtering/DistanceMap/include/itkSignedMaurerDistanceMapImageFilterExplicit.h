#ifndef itkSignedMaurerDistanceMapImageFilterExplicit_h
#define itkSignedMaurerDistanceMapImageFilterExplicit_h

#include "ITKDistanceMapExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<float, 4u>, itk::Image<float, 4u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<unsigned int, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<unsigned char, 2u>, itk::Image<float, 2u> >; //Instantiated 7 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 19 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SignedMaurerDistanceMapImageFilter<itk::Image<float, 3u>, itk::Image<double, 3u> >; //Instantiated 9 times
#endif //itkSignedMaurerDistanceMapImageFilterExplicit_h
