#ifndef itkComplexConjugateImageAdaptorExplicit_h
#define itkComplexConjugateImageAdaptorExplicit_h

#include "ITKImageAdaptorsExport.h"

extern template class ITKImageAdaptors_EXPORT itk::ComplexConjugateImageAdaptor<itk::Image<std::complex<float>, 2u> >; //Instantiated 4 times
extern template class ITKImageAdaptors_EXPORT itk::ComplexConjugateImageAdaptor<itk::Image<std::complex<double>, 2u> >; //Instantiated 4 times
#endif //itkComplexConjugateImageAdaptorExplicit_h
