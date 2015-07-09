#include "itkWarpVectorImageFilter.h"

template class ITKImageGrid_EXPORT itk::WarpVectorImageFilter<itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 14 times
template class ITKImageGrid_EXPORT itk::WarpVectorImageFilter<itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 55 times
template class ITKImageGrid_EXPORT itk::WarpVectorImageFilter<itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u>, itk::Image<itk::Vector<double, 2u>, 2u> >; //Instantiated 18 times
template class ITKImageGrid_EXPORT itk::WarpVectorImageFilter<itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u>, itk::Image<itk::Vector<double, 3u>, 3u> >; //Instantiated 23 times
