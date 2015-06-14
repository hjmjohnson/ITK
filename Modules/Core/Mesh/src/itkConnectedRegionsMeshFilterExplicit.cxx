#include "itkConnectedRegionsMeshFilter.h"

template class ITKMesh_EXPORT itk::ConnectedRegionsMeshFilter<itk::Mesh<int, 3u, itk::DefaultStaticMeshTraits<int, 3u, 3u, float, float, int> >, itk::Mesh<int, 3u, itk::DefaultStaticMeshTraits<int, 3u, 3u, float, float, int> > >; //Instantiated 3 times
template class ITKMesh_EXPORT itk::ConnectedRegionsMeshFilter<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, float, float, double> >, itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, float, float, double> > >; //Instantiated 3 times
