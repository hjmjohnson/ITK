#include "itkComplexConjugateImageAdaptor.h"

template class itk::ComplexConjugateImageAdaptor<itk::Image<std::complex<float>, 2u> >; //Instantiated 4 times
template class itk::ComplexConjugateImageAdaptor<itk::Image<std::complex<double>, 2u> >; //Instantiated 4 times
