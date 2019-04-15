#ifndef itkTriangleMeshToBinaryImageFilterExplicit_h
#define itkTriangleMeshToBinaryImageFilterExplicit_h

#include "ITKMeshExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::TriangleMeshToBinaryImageFilter<itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> >, itk::Image<unsigned char, 3u> >; //Instantiated 6 times
#endif //itkTriangleMeshToBinaryImageFilterExplicit_h
