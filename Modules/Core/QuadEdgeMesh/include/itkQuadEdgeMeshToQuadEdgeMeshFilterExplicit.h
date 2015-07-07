#ifndef itkQuadEdgeMeshToQuadEdgeMeshFilterExplicit_h
#define itkQuadEdgeMeshToQuadEdgeMeshFilterExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshToQuadEdgeMeshFilter<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshTraits<float, 3u, bool, bool, float, float> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshTraits<float, 3u, bool, bool, float, float> > >; //Instantiated 6 times
extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshToQuadEdgeMeshFilter<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshExtendedTraits<double, 3u, 2u, double, double, double, bool, bool> >, itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshExtendedTraits<double, 3u, 2u, double, double, double, bool, bool> > >; //Instantiated 12 times
extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshToQuadEdgeMeshFilter<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> > >; //Instantiated 18 times
extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshToQuadEdgeMeshFilter<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> > >; //Instantiated 15 times
#endif //itkQuadEdgeMeshToQuadEdgeMeshFilterExplicit_h
