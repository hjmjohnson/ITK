#ifndef itkClassifierBaseExplicit_h
#define itkClassifierBaseExplicit_h

#include "ITKClassifiersExport.h"

#include "itkImage.h"

extern template class ITKClassifiers_EXPORT itk::ClassifierBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u> >; //Instantiated 6 times
extern template class ITKClassifiers_EXPORT itk::ClassifierBase<itk::Image<itk::Vector<double, 2u>, 3u> >; //Instantiated 6 times
#endif //itkClassifierBaseExplicit_h
