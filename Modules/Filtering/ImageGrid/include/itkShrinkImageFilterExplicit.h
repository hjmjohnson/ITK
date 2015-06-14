#ifndef itkShrinkImageFilterExplicit_h
#define itkShrinkImageFilterExplicit_h

#include "ITKImageGridExport.h"

extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<double, 3u>, itk::Image<double, 3u> >; //Instantiated 30 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u> >; //Instantiated 8 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 19 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<short, 2u>, itk::Image<short, 2u> >; //Instantiated 13 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<short, 3u>, itk::Image<short, 3u> >; //Instantiated 6 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 16 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<double, 2u>, itk::Image<double, 2u> >; //Instantiated 27 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 78 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 42 times
extern template class ITKImageGrid_EXPORT itk::ShrinkImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u> >; //Instantiated 8 times
#endif //itkShrinkImageFilterExplicit_h
