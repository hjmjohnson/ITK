#ifndef itkNthElementImageAdaptorExplicit_h
#define itkNthElementImageAdaptorExplicit_h

#include "ITKImageAdaptorsExport.h"

extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::CovariantVector<double, 2u>, 2u>, float>; //Instantiated 188 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::Vector<float, 3u>, 3u>, float>; //Instantiated 4 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::FixedArray<float, 2u>, 2u>, float>; //Instantiated 22 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::DiffusionTensor3D<double>, 3u>, float>; //Instantiated 4 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::CovariantVector<float, 2u>, 2u>, float>; //Instantiated 8 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::SymmetricSecondRankTensor<double, 3u>, 3u>, float>; //Instantiated 8 times
extern template class ITKImageAdaptors_EXPORT itk::NthElementImageAdaptor<itk::Image<itk::CovariantVector<double, 3u>, 3u>, float>; //Instantiated 74 times
#endif //itkNthElementImageAdaptorExplicit_h
