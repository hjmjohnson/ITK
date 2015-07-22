#ifndef itkWatershedImageFilterExplicit_h
#define itkWatershedImageFilterExplicit_h

#include "ITKWatershedsExport.h"

extern template class ITKWatersheds_EXPORT itk::WatershedImageFilter<itk::Image<float, 2u> >; //Instantiated 9 times
extern template class ITKWatersheds_EXPORT itk::WatershedImageFilter<itk::Image<double, 2u> >; //Instantiated 3 times
extern template class ITKWatersheds_EXPORT itk::WatershedImageFilter<itk::Image<float, 3u> >; //Instantiated 3 times
#endif //itkWatershedImageFilterExplicit_h
