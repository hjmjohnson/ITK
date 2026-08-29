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

// First include the header file to be tested:
#include "itkABINamespace.h"
#include <gtest/gtest.h>
#include <type_traits>

// ITK's own sources do not yet open ITK_ABI_NAMESPACE_BEGIN, so these cases
// exercise the macros against a local namespace rather than against itk.
namespace itkABINamespaceGTest
{
ITK_ABI_NAMESPACE_BEGIN
class Widget
{
public:
  int
  Value() const
  {
    return 42;
  }
};
ITK_ABI_NAMESPACE_END
} // namespace itkABINamespaceGTest

// The pattern a downstream project uses to forward declare a type so that the
// declaration names the same entity under any configured namespace.
namespace itkABINamespaceGTest
{
ITK_ABI_NAMESPACE_BEGIN
class Widget;
ITK_ABI_NAMESPACE_END
} // namespace itkABINamespaceGTest

namespace
{
int
ITK_ABI_NAMESPACE_MANGLE(itkABINamespaceGTestProbe)()
{
  return 42;
}
} // namespace

// A guarded forward declaration must name the defined type rather than
// introduce a second, incomplete type that shadows it.
TEST(ABINamespace, GuardedForwardDeclarationNamesTheDefinition)
{
  const itkABINamespaceGTest::Widget widget;
  EXPECT_EQ(widget.Value(), 42);
  static_assert(std::is_same_v<decltype(widget), const itkABINamespaceGTest::Widget>);
}

TEST(ABINamespace, MangleProducesACallableSymbol)
{
  EXPECT_EQ(ITK_ABI_NAMESPACE_MANGLE(itkABINamespaceGTestProbe)(), 42);
}

// The default configuration must leave every translation unit exactly as it
// was, so an unguarded declaration keeps naming the same entity.
TEST(ABINamespace, DefaultConfigurationIsANoOp)
{
#if ITK_HAS_ABI_NAMESPACE
  GTEST_SKIP() << "ITK is configured with a non-default ABI namespace.";
#else
  EXPECT_EQ(itkABINamespaceGTestProbe(), 42);
#endif
}
