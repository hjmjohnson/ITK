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
#ifndef itkFixedCenterOfRotationAffineTransform_hxx
#define itkFixedCenterOfRotationAffineTransform_hxx

#include "itkNumericTraits.h"
#include "itkFixedCenterOfRotationAffineTransform.h"
#include "itkAffineTransform.h"
#include "vnl/algo/vnl_matrix_inverse.h"

namespace itk
{
/** Constructor with default arguments */
template< typename TScalar, unsigned int NDimensions, typename TFixedParametersValueType >
FixedCenterOfRotationAffineTransform< TScalar, NDimensions, TFixedParametersValueType >::FixedCenterOfRotationAffineTransform():
  Superclass(ParametersDimension)
{}

template< typename TScalar, unsigned int NDimensions, typename TFixedParametersValueType >
FixedCenterOfRotationAffineTransform< TScalar, NDimensions, TFixedParametersValueType >::FixedCenterOfRotationAffineTransform(
  unsigned int outputSpaceDims,
  unsigned int
  paramsDims):
  Superclass(outputSpaceDims, paramsDims)
{}

template< typename TScalar, unsigned int NDimensions, typename TFixedParametersValueType >
FixedCenterOfRotationAffineTransform< TScalar, NDimensions, TFixedParametersValueType >::FixedCenterOfRotationAffineTransform(
  const MatrixType & matrix,
  const
  OutputVectorType & offset):
  Superclass(matrix, offset)
{}

/** Destructor */
template< typename TScalar, unsigned int NDimensions, typename TFixedParametersValueType >
FixedCenterOfRotationAffineTransform< TScalar, NDimensions, TFixedParametersValueType >::
~FixedCenterOfRotationAffineTransform()
{
}
} // namespace

#endif
