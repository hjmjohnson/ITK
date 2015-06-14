#ifndef itkVTKPolyDataWriterExplicit_h
#define itkVTKPolyDataWriterExplicit_h

#include "ITKMeshExport.h"

extern template class ITKMesh_EXPORT itk::VTKPolyDataWriter<itk::Mesh<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> > >; //Instantiated 6 times
#endif //itkVTKPolyDataWriterExplicit_h
