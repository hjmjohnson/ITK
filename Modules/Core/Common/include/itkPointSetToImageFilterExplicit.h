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
#ifndef itkPointSetToImageFilterExplicit_h
#define itkPointSetToImageFilterExplicit_h
#include "itkPointSet.h"
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<double, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<double, 3u>, 3u, 3u, float, float, itk::Vector<double, 3u> > >, itk::Image<itk::Vector<double, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<float, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<float, 3u>, 3u, 3u, float, float, itk::Vector<float, 3u> > >, itk::Image<itk::Vector<float, 3u>, 3u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<float, 1u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 2u, 2u, float, float, itk::Vector<float, 1u> > >, itk::Image<itk::Vector<float, 1u>, 2u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<float, 1u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 3u, 3u, float, float, itk::Vector<float, 1u> > >, itk::Image<itk::Vector<float, 1u>, 3u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<double, 2u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<double, 2u>, 2u, 2u, float, float, itk::Vector<double, 2u> > >, itk::Image<itk::Vector<double, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<float, 2u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<float, 2u>, 2u, 2u, float, float, itk::Vector<float, 2u> > >, itk::Image<itk::Vector<float, 2u>, 2u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<double, 1u>, 1u, itk::DefaultStaticMeshTraits<itk::Vector<double, 1u>, 1u, 1u, float, float, itk::Vector<double, 1u> > >, itk::Image<itk::Vector<double, 1u>, 1u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<float, 1u>, 4u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 4u, 4u, float, float, itk::Vector<float, 1u> > >, itk::Image<itk::Vector<float, 1u>, 4u> >;
extern template class ITKCommon_EXPORT itk::PointSetToImageFilter<itk::PointSet<itk::Vector<double, 3u>, 4u, itk::DefaultStaticMeshTraits<itk::Vector<double, 3u>, 4u, 4u, float, float, itk::Vector<double, 3u> > >, itk::Image<itk::Vector<double, 3u>, 4u> >;
#endif //itkPointSetToImageFilterExplicit_h
