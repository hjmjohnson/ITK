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
#ifndef itkLaplacianOperatorExplicit_h
#define itkLaplacianOperatorExplicit_h
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianOperator<float, 2u, itk::NeighborhoodAllocator<float> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianOperator<double, 3u, itk::NeighborhoodAllocator<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianOperator<double, 2u, itk::NeighborhoodAllocator<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianOperator<double, 4u, itk::NeighborhoodAllocator<double> >;
ITK_TEMPLATE_INSTANTIATION_EXTERN template class itk::LaplacianOperator<float, 3u, itk::NeighborhoodAllocator<float> >;
#endif //itkLaplacianOperatorExplicit_h
