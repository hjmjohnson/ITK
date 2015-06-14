#include "itkTriangleMeshToSimplexMeshFilter.h"

template class ITKMesh_EXPORT itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
template class ITKMesh_EXPORT itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 6 times
