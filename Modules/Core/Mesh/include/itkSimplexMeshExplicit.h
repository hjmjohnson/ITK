#ifndef itkSimplexMeshExplicit_h
#define itkSimplexMeshExplicit_h

#include "ITKMeshExport.h"

extern template class ITKMesh_EXPORT itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 6 times
extern template class ITKMesh_EXPORT itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 21 times
#endif //itkSimplexMeshExplicit_h
