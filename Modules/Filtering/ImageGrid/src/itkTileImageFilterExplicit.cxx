#include "itkTileImageFilter.h"

template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 6 times
template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<itk::RGBPixel<unsigned char>, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 8 times
template class ITKImageGrid_EXPORT itk::TileImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 9 times
