#ifndef itkTriangleMeshToSimplexMeshFilterExplicit_h
#define itkTriangleMeshToSimplexMeshFilterExplicit_h

#include "ITKMeshExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TriangleMeshToSimplexMeshFilter<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >, itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 6 times
#endif //itkTriangleMeshToSimplexMeshFilterExplicit_h
