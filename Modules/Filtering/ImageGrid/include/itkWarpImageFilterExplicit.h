#ifndef itkWarpImageFilterExplicit_h
#define itkWarpImageFilterExplicit_h

#include "ITKImageGridExport.h"

#include "itkVectorImageToImageAdaptor.h"

extern template class ITKImageGrid_EXPORT itk::WarpImageFilter<itk::Image<unsigned short, 2u>, itk::Image<unsigned short, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 6 times
extern template class ITKImageGrid_EXPORT itk::WarpImageFilter<itk::Image<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 52 times
extern template class ITKImageGrid_EXPORT itk::WarpImageFilter<itk::Image<float, 2u>, itk::Image<float, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 9 times
extern template class ITKImageGrid_EXPORT itk::WarpImageFilter<itk::VectorImageToImageAdaptor<float, 3u>, itk::Image<float, 3u>, itk::Image<itk::Vector<float, 3u>, 3u> >; //Instantiated 24 times
extern template class ITKImageGrid_EXPORT itk::WarpImageFilter<itk::Image<unsigned char, 2u>, itk::Image<unsigned char, 2u>, itk::Image<itk::Vector<float, 2u>, 2u> >; //Instantiated 12 times
#endif //itkWarpImageFilterExplicit_h
