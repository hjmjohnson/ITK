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
#ifndef itkPointSetExplicit_h
#define itkPointSetExplicit_h
#include "itkDefaultStaticMeshTraits.h"
#include "itkDefaultDynamicMeshTraits.h"
//exclude QuadEdgeMesh
extern template class ITKCommon_EXPORT itk::PointSet<itk::Point<double, 2u>, 2u, itk::DefaultStaticMeshTraits<double, 2u, 2u, double, double, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::CovariantVector<float, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::CovariantVector<float, 3u>, 3u, 3u, float, float, itk::CovariantVector<float, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<float, 1u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 3u, 3u, float, float, itk::Vector<float, 1u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<unsigned char, 3u, itk::DefaultStaticMeshTraits<unsigned char, 3u, 3u, float, float, unsigned char> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<float, 1u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 2u, 2u, float, float, itk::Vector<float, 1u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 3u>, 1u, itk::DefaultStaticMeshTraits<itk::Vector<double, 3u>, 1u, 1u, float, float, itk::Vector<double, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Point<float, 2u>, 3u, itk::DefaultStaticMeshTraits<itk::Point<float, 2u>, 3u, 3u, float, float, itk::Point<float, 2u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, float, float, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 2u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<double, 2u>, 2u, 2u, float, float, itk::Vector<double, 2u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Matrix<double, 3u, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Matrix<double, 3u, 3u>, 3u, 3u, float, float, itk::Matrix<double, 3u, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<unsigned short, 3u, itk::DefaultStaticMeshTraits<unsigned short, 3u, 3u, float, float, unsigned short> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<float, 2u>, 2u, itk::DefaultStaticMeshTraits<itk::Vector<float, 2u>, 2u, 2u, float, float, itk::Vector<float, 2u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<unsigned int, 2u, itk::DefaultStaticMeshTraits<unsigned int, 2u, 2u, float, float, unsigned int> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 3u>, 4u, itk::DefaultStaticMeshTraits<itk::Vector<double, 3u>, 4u, 4u, float, float, itk::Vector<double, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 3u, itk::DefaultDynamicMeshTraits<double, 3u, 3u, double, double, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<float, 3u, itk::DefaultStaticMeshTraits<float, 3u, 3u, float, float, float> >;
extern template class ITKCommon_EXPORT itk::PointSet<int, 3u, itk::DefaultStaticMeshTraits<int, 3u, 3u, float, float, int> >;
extern template class ITKCommon_EXPORT itk::PointSet<unsigned int, 3u, itk::DefaultStaticMeshTraits<unsigned int, 3u, 3u, float, float, unsigned int> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<float, 1u>, 4u, itk::DefaultStaticMeshTraits<itk::Vector<float, 1u>, 4u, 4u, float, float, itk::Vector<float, 1u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<float, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<float, 3u>, 3u, 3u, float, float, itk::Vector<float, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 3u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<double, 3u>, 3u, 3u, float, float, itk::Vector<double, 3u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, float, float, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 2u, itk::DefaultStaticMeshTraits<double, 2u, 2u, float, float, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<float, 3u, itk::DefaultDynamicMeshTraits<float, 3u, 3u, float, float, float> >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 2u, itk::DefaultDynamicMeshTraits<double, 2u, 2u, double, float, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<long, 3u, itk::DefaultStaticMeshTraits<long, 3u, 3u, float, float, long> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Point<double, 3u>, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<unsigned char, 2u, itk::DefaultStaticMeshTraits<unsigned char, 2u, 2u, float, float, unsigned char> >;
extern template class ITKCommon_EXPORT itk::PointSet<double, 3u, itk::DefaultStaticMeshTraits<double, 3u, 3u, double, double, double> >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 2u>, 3u, itk::DefaultStaticMeshTraits<itk::Vector<double, 2u>, 3u, 3u, float, float, itk::Vector<double, 2u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<itk::Vector<double, 1u>, 1u, itk::DefaultStaticMeshTraits<itk::Vector<double, 1u>, 1u, 1u, float, float, itk::Vector<double, 1u> > >;
extern template class ITKCommon_EXPORT itk::PointSet<float, 2u, itk::DefaultStaticMeshTraits<float, 2u, 2u, float, float, float> >;
#endif //itkPointSetExplicit_h
