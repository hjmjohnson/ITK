#ifndef itkNeighborhoodOperatorImageFunctionExplicit_h
#define itkNeighborhoodOperatorImageFunctionExplicit_h

#include "ITKImageFunctionExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NeighborhoodOperatorImageFunction<itk::Image<unsigned char, 2u>, double>; //Instantiated 3 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, double>; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NeighborhoodOperatorImageFunction<itk::Image<double, 2u>, double>; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NeighborhoodOperatorImageFunction<itk::Image<float, 3u>, float>; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::NeighborhoodOperatorImageFunction<itk::Image<float, 2u>, float>; //Instantiated 6 times
#endif //itkNeighborhoodOperatorImageFunctionExplicit_h
