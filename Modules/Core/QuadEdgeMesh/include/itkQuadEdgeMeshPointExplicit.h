#ifndef itkQuadEdgeMeshPointExplicit_h
#define itkQuadEdgeMeshPointExplicit_h

#include "ITKQuadEdgeMeshExport.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshPoint<double, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 30 times
extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshPoint<float, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 120 times
#endif //itkQuadEdgeMeshPointExplicit_h
