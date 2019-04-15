#ifndef itkSimplexMeshExplicit_h
#define itkSimplexMeshExplicit_h

#include "ITKMeshExport.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimplexMesh<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 6 times
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::SimplexMesh<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >; //Instantiated 21 times
#endif //itkSimplexMeshExplicit_h
