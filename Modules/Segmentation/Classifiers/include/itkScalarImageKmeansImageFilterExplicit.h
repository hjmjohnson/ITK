#ifndef itkScalarImageKmeansImageFilterExplicit_h
#define itkScalarImageKmeansImageFilterExplicit_h

#include "ITKClassifiersExport.h"

extern template class ITKClassifiers_EXPORT itk::ScalarImageKmeansImageFilter<itk::Image<short, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
extern template class ITKClassifiers_EXPORT itk::ScalarImageKmeansImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 12 times
extern template class ITKClassifiers_EXPORT itk::ScalarImageKmeansImageFilter<itk::Image<short, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 6 times
#endif //itkScalarImageKmeansImageFilterExplicit_h
