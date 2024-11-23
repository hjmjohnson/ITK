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

#include "itkNumericSeriesFileNames.h"
#include "itkMakeUniqueForOverwrite.h"
#include <cstdio>

namespace itk
{
NumericSeriesFileNames::NumericSeriesFileNames()
  : m_SeriesFormat("%d")
{}

const std::vector<std::string> &
NumericSeriesFileNames::GetFileNames()
{
  // validate the indices
  if (m_StartIndex > m_EndIndex)
  {
    itkExceptionMacro("StartIndex " << m_StartIndex << " is greater than EndIndex " << m_EndIndex);
  }
  if (m_IncrementIndex == 0)
  {
    itkExceptionMacro("IncrementIndex is zero.");
  }

  // clear the file names vector
  m_FileNames.clear();

  for (SizeValueType i = m_StartIndex; i <= m_EndIndex; i += m_IncrementIndex)
  {
    char c[10000];
    // snprintf returns the length of the string generated by the
    // snprintf operation (excluding the trailing null),
    // so we can use a 'dry run' to size the buffer.
    ITK_GCC_PRAGMA_PUSH
    ITK_GCC_SUPPRESS_Wformat_nonliteral
    OffsetValueType nchars = snprintf(c, sizeof(c), m_SeriesFormat.c_str(), i);
    ITK_GCC_PRAGMA_POP
    if (nchars <= -1)
    {
      // broken snprintf reports overflow with -1
      nchars = static_cast<OffsetValueType>(m_SeriesFormat.size() + sizeof(c)); // enough room for path +
                                                                                // absurdly long integer string.
    }
    OffsetValueType const bufflen = nchars + 1;
    const auto            temp = make_unique_for_overwrite<char[]>(bufflen);
    ITK_GCC_PRAGMA_PUSH
    ITK_GCC_SUPPRESS_Wformat_nonliteral
    OffsetValueType const result = snprintf(temp.get(), bufflen, m_SeriesFormat.c_str(), i);
    ITK_GCC_PRAGMA_POP
    if (result < 0 || result >= bufflen)
    {
      std::stringstream message_cache;
      message_cache << "The filename is too long for temp buffer."
                    << " Truncated form: " << temp.get() << '.' << std::endl
                    << "nchars: " << nchars << " bufflen: " << bufflen << " result: " << result;
      itkExceptionMacro(<< message_cache.str());
    }
    std::string const fileName(temp.get());
    m_FileNames.push_back(fileName);
  }
  return m_FileNames;
}

void
NumericSeriesFileNames::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "StartIndex: " << m_StartIndex << std::endl;
  os << indent << "EndIndex: " << m_EndIndex << std::endl;
  os << indent << "IncrementIndex: " << m_IncrementIndex << std::endl;
  os << indent << "SeriesFormat: " << m_SeriesFormat << std::endl;

  for (unsigned int i = 0; i < m_FileNames.size(); ++i)
  {
    os << indent << "FileNames[" << i << "]: " << m_FileNames[i] << std::endl;
  }
}
} // namespace itk
