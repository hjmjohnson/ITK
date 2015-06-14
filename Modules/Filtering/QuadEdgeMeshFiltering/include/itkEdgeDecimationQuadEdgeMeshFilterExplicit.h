#ifndef itkEdgeDecimationQuadEdgeMeshFilterExplicit_h
#define itkEdgeDecimationQuadEdgeMeshFilterExplicit_h

#include "ITKQuadEdgeMeshFilteringExport.h"

#include "itkQuadEdgeMeshDecimationCriteria.h"

extern template class ITKQuadEdgeMeshFiltering_EXPORT itk::EdgeDecimationQuadEdgeMeshFilter<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, itk::NumberOfFacesCriterion<itk::QuadEdgeMesh<double, 3u, itk::QuadEdgeMeshTraits<double, 3u, bool, bool, float, float> >, unsigned long, double, itk::MinPriorityQueueElementWrapper<itk::GeometricalQuadEdge<unsigned long, unsigned long, bool, bool, true>*, std::pair<bool, double>, unsigned long> > >; //Instantiated 6 times
#endif //itkEdgeDecimationQuadEdgeMeshFilterExplicit_h
