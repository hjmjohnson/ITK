#ifndef itkQuadEdgeMeshPointExplicit_h
#define itkQuadEdgeMeshPointExplicit_h

#include "ITKQuadEdgeMeshExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::QuadEdgeMeshPoint<double, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 30 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::QuadEdgeMeshPoint<float, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 120 times
#endif //itkQuadEdgeMeshPointExplicit_h
