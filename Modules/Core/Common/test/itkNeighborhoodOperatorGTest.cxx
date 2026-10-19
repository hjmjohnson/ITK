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

#include "itkAnnulusOperator.h"
#include "itkBackwardDifferenceOperator.h"
#include "itkDerivativeOperator.h"
#include "itkForwardDifferenceOperator.h"
#include "itkGaussianDerivativeOperator.h"
#include "itkGaussianOperator.h"
#include "itkImageKernelOperator.h"
#include "itkLaplacianOperator.h"
#include "itkNeighborhoodOperator.h"
#include "itkSobelOperator.h"

#include <type_traits> // For is_default_constructible, is_copy_constructible, etc.
#include "itkGTest.h"

namespace
{
template <typename T>
constexpr bool
IsDefaultConstructibleCopyableNoThrowMovableAndDestructible()
{
  return std::is_default_constructible_v<T> && std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T> &&
         std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T> &&
         std::is_nothrow_destructible_v<T>;
}

static_assert(std::is_copy_assignable_v<itk::NeighborhoodOperator<int, 3>>,
              "NeighborhoodOperator should be copy-assignable.");
static_assert(std::is_nothrow_move_assignable_v<itk::NeighborhoodOperator<int, 3>>,
              "NeighborhoodOperator should be noexcept move-assignable.");

static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::AnnulusOperator<int>>(),
              "AnnulusOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(
  IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::BackwardDifferenceOperator<int>>(),
  "BackwardDifferenceOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::DerivativeOperator<int>>(),
              "DerivativeOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(
  IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::ForwardDifferenceOperator<int>>(),
  "ForwardDifferenceOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(
  IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::GaussianDerivativeOperator<int>>(),
  "GaussianDerivativeOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::GaussianOperator<int>>(),
              "GaussianOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::ImageKernelOperator<int>>(),
              "ImageKernelOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::LaplacianOperator<int>>(),
              "LaplacianOperator should be default-constructible, copyable, noexcept movable, and destructible.");
static_assert(IsDefaultConstructibleCopyableNoThrowMovableAndDestructible<itk::SobelOperator<int>>(),
              "SobelOperator should be default-constructible, copyable, noexcept movable, and destructible.");
} // namespace

TEST(NeighborhoodOperator, ConvertedLegacyTest)
{
  using PixelType = float;
  constexpr unsigned int Dimension1D{ 1 };
  constexpr unsigned int Dimension2D{ 2 };
  constexpr unsigned int Dimension3D{ 3 };
  constexpr unsigned int Dimension4D{ 4 };

  std::cout << "Testing derivative operator" << std::endl;
  itk::DerivativeOperator<PixelType, Dimension3D, vnl_vector<PixelType>> d;

  auto * dPointer = &d;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(dPointer, DerivativeOperator, NeighborhoodOperator);


  constexpr unsigned int order{ 2 };
  d.SetOrder(order);
  EXPECT_EQ(order, d.GetOrder());

  unsigned long direction = 1;
  d.SetDirection(direction);
  EXPECT_EQ(direction, d.GetDirection());

  d.CreateDirectional();


  std::cout << "Testing Gaussian operator" << std::endl;
  itk::GaussianOperator<PixelType, Dimension2D, vnl_vector<PixelType>> g;

  auto * gPointer = &g;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(gPointer, GaussianOperator, NeighborhoodOperator);


  constexpr double variance{ 2.3 };
  g.SetVariance(variance);
  EXPECT_EQ(variance, g.GetVariance());

  constexpr double maximumError{ .01 };
  g.SetMaximumError(maximumError);
  EXPECT_EQ(maximumError, g.GetMaximumError());

  g.CreateDirectional();


  std::cout << "Testing ForwardDifferenceOperator" << std::endl;
  itk::ForwardDifferenceOperator<PixelType, Dimension4D, vnl_vector<PixelType>> f;

  auto * fPointer = &f;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(fPointer, ForwardDifferenceOperator, NeighborhoodOperator);

  direction = 2;
  f.SetDirection(direction);
  EXPECT_EQ(direction, f.GetDirection());

  itk::Size<4> sz;
  sz[0] = sz[1] = sz[2] = sz[3] = 2;
  f.CreateToRadius(sz);


  std::cout << "Testing BackwardDifferenceOperator" << std::endl;
  itk::BackwardDifferenceOperator<PixelType, Dimension2D, vnl_vector<PixelType>> b;

  auto * bPointer = &b;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(bPointer, BackwardDifferenceOperator, NeighborhoodOperator);


  direction = 0;
  b.SetDirection(direction);
  EXPECT_EQ(direction, b.GetDirection());

  b.CreateDirectional();


  std::cout << "Testing 1D LaplacianOperator" << std::endl;
  itk::LaplacianOperator<PixelType, Dimension1D, vnl_vector<PixelType>> a1;

  auto * a1Pointer = &a1;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(a1Pointer, LaplacianOperator, NeighborhoodOperator);


  constexpr double scales_1d[]{ 1.0 / 2.0 };
  a1.SetDerivativeScalings(scales_1d);
  EXPECT_EQ(*scales_1d, *(a1.GetDerivativeScalings()));

  a1.CreateOperator();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < a1.Size(); ++i)
  {
    std::cout << a1[i];
    if (i < a1.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  std::cout << "Testing 2D LaplacianOperator" << std::endl;
  itk::LaplacianOperator<PixelType, Dimension2D, vnl_vector<PixelType>> a2;

  constexpr double scales_2d[]{ 1.0 / 2.0, 1.0 / 4.0 };
  a2.SetDerivativeScalings(scales_2d);
  EXPECT_EQ(*scales_2d, *(a2.GetDerivativeScalings()));

  a2.CreateOperator();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < a2.Size(); ++i)
  {
    std::cout << a2[i];
    if (i < a2.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  std::cout << "Testing 3D LaplacianOperator" << std::endl;
  itk::LaplacianOperator<PixelType, Dimension3D, vnl_vector<PixelType>> a3;

  constexpr double scales_3d[]{ 1.0 / 2.0, 1.0 / 4.0, 1.0 / 5.0 };
  a3.SetDerivativeScalings(scales_3d);
  EXPECT_EQ(*scales_3d, *(a3.GetDerivativeScalings()));

  a3.CreateOperator();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < a3.Size(); ++i)
  {
    std::cout << a3[i];
    if (i < a3.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  std::cout << "Testing SobelOperator2D" << std::endl;
  itk::SobelOperator<PixelType, Dimension2D, vnl_vector<PixelType>> c;

  auto * cPointer = &c;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(cPointer, SobelOperator, NeighborhoodOperator);

  direction = 0;
  c.SetDirection(direction);
  EXPECT_EQ(direction, c.GetDirection());

  c.CreateDirectional();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < c.Size(); ++i)
  {
    std::cout << c[i];
    if (i < c.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  direction = 1;
  c.SetDirection(direction);
  EXPECT_EQ(direction, c.GetDirection());

  c.CreateDirectional();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < c.Size(); ++i)
  {
    std::cout << c[i];
    if (i < c.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  std::cout << "Testing SobelOperator3D" << std::endl;
  itk::SobelOperator<PixelType, Dimension3D, vnl_vector<PixelType>> c2;

  direction = 0;
  c2.SetDirection(direction);
  EXPECT_EQ(direction, c2.GetDirection());

  c2.CreateDirectional();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < c2.Size(); ++i)
  {
    std::cout << c2[i];
    if (i < c2.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  direction = 1;
  c2.SetDirection(direction);
  EXPECT_EQ(direction, c2.GetDirection());

  c2.CreateDirectional();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < c2.Size(); ++i)
  {
    std::cout << c2[i];
    if (i < c2.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;

  direction = 2;
  c2.SetDirection(direction);
  EXPECT_EQ(direction, c2.GetDirection());

  c2.CreateDirectional();

  std::cout << "    Operator = [ ";
  for (unsigned int i = 0; i < c2.Size(); ++i)
  {
    std::cout << c2[i];
    if (i < c2.Size() - 1)
    {
      std::cout << ", ";
    }
  }
  std::cout << ']' << std::endl << std::endl;


  std::cout << "Test finished." << std::endl;
}
