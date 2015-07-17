#include "itkFEMSpatialObjectReader.h"

template class ITKFEM_EXPORT itk::FEMSpatialObjectReader<3u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >; //Instantiated 12 times
template class ITKFEM_EXPORT itk::FEMSpatialObjectReader<2u, unsigned char, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >; //Instantiated 34 times
