#ifndef itkLabelMapContourOverlayImageFilterExplicit_h
#define itkLabelMapContourOverlayImageFilterExplicit_h

#include "ITKImageFusionExport.h"

#include "itkLabelMap.h"
#include "itkLabelObject.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMapContourOverlayImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::Image<unsigned char, 2u>, itk::Image<itk::RGBPixel<unsigned char>, 2u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMapContourOverlayImageFilter<itk::LabelMap<itk::LabelObject<unsigned char, 2u> >, itk::Image<unsigned char, 2u>, itk::VectorImage<unsigned char, 2u> >; //Instantiated 6 times
#endif //itkLabelMapContourOverlayImageFilterExplicit_h
