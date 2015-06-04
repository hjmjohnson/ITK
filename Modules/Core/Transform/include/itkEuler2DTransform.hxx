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
#ifndef itkEuler2DTransform_hxx
#define itkEuler2DTransform_hxx

#include "itkEuler2DTransform.h"

namespace itk
{
// Constructor with default arguments
template< typename TScalar, typename TFixedParametersValueType >
Euler2DTransform< TScalar, TFixedParametersValueType >
::Euler2DTransform():
  Superclass(ParametersDimension)
{}

// Constructor with arguments
template< typename TScalar, typename TFixedParametersValueType >
Euler2DTransform< TScalar, TFixedParametersValueType >::Euler2DTransform(unsigned int parametersDimension):
  Superclass(parametersDimension)
{}

// Create and return an inverse transformation
template< typename TScalar, typename TFixedParametersValueType >
void
Euler2DTransform< TScalar, TFixedParametersValueType >::CloneInverseTo(Pointer & result) const
{
  result = New();
  this->GetInverse( result.GetPointer() );
}

// return an inverse transformation
template< typename TScalar, typename TFixedParametersValueType >
bool
Euler2DTransform< TScalar, TFixedParametersValueType >::GetInverse(Self *inverse) const
{
  if ( !inverse )
    {
    return false;
    }

  inverse->SetFixedParameters( this->GetFixedParameters() );
  inverse->SetCenter( this->GetCenter() );  // inverse have the same center
  inverse->SetAngle( -this->GetAngle() );
  inverse->SetTranslation( -( this->GetInverseMatrix() * this->GetTranslation() ) );

  return true;
}

// Return an inverse of this transform
template< typename TScalar, typename TFixedParametersValueType >
typename Euler2DTransform< TScalar, TFixedParametersValueType >::InverseTransformBasePointer
Euler2DTransform< TScalar, TFixedParametersValueType >
::GetInverseTransform() const
{
  Pointer inv = New();

  return GetInverse(inv) ? inv.GetPointer() : ITK_NULLPTR;
}

// Create and return an inverse transformation
template< typename TScalar, typename TFixedParametersValueType >
void
Euler2DTransform< TScalar, TFixedParametersValueType >::CloneTo(Pointer & result) const
{
  result = New();
  result->SetCenter( this->GetCenter() );
  result->SetAngle( this->GetAngle() );
  result->SetTranslation( this->GetTranslation() );
}

// Print self
template< typename TScalar, typename TFixedParametersValueType >
void
Euler2DTransform< TScalar, TFixedParametersValueType >::PrintSelf(std::ostream & os, Indent indent) const
{
  this->Superclass::PrintSelf(os, indent);
}
} // namespace

#endif
