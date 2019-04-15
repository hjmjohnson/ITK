#ifndef itkFastMarchingStoppingCriterionBaseExplicit_h
#define itkFastMarchingStoppingCriterionBaseExplicit_h

#include "ITKFastMarchingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingStoppingCriterionBase<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshTraits<float, 3u, bool, bool, float, float> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshTraits<float, 3u, bool, bool, float, float> > >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingStoppingCriterionBase<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 24 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingStoppingCriterionBase<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> > >; //Instantiated 10 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingStoppingCriterionBase<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
#endif //itkFastMarchingStoppingCriterionBaseExplicit_h
