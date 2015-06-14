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
#ifndef itkFunctionBaseExplicit_h
#define itkFunctionBaseExplicit_h
#include "itkPoint.h"
#include "itkContinuousIndex.h"
#include "itkArray.h"
#include "itkVariableLengthVector.h"
#include "itkCovariantVector.h"
#include "itkSymmetricSecondRankTensor.h"
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 2u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::ContinuousIndex<float, 2u>, itk::Array<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Array<double>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<short>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<double, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, vnl_matrix<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, bool>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, itk::FixedArray<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<double, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::ContinuousIndex<float, 3u>, itk::Array<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<unsigned short>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 1u>, itk::Vector<double, 1u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<unsigned int>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<unsigned char>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, itk::VariableLengthVector<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 2u>, itk::CovariantVector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<int>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 4u>, itk::Vector<double, 4u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<unsigned int, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, itk::CovariantVector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<float>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::ContinuousIndex<double, 3u>, itk::Array<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, itk::CovariantVector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<double>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 4u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<float, float>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, vnl_matrix<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 1u>, bool>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, itk::VariableLengthVector<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 2u>, itk::FixedArray<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<signed char, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 4u>, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<int, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<unsigned short, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<float, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<unsigned char, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 4u>, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::VariableLengthVector<signed char>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::FixedArray<short, 1u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, bool>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, itk::Vector<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::ContinuousIndex<double, 2u>, itk::Array<double> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, bool>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 2u>, itk::Vector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, itk::CovariantVector<double, 2u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 4u>, itk::Vector<double, 4u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 3u>, itk::SymmetricSecondRankTensor<double, 3u> >;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 2u>, bool>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 2u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<double, 4u>, double>;
extern template class ITKCommon_EXPORT itk::FunctionBase<itk::Point<float, 3u>, itk::Vector<double, 2u> >;
#endif //itkFunctionBaseExplicit_h
