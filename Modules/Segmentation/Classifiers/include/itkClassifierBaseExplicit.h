#ifndef itkClassifierBaseExplicit_h
#define itkClassifierBaseExplicit_h

#include "ITKClassifiersExport.h"

#include "itkImage.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ClassifierBase<itk::Image<itk::Vector<unsigned short, 1u>, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ClassifierBase<itk::Image<itk::Vector<double, 2u>, 3u> >; //Instantiated 6 times
#endif //itkClassifierBaseExplicit_h
