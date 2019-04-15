#ifndef itkWarpVectorImageFilterExplicit_h
#define itkWarpVectorImageFilterExplicit_h

#include "ITKImageGridExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpVectorImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 14 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpVectorImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 55 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpVectorImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpVectorImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 23 times
#endif //itkWarpVectorImageFilterExplicit_h
