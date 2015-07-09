#ifndef itkObjectMorphologyImageFilterExplicit_h
#define itkObjectMorphologyImageFilterExplicit_h

#include "ITKBinaryMathematicalMorphologyExport.h"

#include "itkFlatStructuringElement.h"
#include "itkBinaryBallStructuringElement.h"

extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::ObjectMorphologyImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 6 times
#endif //itkObjectMorphologyImageFilterExplicit_h
