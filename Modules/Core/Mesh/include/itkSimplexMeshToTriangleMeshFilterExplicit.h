#ifndef itkSimplexMeshToTriangleMeshFilterExplicit_h
#define itkSimplexMeshToTriangleMeshFilterExplicit_h

#include "ITKMeshExport.h"

extern template class ITKMesh_EXPORT itk::SimplexMeshToTriangleMeshFilter<itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >, itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 6 times
#endif //itkSimplexMeshToTriangleMeshFilterExplicit_h
