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
#ifndef itkCorrespondenceDataStructureIterator_hxx
#define itkCorrespondenceDataStructureIterator_hxx


namespace itk
{

template <typename TStructureType>
CorrespondenceDataStructureIterator<TStructureType>::CorrespondenceDataStructureIterator(TStructureType * StructurePtr)
  : m_Structure(StructurePtr)
  , m_CorrespondingListPointer(&(*m_SecondaryListIterator))
  , m_NodeListPointer(StructurePtr->m_NodeList)
  , m_SecondaryListPointer(&(*m_NodeListIterator))
{
  m_NodeListIterator = m_NodeListPointer->begin();
  m_SecondaryListIterator = m_SecondaryListPointer->begin();
  m_CorrespondingListIterator = m_CorrespondingListPointer->begin();
}

/** Used to verify that the iterator is at the end of the data structure. */
template <typename TStructureType>
bool
CorrespondenceDataStructureIterator<TStructureType>::IsAtEnd() const
{
  return m_IsAtEnd;
}

template <typename TStructureType>
void
CorrespondenceDataStructureIterator<TStructureType>::GoToNext()
{
  ++m_CorrespondingListIterator;

  if (m_CorrespondingListIterator == m_CorrespondingListPointer->end())
  {
    this->GoToNextBaseGroup();
  }
}

template <typename TStructureType>
void
CorrespondenceDataStructureIterator<TStructureType>::GoToNextBaseGroup()
{
  ++m_SecondaryListIterator;
  if (m_SecondaryListIterator != m_SecondaryListPointer->end())
  {
    m_CorrespondingListPointer = &(*m_SecondaryListIterator);
    m_CorrespondingListIterator = m_CorrespondingListPointer->begin();
  }
  else if (m_SecondaryListIterator == m_SecondaryListPointer->end())
  {
    ++m_NodeListIterator;

    if (m_NodeListIterator != m_NodeListPointer->end())
    {
      m_SecondaryListPointer = &(*m_NodeListIterator);
      m_SecondaryListIterator = m_SecondaryListPointer->begin();

      m_CorrespondingListPointer = &(*m_SecondaryListIterator);
      m_CorrespondingListIterator = m_CorrespondingListPointer->begin();
    }
    else if (m_NodeListIterator == m_NodeListPointer->end())
    {
      m_IsAtEnd = true;
    }
  }
}

template <typename TStructureType>
void
CorrespondenceDataStructureIterator<TStructureType>::Reset()
{
  m_IsAtEnd = false;

  m_NodeListPointer = m_Structure->m_NodeList;
  m_NodeListIterator = m_NodeListPointer->begin();

  m_SecondaryListPointer = &(*m_NodeListIterator);
  m_SecondaryListIterator = m_SecondaryListPointer->begin();

  m_CorrespondingListPointer = &(*m_SecondaryListIterator);
  m_CorrespondingListIterator = m_CorrespondingListPointer->begin();
}
} // end namespace itk

#endif
