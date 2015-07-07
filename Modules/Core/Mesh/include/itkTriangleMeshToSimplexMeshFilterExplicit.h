#ifndef itkTriangleMeshToSimplexMeshFilterExplicit_h
#define itkTriangleMeshToSimplexMeshFilterExplicit_h

#include "ITKMeshExport.h"

extern template class ITKMesh_EXPORT itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
extern template class ITKMesh_EXPORT itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 6 times
#endif //itkTriangleMeshToSimplexMeshFilterExplicit_h
