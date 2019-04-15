#ifndef itkLabelMapExplicit_h
#define itkLabelMapExplicit_h

#include "itkLabelObject.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::LabelObject<signed char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;

#ifndef ITKShapeLabelObjectIncludes
#include "itkShapeLabelObject.h"
#include "itkStatisticsLabelObject.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::ShapeLabelObject<unsigned char, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::ShapeLabelObject<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> >;

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::StatisticsLabelObject<unsigned long, 2u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 3u> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 2u> >;
#endif //ITKShapeLabelObjectIncludes

#ifndef ITKAttributeLabelObjectIncludes
#include "itkAttributeLabelObject.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::AttributeLabelObject<unsigned char, 3u, int> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> >;
#endif //ITKAttributeLabelObjectIncludes

#endif //itkLabelMapExplicit_h
