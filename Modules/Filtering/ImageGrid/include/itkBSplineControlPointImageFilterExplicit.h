#ifndef itkBSplineControlPointImageFilterExplicit_h
#define itkBSplineControlPointImageFilterExplicit_h

#include "ITKImageGridExport.h"

extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 3u>, itk::Image<itk::Vector<float, 1u>, 3u> >; //Instantiated 18 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 2u>, 3u>, itk::Image<itk::Vector<float, 2u>, 3u> >; //Instantiated 9 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 3u> >; //Instantiated 12 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 2u>, itk::Image<itk::Vector<float, 1u>, 2u> >; //Instantiated 18 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 4u>, itk::Image<itk::Vector<float, 1u>, 4u> >; //Instantiated 6 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 3u>, 4u>, itk::Image<itk::Vector<float, 3u>, 4u> >; //Instantiated 9 times
extern template class ITKImageGrid_EXPORT itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 4u> >; //Instantiated 18 times
#endif //itkBSplineControlPointImageFilterExplicit_h
