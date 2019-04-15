#ifndef itkFastMarchingThresholdStoppingCriterionExplicit_h
#define itkFastMarchingThresholdStoppingCriterionExplicit_h

#include "ITKFastMarchingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingThresholdStoppingCriterion<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingThresholdStoppingCriterion<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 16 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingThresholdStoppingCriterion<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> > >; //Instantiated 8 times
#endif //itkFastMarchingThresholdStoppingCriterionExplicit_h
