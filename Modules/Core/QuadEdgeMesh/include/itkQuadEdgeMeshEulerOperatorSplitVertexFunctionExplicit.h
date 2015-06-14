#ifndef itkQuadEdgeMeshEulerOperatorSplitVertexFunctionExplicit_h
#define itkQuadEdgeMeshEulerOperatorSplitVertexFunctionExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"
#include "itkGeometricalQuadEdge.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshEulerOperatorSplitVertexFunction<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 6 times
#endif //itkQuadEdgeMeshEulerOperatorSplitVertexFunctionExplicit_h
