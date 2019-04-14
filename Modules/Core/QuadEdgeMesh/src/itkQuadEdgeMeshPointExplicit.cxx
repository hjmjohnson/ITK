#include "itkQuadEdgeMeshPoint.h"

template class itk::QuadEdgeMeshPoint<double, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 30 times
template class itk::QuadEdgeMeshPoint<float, 3u, itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true> >; //Instantiated 120 times
