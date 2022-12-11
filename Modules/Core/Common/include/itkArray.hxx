/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkArray_hxx
#define itkArray_hxx

#include "itkNumericTraitsArrayPixel.h"

namespace itk
{

template <typename TValue>
Array<TValue>::Array(const Self & rhs)
  // The copy constructor creates new memory, no matter
  // the setting of let array manage memory of rhs
  : m_NumElements{ static_cast<Eigen::Index>(rhs.m_NumElements) }
  , m_LetArrayManageMemory{ true }
{
  Array_alloc_blah(this->m_NumElements);
  std::copy(rhs.begin(), rhs.end(), this->m_Data);
}

template <typename TValue>
Array<TValue>::Array(const VnlVectorType & rhs)
  // The vnl vector copy constructor creates new memory
  // no matter the setting of let array manage memory of rhs
  : m_NumElements{ static_cast<Eigen::Index>(rhs.m_NumElements) }
  , m_LetArrayManageMemory{ true }
{
  Array_alloc_blah(this->m_NumElements);
  std::copy(rhs.begin(), rhs.end(), this->m_Data);
}


template <typename TValue>
Array<TValue>::Array(SizeValueType dimension)
  // The vnl vector copy constructor creates new memory
  // no matter the setting of let array manage memory of rhs
  : m_NumElements{ static_cast<Eigen::Index>(dimension) }
  , m_LetArrayManageMemory{ true }
{
  Array_alloc_blah(m_NumElements);
}

template <typename TValue>
Array<TValue>::Array(const SizeValueType dimension, const TValue & value)
  : Array(dimension)
{
  this->Fill(value);
}

///** Constructor with user specified data */
template <typename TValue>
Array<TValue>::Array(ValueType * datain, SizeValueType sz, bool LetArrayManageMemory)
  : m_NumElements{ static_cast<Eigen::Index>(sz) }
  , m_LetArrayManageMemory{ LetArrayManageMemory }
{
  if (LetArrayManageMemory)
  {
    Array_alloc_blah(sz);
    std::copy(datain, datain + sz, m_Data);
  }
  else
  {
    m_Data = datain;
  }
}

/** Constructor with user specified const data */
template <typename TValue>
Array<TValue>::Array(const ValueType * datain, SizeValueType sz)
  // The vnl vector copy constructor creates new memory
  // no matter the setting of let array manage memory of rhs
  : m_NumElements{ static_cast<Eigen::Index>(sz) }
  , m_LetArrayManageMemory{ true }
{
  Array_alloc_blah(sz);
  std::copy(datain, datain + sz, m_Data);
}

/** Destructor */
template <typename TValue>
Array<TValue>::~Array()
{
  if (!m_LetArrayManageMemory)
  {
    Array_free_blah;
  }
}

template <typename TValue>
void
Array<TValue>::SetDataSameSize(TValue * datain, bool LetArrayManageMemory)
{
  // NOTE: Required to have same size vnl_vector< TValue >::num_elmts = sz;
  m_LetArrayManageMemory = LetArrayManageMemory;
  const auto temp_size = this->m_NumElements;
  if (m_LetArrayManageMemory)
  {
    Array_free_blah;
  }
  m_NumElements = temp_size;
  m_Data = datain;
}

template <typename TValue>
void
Array<TValue>::SetData(TValue * datain, SizeValueType sz, bool LetArrayManageMemory)
{
  if (m_LetArrayManageMemory)
  {
    Array_free_blah;
  }
  m_Data = datain;
  m_NumElements = sz;
  m_LetArrayManageMemory = LetArrayManageMemory;
}

template <typename TValue>
void
Array<TValue>::SetSize(SizeValueType sz)
{
  if (this->Size() != sz)
  {
    // Call the superclass's set_size
    this->set_size(sz);
  }
}

template <typename TValue>
auto
Array<TValue>::operator=(const Self & rhs) -> Self &
{
  if (this != &rhs)
  {
    // Set the size the same as rhs.
    // The SetSize method takes care of who is responsible
    // for memory management
    //
    this->SetSize(rhs.GetSize());
    std::copy(rhs.begin(), rhs.end(), this->m_Data);
  }
  return *this;
}

template <typename TValue>
auto
Array<TValue>::operator=(const VnlVectorType & rhs) -> Self &
{
  // Set the size the same as rhs.
  // The SetSize method takes care of who is responsible
  // for memory management
  //
  this->SetSize(rhs.size());
  std::copy(rhs.cbegin(), rhs.cend(), m_Data);
  return *this;
}
} // namespace itk

#endif
