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
#ifndef itkArrayMemoryReference_hxx
#define itkArrayMemoryReference_hxx

#include "itkNumericTraitsArrayPixel.h"

namespace itk
{
/** Default constructor */
template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference()
  : vnl_vector<TValue>()
{}

/** Copy constructor */
template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference(const Self & rhs)
  : vnl_vector<TValue>(rhs)
// The copy constructor creates new memory, no matter
// the setting of let array manage memory of rhs
{}

template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference(const VnlVectorType & rhs)
  : vnl_vector<TValue>(rhs)
// The vnl vector copy constructor creates new memory
// no matter the setting of let array manage memory of rhs
{}

/** Constructor with size */
template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference(SizeValueType dimension)
  : vnl_vector<TValue>(dimension)
// The vnl vector copy constructor creates new memory
// no matter the setting of let array manage memory of rhs
{}

/** Constructor with size and initial value for each element. */
template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference(const SizeValueType dimension, const TValue & value)
  : vnl_vector<TValue>(dimension, value)
{}

///** Constructor with user specified data */
// template <typename TValue>
// Array<TValue>::Array(ValueType * datain, SizeValueType sz, bool LetArrayManageMemory)
//  : m_LetArrayManageMemory(LetArrayManageMemory)
//{
//  vnl_vector<TValue>::data = datain;
//  vnl_vector<TValue>::num_elmts = sz;
//}

/** Constructor with user specified const data */
template <typename TValue>
ArrayMemoryReference<TValue>::ArrayMemoryReference(const ValueType * datain, SizeValueType sz)
  : vnl_vector<TValue>(datain, sz)
// The vnl vector copy constructor creates new memory
// no matter the setting of let array manage memory of rhs
{}

/** Destructor */
template <typename TValue>
ArrayMemoryReference<TValue>::~ArrayMemoryReference()
{
  if (!m_LetArrayManageMemory)
  {
    assert(0 == 1);
    // vnl_vector<TValue>::data = nullptr;
  }
}

// template <typename TValue>
// void
// Array<TValue>::SetDataSameSize(TValue * datain, bool LetArrayManageMemory)
//{
//  if (m_LetArrayManageMemory)
//  {
//    vnl_vector<TValue>::destroy();
//  }
//  assert(0==1);
//  // HACK vnl_vector<TValue>::data = datain;
//  // NOTE: Required to have same size vnl_vector< TValue >::num_elmts = sz;
//  m_LetArrayManageMemory = LetArrayManageMemory;
//}
//
// template <typename TValue>
// void
// Array<TValue>::SetData(TValue * datain, SizeValueType sz, bool LetArrayManageMemory)
//{
//  if (m_LetArrayManageMemory)
//  {
//    vnl_vector<TValue>::destroy();
//  }
//  assert(0==1);
//  // HACK vnl_vector<TValue>::data = datain;
//  // HACK vnl_vector<TValue>::num_elmts = sz;
//  m_LetArrayManageMemory = LetArrayManageMemory;
//}

template <typename TValue>
void
ArrayMemoryReference<TValue>::SetSize(SizeValueType sz)
{
  if (this->size() != sz)
  {
    // If the array doesn't own the data we do not want to erase it
    // on a resize
    if (!m_LetArrayManageMemory)
    {
      // HACK vnl_vector<TValue>::data() = nullptr;
    }

    // Call the superclass's set_size
    this->set_size(sz);

    // Size we have allocated new data we need to take
    // responsibility for deleting it
    m_LetArrayManageMemory = true;
  }
}

template <typename TValue>
auto
ArrayMemoryReference<TValue>::operator=(const Self & rhs) -> Self &
{
  if (this != &rhs)
  {

    // Set the size the same as rhs.
    // The SetSize method takes care of who is responsible
    // for memory management
    //
    this->SetSize(rhs.GetSize());

    // Call the superclass implementation
    this->VnlVectorType::operator=(rhs);
  }
  return *this;
}

template <typename TValue>
auto
ArrayMemoryReference<TValue>::operator=(const VnlVectorType & rhs) -> Self &
{
  if (this != &rhs)
  {

    // Set the size the same as rhs.
    // The SetSize method takes care of who is responsible
    // for memory management
    //
    this->SetSize(rhs.size());

    // Call the superclass implementation
    this->VnlVectorType::operator=(rhs);
  }
  return *this;
}
} // namespace itk

#endif
