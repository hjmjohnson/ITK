#ifndef itkImageClassifierBaseExplicit_h
#define itkImageClassifierBaseExplicit_h

#include "ITKClassifiersExport.h"

extern template class ITKClassifiers_EXPORT itk::ImageClassifierBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
extern template class ITKClassifiers_EXPORT itk::ImageClassifierBase<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 6 times
#endif //itkImageClassifierBaseExplicit_h
