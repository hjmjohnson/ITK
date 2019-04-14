#include "itkSimplexMesh.h"

template class itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 6 times
template class itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 21 times
