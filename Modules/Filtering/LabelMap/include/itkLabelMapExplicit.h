#ifndef itkLabelMapExplicit_h
#define itkLabelMapExplicit_h

#include "itkLabelObject.h"
#include "itkAttributeLabelObject.h"
#include "itkShapeLabelObject.h"
#include "itkStatisticsLabelObject.h"

extern template class itk::LabelMap<itk::LabelObject<unsigned char, 3u> >;
extern template class itk::LabelMap<itk::AttributeLabelObject<unsigned long, 3u, bool> >;
extern template class itk::LabelMap<itk::LabelObject<signed char, 2u> >;
extern template class itk::LabelMap<itk::ShapeLabelObject<unsigned char, 2u> >;
extern template class itk::LabelMap<itk::StatisticsLabelObject<unsigned long, 2u> >;
extern template class itk::LabelMap<itk::LabelObject<unsigned long, 2u> >;
extern template class itk::LabelMap<itk::ShapeLabelObject<unsigned char, 3u> >;
extern template class itk::LabelMap<itk::ShapeLabelObject<unsigned long, 2u> >;
extern template class itk::LabelMap<itk::LabelObject<unsigned long, 3u> >;
extern template class itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 3u> >;
extern template class itk::LabelMap<itk::AttributeLabelObject<unsigned char, 3u, int> >;
extern template class itk::LabelMap<itk::LabelObject<unsigned char, 2u> >;
extern template class itk::LabelMap<itk::AttributeLabelObject<unsigned long, 2u, bool> >;
extern template class itk::LabelMap<itk::StatisticsLabelObject<unsigned char, 2u> >;
#endif //itkLabelMapExplicit_h
