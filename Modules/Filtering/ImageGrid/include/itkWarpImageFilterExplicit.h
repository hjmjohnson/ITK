#ifndef itkWarpImageFilterExplicit_h
#define itkWarpImageFilterExplicit_h

#include "ITKImageGridExport.h"

#include "itkVectorImageToImageAdaptor.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 52 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpImageFilter<itk::VectorImageToImageAdaptor<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::WarpImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkWarpImageFilterExplicit_h
