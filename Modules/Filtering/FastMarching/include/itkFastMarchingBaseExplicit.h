#ifndef itkFastMarchingBaseExplicit_h
#define itkFastMarchingBaseExplicit_h

#include "ITKFastMarchingExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingBase<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 27 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingBase<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 15 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::FastMarchingBase<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> > >; //Instantiated 15 times
#endif //itkFastMarchingBaseExplicit_h
