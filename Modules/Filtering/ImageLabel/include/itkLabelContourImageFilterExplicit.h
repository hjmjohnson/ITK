#ifndef itkLabelContourImageFilterExplicit_h
#define itkLabelContourImageFilterExplicit_h

#include "ITKImageLabelExport.h"

extern template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 9 times
extern template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
extern template class ITKImageLabel_EXPORT itk::LabelContourImageFilter<itk::Image<long, 3u>, itk::Image<long, 3u> >; //Instantiated 6 times
#endif //itkLabelContourImageFilterExplicit_h
