#ifndef itkFastChamferDistanceImageFilterExplicit_h
#define itkFastChamferDistanceImageFilterExplicit_h

#include "ITKDistanceMapExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastChamferDistanceImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastChamferDistanceImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 7 times
#endif //itkFastChamferDistanceImageFilterExplicit_h
