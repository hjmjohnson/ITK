#ifndef itkTileImageFilterExplicit_h
#define itkTileImageFilterExplicit_h

#include "ITKImageGridExport.h"

extern template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
extern template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 8 times
extern template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
#endif //itkTileImageFilterExplicit_h
