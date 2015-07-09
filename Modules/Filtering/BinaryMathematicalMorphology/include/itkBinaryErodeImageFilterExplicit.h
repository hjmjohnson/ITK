#ifndef itkBinaryErodeImageFilterExplicit_h
#define itkBinaryErodeImageFilterExplicit_h

#include "ITKBinaryMathematicalMorphologyExport.h"

extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<signed char, 3u>, itk::Image<signed char, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u>, itk::BinaryBallStructuringElement<unsigned short, 3u, itk::NeighborhoodAllocator<unsigned short> > >; //Instantiated 45 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<int, 3u>, itk::Image<int, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned int, 2u>, itk::Image<unsigned int, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::BinaryBallStructuringElement<float, 3u, itk::NeighborhoodAllocator<float> > >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<int, 2u>, itk::Image<int, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned short, 3u>, itk::Image<unsigned short, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 21 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 15 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::BinaryBallStructuringElement<unsigned char, 3u, itk::NeighborhoodAllocator<unsigned char> > >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::BinaryBallStructuringElement<float, 2u, itk::NeighborhoodAllocator<float> > >; //Instantiated 6 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<signed char, 2u>, itk::Image<signed char, 2u>, itk::FlatStructuringElement<2u> >; //Instantiated 12 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned char, 1u>, itk::Image<unsigned char, 1u>, itk::FlatStructuringElement<1u> >; //Instantiated 9 times
extern template class ITKBinaryMathematicalMorphology_EXPORT itk::BinaryErodeImageFilter<itk::Image<unsigned int, 3u>, itk::Image<unsigned int, 3u>, itk::FlatStructuringElement<3u> >; //Instantiated 12 times
#endif //itkBinaryErodeImageFilterExplicit_h
