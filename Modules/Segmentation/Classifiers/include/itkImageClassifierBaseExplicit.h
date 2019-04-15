#ifndef itkImageClassifierBaseExplicit_h
#define itkImageClassifierBaseExplicit_h

#include "ITKClassifiersExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageClassifierBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageClassifierBase<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
#endif //itkImageClassifierBaseExplicit_h
