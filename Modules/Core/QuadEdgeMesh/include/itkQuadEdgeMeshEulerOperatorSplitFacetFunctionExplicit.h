#ifndef itkQuadEdgeMeshEulerOperatorSplitFacetFunctionExplicit_h
#define itkQuadEdgeMeshEulerOperatorSplitFacetFunctionExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"
#include "itkGeometricalQuadEdge.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshEulerOperatorSplitFacetFunction<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 9 times
#endif //itkQuadEdgeMeshEulerOperatorSplitFacetFunctionExplicit_h
