#ifndef itkImageToMeshFilterExplicit_h
#define itkImageToMeshFilterExplicit_h

#include "ITKMeshExport.h"

#include "itkImage.h"

ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::ImageToMeshFilter<itk::Image<unsigned char, 3u>, itk::PointSet<itk::Matrix<double, 3u, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Matrix<double, 3u, 3u>, 3u, 3u, float, float, itk::Matrix<double, 3u, 3u> > > >; //Instantiated 6 times
#endif //itkImageToMeshFilterExplicit_h
