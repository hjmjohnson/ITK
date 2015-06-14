#ifndef itkLabelMapExplicit_h
#define itkLabelMapExplicit_h

#include "itkLabelObject.h"

extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::LabelObject<signed char, 2u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;

#ifndef ITKShapeLabelObjectIncludes
#include "itkShapeLabelObject.h"
#include "itkStatisticsLabelObject.h"

extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned char, 2u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned char, 3u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> >;

extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::StatisticsLabelObject<unsigned long, 2u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 3u> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 2u> >;
#endif //ITKShapeLabelObjectIncludes

#ifndef ITKAttributeLabelObjectIncludes
#include "itkAttributeLabelObject.h"

extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned char, 3u, int> >;
extern template class ITKLabelMap_EXPORT itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> >;
#endif //ITKAttributeLabelObjectIncludes

#endif //itkLabelMapExplicit_h
