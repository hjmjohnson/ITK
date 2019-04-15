#ifndef itkBinaryContourImageFilterExplicit_h
#define itkBinaryContourImageFilterExplicit_h

#include "ITKImageLabelExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<float, 4u>, itk::Image<float, 4u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 33 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 33 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BinaryContourImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 6 times
#endif //itkBinaryContourImageFilterExplicit_h
