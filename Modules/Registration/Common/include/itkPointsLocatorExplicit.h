#ifndef itkPointsLocatorExplicit_h
#define itkPointsLocatorExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::PointsLocator<itk::VectorContainer<unsigned long, itk::Point<float, 3u> > >; //Instantiated 15 times
extern template class ITKRegistrationCommon_EXPORT itk::PointsLocator<itk::VectorContainer<unsigned long, itk::Point<float, 2u> > >; //Instantiated 33 times
#endif //itkPointsLocatorExplicit_h
