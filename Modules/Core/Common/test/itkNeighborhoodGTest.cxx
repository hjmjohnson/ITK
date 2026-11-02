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

#include "itkNeighborhood.h"
#include "itkVector.h"
#include "itkGTest.h"

TEST(Neighborhood, ConvertedLegacyTest)
{
  SCOPED_TRACE("TESTING WITH VNL_VECTOR ALLOCATOR");
  itk::Neighborhood<float, 2, vnl_vector<float>> b;
  b.SetRadius(3);

  SCOPED_TRACE("Test data access");
  for (unsigned int i = 0; i < b.Size(); ++i)
  {
    b[i] = static_cast<float>(i);
  }
  b.Print(std::cout);

  SCOPED_TRACE("Test non_const iterators");
  for (itk::Neighborhood<float, 2>::Iterator it = b.Begin(); it < b.End(); ++it)
  {
    *it = 4.0f;
  }
  b.Print(std::cout);

  SCOPED_TRACE("Test const_iterators");
  for (itk::Neighborhood<float, 2>::ConstIterator itc = b.Begin(); itc < b.End(); ++itc)
  {
    std::cout << *itc << ' ';
  }

  SCOPED_TRACE("Copy the buffer into a vnl_vector");
  vnl_vector<float> v = b.GetBufferReference();
  v[2] = 0.0f;
  std::cout << &v << std::endl;
  b.Print(std::cout); // b unmodified

  SCOPED_TRACE("Pointer to the buffer with a const vnl_vector");
  const vnl_vector<float> & vcp = b.GetBufferReference();
  std::cout << &vcp << std::endl;
  std::cout << vcp;

  SCOPED_TRACE("Point to the buffer using a vnl_vector");
  vnl_vector<float> & vp = b.GetBufferReference();
  std::cout << &vp << std::endl;
  vp[2] = 0.0f;
  b.Print(std::cout); // b modified

  SCOPED_TRACE("TESTING WITH DEFAULT ALLOCATOR");
  itk::Neighborhood<float, 2> q;
  itk::Size<2>                rad;
  rad[0] = 3;
  rad[1] = 2;
  q.SetRadius(rad);
  q.Print(std::cout);

  SCOPED_TRACE("Testing assignment operator");
  const itk::Neighborhood<float, 2> p = q;
  p.Print(std::cout);

  SCOPED_TRACE("Testing copy constructor");
  const itk::Neighborhood<float, 2> r(q);
  r.Print(std::cout);

  SCOPED_TRACE("Testing instantiation with itk::Vector");
  itk::Neighborhood<itk::Vector<float, 3>, 2> s;
  s.SetRadius(rad);
  s.Print(std::cout);

  SCOPED_TRACE("Testing stride lengths");
  itk::Neighborhood<float, 2> stride_2d;
  stride_2d.SetRadius(1);
  stride_2d.Print(std::cout);

  SCOPED_TRACE("3d");
  itk::Neighborhood<float, 3> stride_3d;
  stride_3d.SetRadius(1);
  stride_3d.Print(std::cout);

  SCOPED_TRACE("Printing the indices of the 8 neighbors");
  std::cout << stride_3d.GetOffset(4) << std::endl;
  std::cout << stride_3d.GetOffset(10) << std::endl;
  std::cout << stride_3d.GetOffset(12) << std::endl;
  std::cout << stride_3d.GetOffset(13) << std::endl;
  std::cout << stride_3d.GetOffset(14) << std::endl;
  std::cout << stride_3d.GetOffset(16) << std::endl;
  std::cout << stride_3d.GetOffset(22) << std::endl;


  SCOPED_TRACE("ANOTHER TEST");
  itk::Neighborhood<float, 2> q2;
  q2.SetRadius(3);
  q2.Print(std::cout);
}
