#ifndef itkVectorMagnitudeImageFilterExplicit_h
#define itkVectorMagnitudeImageFilterExplicit_h

#include "ITKImageIntensityExport.h"

extern template class ITKImageIntensity_EXPORT itk::VectorMagnitudeImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<double, 2u> >; //Instantiated 11 times
extern template class ITKImageIntensity_EXPORT itk::VectorMagnitudeImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<double, 3u> >; //Instantiated 14 times
#endif //itkVectorMagnitudeImageFilterExplicit_h
