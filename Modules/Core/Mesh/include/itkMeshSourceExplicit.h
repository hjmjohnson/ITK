#ifndef itkMeshSourceExplicit_h
#define itkMeshSourceExplicit_h

#include "ITKMeshExport.h"

#include "itkSimplexMesh.h"

extern template class ITKMesh_EXPORT itk::MeshSource<itk::PointSet<long, 3u, itk::DefaultStaticMeshTraits<long, 3u, 3u, float, float, long> > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 9 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, float, float, double> > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::PointSet<itk::Matrix<double, 3u, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Matrix<double, 3u, 3u>, 3u, 3u, float, float, itk::Matrix<double, 3u, 3u> > > >; //Instantiated 9 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> > >; //Instantiated 30 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<int, 3u, itk::DefaultStaticMeshTraits<int, 3u, 3u, float, float, int> > >; //Instantiated 12 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<itk::Point<float, 2u>, 3u, itk::DefaultStaticMeshTraits<itk::Point<float, 2u>, 3u, 3u, float, float, itk::Point<float, 2u> > > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::PointSet<itk::Vector<float, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<float, 3u>, 3u, 3u, float, float, itk::Vector<float, 3u> > > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::MeshSource<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, float, float, double> > >; //Instantiated 18 times
#endif //itkMeshSourceExplicit_h
