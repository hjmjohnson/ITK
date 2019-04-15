#ifndef itkQuadEdgeMeshZipMeshFunctionExplicit_h
#define itkQuadEdgeMeshZipMeshFunctionExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::QuadEdgeMeshZipMeshFunction<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 15 times
#endif //itkQuadEdgeMeshZipMeshFunctionExplicit_h
