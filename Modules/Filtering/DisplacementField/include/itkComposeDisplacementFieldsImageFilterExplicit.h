#ifndef itkComposeDisplacementFieldsImageFilterExplicit_h
#define itkComposeDisplacementFieldsImageFilterExplicit_h

#include "ITKDisplacementFieldExport.h"

extern template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 17 times
extern template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 6 times
extern template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 10 times
extern template class ITKDisplacementField_EXPORT itk::ComposeDisplacementFieldsImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 14 times
#endif //itkComposeDisplacementFieldsImageFilterExplicit_h
