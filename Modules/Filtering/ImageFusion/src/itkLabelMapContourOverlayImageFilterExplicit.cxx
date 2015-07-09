#include "itkLabelMapContourOverlayImageFilter.h"

template class ITKImageFusion_EXPORT itk::LabelMapContourOverlayImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::Image<unsigned char, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 6 times
template class ITKImageFusion_EXPORT itk::LabelMapContourOverlayImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::Image<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 6 times
