#ifndef itkWatershedImageFilterExplicit_h
#define itkWatershedImageFilterExplicit_h

#include "ITKWatershedsExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WatershedImageFilter<itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WatershedImageFilter<itk::Image<double, 2u> >; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WatershedImageFilter<itk::Image<float, 3u> >; //Instantiated 3 times
#endif //itkWatershedImageFilterExplicit_h
