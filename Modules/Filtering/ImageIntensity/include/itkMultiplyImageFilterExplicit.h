#ifndef itkMultiplyImageFilterExplicit_h
#define itkMultiplyImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

#include "itkComplexConjugateImageAdaptor.h"

extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<std::complex<double>, 3u>, itk::Image<std::complex<double>, 3u>, itk::Image<std::complex<double>, 3u> >; //Instantiated 30 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u>, itk::Image<int, 3u> >; //Instantiated 15 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 13 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 39 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<std::complex<float>, 2u>, itk::Image<std::complex<float>, 2u>, itk::Image<std::complex<float>, 2u> >; //Instantiated 9 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<std::complex<double>, 2u>, itk::Image<std::complex<double>, 2u>, itk::Image<std::complex<double>, 2u> >; //Instantiated 56 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 65 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u> >; //Instantiated 18 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 32 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<double, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 28 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 18 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u> >; //Instantiated 15 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 15 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<std::complex<double>, 2u>, itk::ComplexConjugateImageAdaptor<itk::Image<std::complex<double>, 2u> >, itk::Image<std::complex<double>, 2u> >; //Instantiated 7 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 13 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u> >; //Instantiated 18 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u>, itk::Image<int, 2u> >; //Instantiated 15 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u>, itk::Image<signed char, 3u> >; //Instantiated 9 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 27 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u>, itk::Image<double, 2u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<double, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 25 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u> >; //Instantiated 17 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<double, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 45 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::Image<double, 2u> >; //Instantiated 10 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u>, itk::Image<double, 3u> >; //Instantiated 6 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 26 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u>, itk::Image<short, 2u> >; //Instantiated 15 times
extern template class ITKImageIntensity_EXPORT itk::MultiplyImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u>, itk::Image<signed char, 2u> >; //Instantiated 9 times
#endif //itkMultiplyImageFilterExplicit_h
