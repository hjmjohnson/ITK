#ifndef itkMeanSquareRegistrationFunctionExplicit_h
#define itkMeanSquareRegistrationFunctionExplicit_h

#include "ITKRegistrationCommonExport.h"

extern template class ITKRegistrationCommon_EXPORT itk::MeanSquareRegistrationFunction<itk::Image<unsigned char, 3u>, itk::Image<unsigned char, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 9 times
#endif //itkMeanSquareRegistrationFunctionExplicit_h
