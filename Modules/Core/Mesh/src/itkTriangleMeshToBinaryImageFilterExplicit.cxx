#include "itkTriangleMeshToBinaryImageFilter.h"

template class ITKMesh_EXPORT itk::TriangleMeshToBinaryImageFilter<itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> >, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
