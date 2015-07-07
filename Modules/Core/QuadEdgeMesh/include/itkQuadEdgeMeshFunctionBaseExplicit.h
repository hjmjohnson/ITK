#ifndef itkQuadEdgeMeshFunctionBaseExplicit_h
#define itkQuadEdgeMeshFunctionBaseExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshFunctionBase<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true>*>; //Instantiated 36 times
extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshFunctionBase<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, unsigned long>; //Instantiated 15 times
#endif //itkQuadEdgeMeshFunctionBaseExplicit_h
