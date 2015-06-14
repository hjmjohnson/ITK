/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkSymmetricEigenAnalysisExplicit_h
#define itkSymmetricEigenAnalysisExplicit_h
#include "itkMatrix.h"
extern template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<double, 4u, 4u>, vnl_vector<double>, vnl_matrix<double> >;
extern template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<float, 3u, 3u>, itk::FixedArray<float, 3u>, itk::Matrix<float, 3u, 3u> >;
extern template class ITKCommon_EXPORT itk::SymmetricEigenAnalysis<itk::Matrix<double, 3u, 3u>, itk::FixedArray<double, 3u>, itk::Matrix<double, 3u, 3u> >;
#endif //itkSymmetricEigenAnalysisExplicit_h
