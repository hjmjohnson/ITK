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
#ifndef itkDataObjectDecoratorExplicit_h
#define itkDataObjectDecoratorExplicit_h
#include "itkVectorContainer.h"
//exclude GaussianSmoothingOnUpdateDisplacementFieldTransform
//exclude Transform
//exclude BSplineTransform
//exclude AffineTransform
//exclude DisplacementFieldTransform
//exclude FunctionBase
extern template class ITKCommon_EXPORT itk::DataObjectDecorator<itk::VectorContainer<unsigned char, double> >;
#endif //itkDataObjectDecoratorExplicit_h
