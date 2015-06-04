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
#ifndef itkTransformFileWriter_hxx
#define itkTransformFileWriter_hxx

#include "itkTransformFileWriter.h"
#include "itkTransformFactoryBase.h"
#include "itkTransformIOFactory.h"
#include "itkCompositeTransformIOHelper.h"

namespace itk
{


template<typename ScalarType, typename TFixedParameterValueType>
TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::TransformFileWriterTemplate() :
  m_FileName(""),
  m_AppendMode(false)
{
  TransformFactoryBase::RegisterDefaultTransforms();
}

template<typename ScalarType, typename TFixedParameterValueType>
TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::~TransformFileWriterTemplate()
{
}

/** Set the writer to append to the specified file */
template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::SetAppendOn()
{
  this->SetAppendMode(true);
}

/** Set the writer to overwrite the specified file - This is the
* default mode. */
template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::SetAppendOff()
{
  this->SetAppendMode(false);
}

/** Set the writer mode (append/overwrite). */
template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::SetAppendMode(bool mode)
{
  this->m_AppendMode = mode;
}

/** Get the writer mode. */
template<typename ScalarType, typename TFixedParameterValueType>
bool TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::GetAppendMode()
{
  return ( this->m_AppendMode );
}

template<>
void
TransformFileWriterTemplate<double>
::PushBackTransformList(const Object *transObj);

template<>
void
TransformFileWriterTemplate<float>
::PushBackTransformList(const Object *transObj);

/** Set the input transform and reinitialize the list of transforms */
template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::SetInput(const Object *transform)
{
  m_TransformList.clear();
  this->PushBackTransformList(transform);
}

template<typename ScalarType, typename TFixedParameterValueType>
const typename TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>::TransformType *
TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::GetInput()
{
  ConstTransformPointer res = *(m_TransformList.begin());
  return res.GetPointer();
}

/** Add a transform to be written */
template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::AddTransform(const Object *transform)
{
  /* Check for a CompositeTransform.
   * The convention is that there should be one, and it should
   * be the first transform in the file
   */
  const std::string transformName = transform->GetNameOfClass();
  if( transformName.find("CompositeTransform") != std::string::npos )
    {
    if(this->m_TransformList.size() > 0)
      {
      itkExceptionMacro("Can only write a transform of type CompositeTransform "
                        "as the first transform in the file.");
      }
    }

  this->PushBackTransformList(transform);
}

template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::Update()
{
  if ( m_FileName == "" )
    {
    itkExceptionMacro ("No file name given");
    }

  if( m_TransformIO.IsNull() )
    {
    typedef TransformIOFactoryTemplate< ScalarType, TFixedParameterValueType > TransformFactoryIOType;
    m_TransformIO = TransformFactoryIOType::CreateTransformIO( m_FileName.c_str(), WriteMode );
    if ( m_TransformIO.IsNull() )
      {
      itkExceptionMacro("Can't Create IO object for file " << m_FileName);
      }
    }

  m_TransformIO->SetAppendMode(this->m_AppendMode);
  m_TransformIO->SetFileName(this->m_FileName);
  m_TransformIO->SetTransformList(this->m_TransformList);
  m_TransformIO->Write();
}

template<typename ScalarType, typename TFixedParameterValueType>
void TransformFileWriterTemplate<ScalarType, TFixedParameterValueType>
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "FileName: " << m_FileName << std::endl;
}

} // namespace itk

#endif
