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
#ifndef itkArray_h
#define itkArray_h

#include "itkMacro.h"

#include "vxl_version.h"
#include "vnl/vnl_vector.h"

//--------------------------------------------------------------------------------
// This macro allocates the dynamic storage used by a vnl_vector.
#define Array_alloc_blah(size_elements)                                                                              \
  do                                                                                                                 \
  {                                       /* Macro needs to be a single statement to allow semicolon at macro end */ \
    assert(this->m_LetArrayManageMemory); /*Resizing memory requires management rights */                            \
    this->m_NumElements = (size_elements);                                                                           \
    this->m_Data = (size_elements > 0) ? new TValue[size_elements] : nullptr;                                        \
  } while (false)

// This macro deallocates the dynamic storage used by a vnl_vector.
#define Array_free_blah                                                        \
  do                                                                           \
  { /* Macro needs to be a single statement to allow semicolon at macro end */ \
    if (this->m_LetArrayManageMemory)                                          \
    {                                                                          \
      if (this->m_Data)                                                        \
      {                                                                        \
        delete[] this->m_Data;                                                 \
      }                                                                        \
    }                                                                          \
    this->m_Data = nullptr;                                                    \
    this->m_NumElements = 0;                                                   \
    this->m_LetArrayManageMemory = true;                                       \
  } while (false)

namespace itk
{
/**
 * \class Array
 *  \brief Array class with size defined at construction time.
 *
 * This class derives from the vnl_vector<> class.
 * Its size is assigned at construction time (run time) and can
 * not be changed afterwards except by using assignment to another
 * Array.
 *
 * The class is templated over the type of the elements.
 *
 * Template parameters for class Array:
 *
 * - TValue = Element type stored at each location in the array.
 *
 * \ingroup DataRepresentation
 * \ingroup ITKCommon
 */
template <typename TValue>
class ITK_TEMPLATE_EXPORT Array
{
public:
  /** The element type stored at each location in the Array. */
  using ValueType = TValue;
  using Self = Array;
  using VnlVectorType = vnl_vector<TValue>;
  using SizeValueType = typename vnl_vector<TValue>::size_type;

public:
  /** Default constructor. It is created with an empty array
   *  it has to be allocated later by assignment */
  Array() = default;

  /** Copy constructor.  Uses VNL copy constructor with correct
   *  setting for memory management. */
  Array(const Array &);

  /** Construct from a VnlVectorType */
  explicit Array(const VnlVectorType &);

  /** Constructor with size. Size can only be changed by assignment.
   * \note This constructor may not initialize its elements.
   */
  explicit Array(SizeValueType dimension);

  /** Constructor with size and initial value for each element. */
  explicit Array(SizeValueType dimension, const ValueType & value);

  /** Constructor that initializes array with contents from a user supplied
   * buffer. The pointer to the buffer and the length is specified. By default,
   * the array does not manage the memory of the buffer. It merely points to
   * that location and it is the user's responsibility to delete it.
   * If "LetArrayManageMemory" is true, then this class will free the
   * memory when this object is destroyed. */
  Array(ValueType * datain, SizeValueType sz, bool LetArrayManageMemory = false);

  /** Constructor that initializes array with contents from a user supplied
   * const buffer. The pointer to the buffer and the length is specified. By default,
   * the array does a deep copy of the const pointer data, so the array class also
   * manages memory. */
  Array(const ValueType * datain, SizeValueType sz);


  /** Constructor to initialize an array from another of any data type */
  template <typename TArrayValue>
  Array(const Array<TArrayValue> & r)
  {
    this->SetSize(r.GetSize());
    for (SizeValueType i = 0; i < r.GetSize(); ++i)
    {
      this->operator[](i) = static_cast<TValue>(r[i]);
    }
  }

  /** Set all the elements of the array to the specified value */
  void
  Fill(TValue const & v)
  {
    std::fill(this->begin(), this->end(), v);
  }

  /** Copy operator */
  Self &
  operator=(const Self & rhs);

  Self &
  operator=(const VnlVectorType & rhs);

  bool
  operator==(const Self & rhs) const
  {
    if (this == &rhs) // same object => equal.
    {
      return true;
    }
    if (this->Size() != rhs.Size()) // Size different ?
    {
      return false; // Then not equal.
    }
    return std::equal(this->begin(), this->end(), rhs.begin());
  }

  bool
  operator!=(const Self & rhs) const
  {
    return !operator==(rhs);
  }

  /** Return the number of elements in the Array  */
  SizeValueType
  Size() const
  {
    return static_cast<SizeValueType>(this->m_NumElements);
  }

  // vnl_exposure funciton #if !defined(ITK_LEGACY_REMOVE)
  SizeValueType
  size() const
  {
    return this->Size();
  };
  // #endif

  unsigned int
  GetNumberOfElements() const
  {
    return static_cast<unsigned int>(this->Size());
  }

  /** Get one element */
  const TValue &
  GetElement(SizeValueType i) const
  {
    return this->operator[](i);
  }

  /** Set one element */
  void
  SetElement(SizeValueType i, const TValue & value)
  {
    this->operator[](i) = value;
  }

  /** Destructively set the size to that given.  Will lose data.  */
  void
  SetSize(SizeValueType sz);

  SizeValueType
  GetSize() const
  {
    return static_cast<SizeValueType>(this->Size());
  }

  /** Set the pointer from which the data is imported.
   * If "LetArrayManageMemory" is false, then the application retains
   * the responsibility of freeing the memory for this data.  If
   * "LetArrayManageMemory" is true, then this class will free the
   * memory when this object is destroyed.
   * NOTE: This signature requires that internal array is being
   *       replaced by data array of exactly the same size
   */
  void
  SetDataSameSize(TValue * datain, bool LetArrayManageMemory = false);

  /** Similar to the previous method. In the above method, the size must be
   * separately set prior to using user-supplied data. This introduces an
   * unnecessary allocation step to be performed. This method avoids it
   * and should be used to import data wherever possible to avoid this.
   * Set the pointer from which the data is imported.
   * If "LetArrayManageMemory" is false, then the application retains
   * the responsibility of freeing the memory for this data.  If
   * "LetArrayManageMemory" is true, then this class will free the
   * memory when this object is destroyed. */
  void
  SetData(TValue * datain, SizeValueType sz, bool LetArrayManageMemory = false);

#ifdef __INTEL_COMPILER
#  pragma warning disable 444 // destructor for base class "itk::Array<>" is not virtual
#endif
  /** This destructor is not virtual for performance reasons. However, this
   * means that subclasses cannot allocate memory. */
  virtual ~Array();

  void
  Swap(Array & other)
  {
    std::swap(m_Data, other.m_Data);
    std::swap(m_NumElements, other.m_NumElements);
    std::swap(m_LetArrayManageMemory, other.m_LetArrayManageMemory);
  }

  //: Return reference to the element at specified index. No range checking.
  TValue & operator[](size_t i) { return m_Data[i]; }
  //: Return reference to the element at specified index. No range checking.
  TValue const & operator[](size_t i) const { return m_Data[i]; }

  Self operator*(const TValue v) const
  {
    Self result(this->Size());
    std::transform(this->begin(), this->end(), result.begin(), [v](const TValue d) -> TValue { return d * v; });
    return result;
  }

  Self
  operator+(const TValue v) const
  {
    Self result(this->Size());
    std::transform(this->begin(), this->end(), result.begin(), [v](const TValue d) -> TValue { return d + v; });
    return result;
  }

  Self
  operator-(const TValue v) const
  {
    Self result(this->Size());
    std::transform(this->begin(), this->end(), result.begin(), [v](const TValue d) -> TValue { return d - v; });
    return result;
  }

  Self
  operator/(const TValue v) const
  {
    Self result(this->Size());
    std::transform(this->begin(), this->end(), result.begin(), [v](const TValue d) -> TValue { return d / v; });
    return result;
  }


  Self &
  operator*=(const TValue v)
  {
    std::transform(this->begin(), this->end(), this->begin(), [v](const TValue d) -> TValue { return d * v; });
    return *this;
  }

  Self &
  operator/=(const TValue v)
  {
    std::transform(this->begin(), this->end(), this->begin(), [v](const TValue d) -> TValue { return d / v; });
    return *this;
  }

  Self &
  operator+=(const TValue v)
  {
    std::transform(this->begin(), this->end(), this->begin(), [v](const TValue d) -> TValue { return d + v; });
    return *this;
  }

  Self &
  operator-=(const TValue v)
  {
    std::transform(this->begin(), this->end(), this->begin(), [v](const TValue d) -> TValue { return d - v; });
    return *this;
  }

  Self operator*(const Self & v) const
  {
    Self          result(*this);
    return result.operator*=(v);
  }

  Self &
  operator*=(const Self & v)
  {
    for (size_t i = 0; i < this->Size(); ++i)
    {
      this->operator[](i) *= v.get(i);
    }
    return *this;
  }

  Self
  operator+(const Self & v) const
  {
    Self          result(*this);
    return result.operator+=(v);
  }

  Self &
  operator+=(const Self & v)
  {
    for (size_t i = 0; i < this->Size(); ++i)
    {
      this->operator[](i) += v.get(i);
    }
    return *this;
  }

  Self
  operator-(const Self & v) const
  {
    Self          result(*this);
    return result.operator-=(v);
  }

  Self &
  operator-=(const Self & v)
  {
    for (size_t i = 0; i < this->Size(); ++i)
    {
      this->operator[](i) -= v.get(i);
    }
    return *this;
  }

  Self
  operator/(const Self & v) const
  {
    Self          result(*this);
    return result.operator/=(v);
  }

  Self &
  operator/=(const Self & v)
  {
    for (size_t i = 0; i < this->Size(); ++i)
    {
      this->operator[](i) /= v.get(i);
    }
    return *this;
  }


  //: Access the contiguous block storing the elements in the vector. O(1).
  //  data_block()[0] is the first element of the vector
  TValue const *
  data_block() const
  {
    return m_Data;
  }

  //: Access the contiguous block storing the elements in the vector. O(1).
  //  data_block()[0] is the first element of the vector
  TValue *
  data_block()
  {
    return m_Data;
  }

  void
  put(const size_t i, TValue const & v)
  {
    this->m_Data[i] = v;
  }

  TValue
  get(const size_t i) const
  {
    return this->m_Data[i];
  }

  void
  clear()
  {
    this->SetSize(0);
  }

  //: Type defs for iterators
  using element_type = TValue;
  using size_type = size_t;

  //: Type defs for iterators
  using iterator = TValue *;
  //: Iterator pointing to start of data
  iterator
  begin()
  {
    return m_Data;
  }

  //: Iterator pointing to element beyond end of data
  iterator
  end()
  {
    return m_Data + m_NumElements;
  }

  //: Const iterator type
  using const_iterator = TValue const *;
  //: Iterator pointing to start of data
  const_iterator
  begin() const
  {
    return m_Data;
  }
  //: Iterator pointing to element beyond end of data
  const_iterator
  end() const
  {
    return m_Data + m_NumElements;
  }

  //: Analogous to std::vector::front().
  TValue &
  front()
  {
    return *m_Data;
  }
  //: Analogous to std::vector::back().
  TValue &
  back()
  {
    return m_Data[m_NumElements - 1];
  }

  //: Analogous to std::vector::front() (const overload).
  const TValue &
  front() const
  {
    return *m_Data;
  }
  //: Analogous to std::vector::back() (const overload).
  const TValue &
  back() const
  {
    return m_Data[m_NumElements - 1];
  }

  //: Read an Array<T> from an ascii std::istream.
  // If the Array<T> has nonzero size on input, read that many values.
  // Otherwise, read to EOF.
  bool
  read_ascii(std::istream & s)
  {
    bool size_known = (this->Size() != 0);
    if (size_known)
    {
      for (size_t i = 0; i < this->Size(); ++i)
      {
        if (!(s >> (*this)[i]))
        {
          return false;
        }
      }
      return true;
    }

    // Just read until EOF
    std::vector<TValue> allvals;
    size_t              n = 0;
    TValue              value;
    while (s >> value)
    {
      allvals.push_back(value);
      ++n;
    }
    this->SetSize(n); //*this = vnl_vector<T>(n);
    for (size_t i = 0; i < n; ++i)
    {
      this->put(i, allvals[i]);
    }
    return true;
  }

  TValue
  magnitude()
  {
    return std::sqrt(std::inner_product(m_Data, m_Data + m_NumElements, m_Data, 0.0));
  }

  bool
  is_zero() const
  {
    auto is_zero_value = [](const TValue i) { return i == TValue{ 0 }; };
    return std::find_if_not(this->begin(), this->end(), is_zero_value) == this->end();
  }

private:
  bool
  set_size(Eigen::Index n)
  {
    if (this->m_Data)
    {
      // if no change in size, do not reallocate.
      if (this->m_NumElements == n)
        return false;

      Array_free_blah;
    }
    Array_alloc_blah(n);
    return true;
  }

  TValue *     m_Data{ nullptr };
  Eigen::Index m_NumElements{ 0 };

  /** Indicates whether this array manages the memory of its data. */
  bool m_LetArrayManageMemory{ true };
};

//: Read a Array<T> from an ascii std::istream.
// If the Array has nonzero size on input, read that many values.
// Otherwise, read to EOF.
template <typename TValue>
std::istream &
operator>>(std::istream & s, Array<TValue> & M)
{
  M.read_ascii(s);
  return s;
}

template <typename TValue>
std::ostream &
operator<<(std::ostream & os, const Array<TValue> & arr)
{
  os << '[';
  const unsigned int length = arr.Size();
  if (length >= 1)
  {
    const unsigned int last = length - 1;
    for (unsigned int i = 0; i < last; ++i)
    {
      os << arr[i] << ", ";
    }
    os << arr[last];
  }
  os << ']';
  return os;
}

// declaration of specialization
template <>
ITKCommon_EXPORT std::ostream & operator<<<double>(std::ostream & os, const Array<double> & arr);
template <>
ITKCommon_EXPORT std::ostream & operator<<<float>(std::ostream & os, const Array<float> & arr);


template <typename T>
inline void
swap(Array<T> & a, Array<T> & b)
{
  a.Swap(b);
}


//: multiply scalar and vector. O(n).
// \relatesalso vnl_vector
template <class T>
inline Array<T> operator*(T s, Array<T> const & v)
{
  return v * s;
}


template <class T>
inline Array<T>
operator/(T s, Array<T> const & v)
{
  const T inverse = 1.0 / s;
  return v * inverse;
}


} // namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkArray.hxx"
#endif

#endif
