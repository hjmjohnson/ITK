#ifndef itkRegularSphereMeshSourceExplicit_h
#define itkRegularSphereMeshSourceExplicit_h

#include "ITKMeshExport.h"

extern template class ITKMesh_EXPORT itk::RegularSphereMeshSource<itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> > >; //Instantiated 9 times
extern template class ITKMesh_EXPORT itk::RegularSphereMeshSource<itk::Mesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 9 times
extern template class ITKMesh_EXPORT itk::RegularSphereMeshSource<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, float, float, double> > >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::RegularSphereMeshSource<itk::Mesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> > >; //Instantiated 18 times
#endif //itkRegularSphereMeshSourceExplicit_h
