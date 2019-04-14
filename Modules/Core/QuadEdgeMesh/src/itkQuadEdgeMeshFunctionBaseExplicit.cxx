#include "itkQuadEdgeMeshFunctionBase.h"

template class itk::QuadEdgeMeshFunctionBase<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true>*>; //Instantiated 36 times
template class itk::QuadEdgeMeshFunctionBase<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, unsigned long>; //Instantiated 15 times
