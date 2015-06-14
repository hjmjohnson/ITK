#ifndef itkMeanImageFilterExplicit_h
#define itkMeanImageFilterExplicit_h

#include "ITKSmoothingExport.h"

extern template class ITKSmoothing_EXPORT itk::MeanImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 7 times
extern template class ITKSmoothing_EXPORT itk::MeanImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
#endif //itkMeanImageFilterExplicit_h
