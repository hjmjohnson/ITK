#include "itkSymmetricEigenAnalysis.h"

template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<double, 4u, 4u>, vnl_vector<double>, vnl_matrix<double> >; //Instantiated 6 times
template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<float, 3u, 3u>, itk::FixedArray<float, 3u>, itk::Matrix<float, 3u, 3u> >; //Instantiated 20 times
template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<double, 3u, 3u>, itk::FixedArray<double, 3u>, itk::Matrix<double, 3u, 3u> >; //Instantiated 214 times
