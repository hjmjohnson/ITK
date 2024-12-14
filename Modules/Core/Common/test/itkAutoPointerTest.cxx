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

#include <iostream>

#include "itkAutoPointer.h"

class TestObject
{
public:
  using Self = TestObject;
  using AutoPointer = itk::AutoPointer<Self>;
  using ConstAutoPointer = itk::AutoPointer<const Self>;
  TestObject() { std::cout << "TestObject Constructed" << '\n'; }
  virtual ~TestObject() { std::cout << "TestObject Destructed" << '\n'; }
  const char *
  GetClassName() const
  {
    return "my Class name is TestObject";
  }
};


int
itkAutoPointerTest(int, char *[])
{

  auto * obj = new TestObject;

  TestObject::AutoPointer ptr1;
  ptr1.TakeOwnership(obj);

  std::cout << "after assignment from raw pointer" << '\n';
  std::cout << "ptr1 IsOwner = " << ptr1.IsOwner() << '\n';

  std::cout << ptr1->GetClassName() << '\n';

  TestObject::AutoPointer ptr2(ptr1);

  std::cout << "after copy constructor " << '\n';
  std::cout << "ptr1 IsOwner = " << ptr1.IsOwner() << '\n';
  std::cout << "ptr2 IsOwner = " << ptr2.IsOwner() << '\n';

  ptr2.Reset();
  std::cout << "after Reset " << '\n';
  std::cout << "ptr2 IsOwner = " << ptr2.IsOwner() << '\n';

  ptr1.TakeOwnership(new TestObject);
  std::cout << "after assignment from raw pointer" << '\n';
  std::cout << "ptr1 IsOwner = " << ptr1.IsOwner() << '\n';

  // The following test exercise the methods but don't validate the results
  if (ptr1 == ptr2)
  {
    std::cout << "AutoPointers are equal " << '\n';
  }
  if (ptr1 > ptr2)
  {
    std::cout << "ptr1 > ptr2" << '\n';
  }
  if (ptr1 < ptr2)
  {
    std::cout << "ptr1 < ptr2" << '\n';
  }


  TestObject::ConstAutoPointer cptr1;
  cptr1.TakeOwnership(new TestObject);


  const TestObject::ConstAutoPointer cptr2(cptr1);


  return EXIT_SUCCESS;
}
