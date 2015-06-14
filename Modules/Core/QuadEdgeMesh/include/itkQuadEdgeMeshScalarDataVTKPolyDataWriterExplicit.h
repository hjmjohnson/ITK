#ifndef itkQuadEdgeMeshScalarDataVTKPolyDataWriterExplicit_h
#define itkQuadEdgeMeshScalarDataVTKPolyDataWriterExplicit_h

#include "ITKQuadEdgeMeshExport.h"

#include "itkQuadEdgeMesh.h"

extern template class ITKQuadEdgeMesh_EXPORT itk::QuadEdgeMeshScalarDataVTKPolyDataWriter<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshTraits<float, 3u, bool, bool, float, float> > >; //Instantiated 3 times
#endif //itkQuadEdgeMeshScalarDataVTKPolyDataWriterExplicit_h
