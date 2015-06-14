#ifndef itkExponentialDisplacementFieldImageFilterExplicit_h
#define itkExponentialDisplacementFieldImageFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

extern template class ITKDisplacementField_EXPORT itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 57 times
extern template class ITKDisplacementField_EXPORT itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 24 times
extern template class ITKDisplacementField_EXPORT itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 30 times
extern template class ITKDisplacementField_EXPORT itk::ExponentialDisplacementFieldImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkExponentialDisplacementFieldImageFilterExplicit_h
