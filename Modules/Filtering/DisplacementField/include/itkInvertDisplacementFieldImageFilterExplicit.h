#ifndef itkInvertDisplacementFieldImageFilterExplicit_h
#define itkInvertDisplacementFieldImageFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

extern template class ITKDisplacementField_EXPORT itk::InvertDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 9 times
extern template class ITKDisplacementField_EXPORT itk::InvertDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 15 times
extern template class ITKDisplacementField_EXPORT itk::InvertDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 6 times
extern template class ITKDisplacementField_EXPORT itk::InvertDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 12 times
#endif //itkInvertDisplacementFieldImageFilterExplicit_h
