#ifndef itkTileImageFilterExplicit_h
#define itkTileImageFilterExplicit_h

#include "ITKImageGridExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TileImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TileImageFilter<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TileImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkTileImageFilterExplicit_h
