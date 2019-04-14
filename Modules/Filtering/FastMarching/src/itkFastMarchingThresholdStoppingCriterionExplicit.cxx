#include "itkFastMarchingThresholdStoppingCriterion.h"

template class itk::FastMarchingThresholdStoppingCriterion<itk::Image<float, 3u>, itk::Image<float, 3u> >; //Instantiated 8 times
template class itk::FastMarchingThresholdStoppingCriterion<itk::Image<float, 2u>, itk::Image<float, 2u> >; //Instantiated 16 times
template class itk::FastMarchingThresholdStoppingCriterion<itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> >, itk::QuadEdgeMesh<float, 3u, itk::QuadEdgeMeshExtendedTraits<float, 3u, 2u, double, double, float, bool, bool> > >; //Instantiated 8 times
