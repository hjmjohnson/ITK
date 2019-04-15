#ifndef itkBSplineControlPointImageFilterExplicit_h
#define itkBSplineControlPointImageFilterExplicit_h

#include "ITKImageGridExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 3u>, itk::Image<itk::Vector<float, 1u>, 3u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 2u>, 3u>, itk::Image<itk::Vector<float, 2u>, 3u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<double, 2u>, 3u>, itk::Image<itk::Vector<double, 2u>, 3u> >; //Instantiated 12 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 2u>, itk::Image<itk::Vector<float, 1u>, 2u> >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 1u>, 4u>, itk::Image<itk::Vector<float, 1u>, 4u> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<float, 3u>, 4u>, itk::Image<itk::Vector<float, 3u>, 4u> >; //Instantiated 9 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::BSplineControlPointImageFilter<itk::Image<itk::Vector<double, 3u>, 4u>, itk::Image<itk::Vector<double, 3u>, 4u> >; //Instantiated 18 times
#endif //itkBSplineControlPointImageFilterExplicit_h
