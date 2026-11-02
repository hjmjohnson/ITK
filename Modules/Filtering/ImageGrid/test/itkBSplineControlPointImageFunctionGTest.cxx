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
#include "itkBSplineControlPointImageFunction.h"
#include "itkGTest.h"

TEST(BSplineControlPointImageFunction, ConvertedLegacyTest)
{

  // We construct a B-spline parametric curve equal to f(u) = 0.5 * u^2 - 0.5 * u
  // + 1/6.  This is done using a cubic order spline with controls points
  // (1, 0, 0, 1)

  constexpr unsigned int ParametricDimension{ 1 };
  constexpr unsigned int DataDimension{ 1 };

  using RealType = float;
  using VectorType = itk::Vector<RealType, DataDimension>;
  using VectorImageType = itk::Image<VectorType, ParametricDimension>;

  auto phiLattice = VectorImageType::New();

  auto                       size = itk::MakeFilled<VectorImageType::SizeType>(4);
  auto                       spacing = itk::MakeFilled<VectorImageType::SpacingType>(1.0);
  VectorImageType::PointType origin{};

  phiLattice->SetOrigin(origin);
  phiLattice->SetSpacing(spacing);
  phiLattice->SetRegions(size);
  phiLattice->AllocateInitialized();

  // To create the specified function, the first and last control points have
  // a value of 1.0;

  VectorImageType::IndexType index{};
  auto                       value = itk::MakeFilled<VectorImageType::PixelType>(1.0);
  phiLattice->SetPixel(index, value);
  index.Fill(3);
  value.Fill(1.0);
  phiLattice->SetPixel(index, value);

  using BSplinerType = itk::BSplineControlPointImageFunction<VectorImageType>;
  auto bspliner = BSplinerType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(bspliner, BSplineControlPointImageFunction, ImageFunction);

  // Define the parametric domain [0, 1).
  origin.Fill(0);
  spacing.Fill(0.01);
  size.Fill(101);

  bspliner->SetOrigin(origin);
  EXPECT_EQ(origin, bspliner->GetOrigin());

  bspliner->SetSpacing(spacing);
  EXPECT_EQ(spacing, bspliner->GetSpacing());

  bspliner->SetSize(size);
  EXPECT_EQ(size, bspliner->GetSize());

  constexpr unsigned int bSplineOrderValue{ 3 };
  bspliner->SetSplineOrder(bSplineOrderValue);
  for (auto i : bspliner->GetSplineOrder())
  {
    EXPECT_EQ(i, bSplineOrderValue) << "Error in itk::BSplineControlPointImageFunction::GetSplineOrder";
  }

  auto bSplineOrder = itk::MakeFilled<BSplinerType::ArrayType>(bSplineOrderValue);
  bspliner->SetSplineOrder(bSplineOrder);
  EXPECT_EQ(bSplineOrder, bspliner->GetSplineOrder());

  constexpr BSplinerType::ArrayType::ValueType closeDimensionValue{ 0 };
  auto closeDimension = itk::MakeFilled<BSplinerType::ArrayType>(closeDimensionValue);
  bspliner->SetCloseDimension(closeDimension);
  EXPECT_EQ(closeDimension, bspliner->GetCloseDimension());

  constexpr BSplinerType::RealType bSplineEpsilon{ 1e-3 };
  bspliner->SetBSplineEpsilon(bSplineEpsilon);
  EXPECT_EQ(bSplineEpsilon, bspliner->GetBSplineEpsilon());


  bspliner->SetInputImage(phiLattice);

  BSplinerType::PointType    point;
  BSplinerType::GradientType gradient;
  BSplinerType::GradientType hessianComponent;
  BSplinerType::OutputType   data;

  // f(0) = 1/6;
  // f'(u) = u - 0.5 so f'(0) should be -0.5.
  // f"(u) = 1
  try
  {
    point[0] = 0.0;

    data = bspliner->EvaluateAtParametricPoint(point);
    EXPECT_NEAR(data[0], 0.166666666667, 1e-5) << "Evaluate1: data is further away from the expected value.";

    gradient = bspliner->EvaluateGradientAtParametricPoint(point);
    EXPECT_NEAR(gradient(0, 0), -0.5, 1e-5) << "Evaluate1: gradient is further away from the expected value.";

    hessianComponent = bspliner->EvaluateHessianAtParametricPoint(point, 0);

    EXPECT_NEAR(hessianComponent(0, 0), 1.0, 1e-5) << "Evaluate1: hessian is further away from the expected value.";
  }
  catch (...)
  {
    std::cerr << "Error in evaluate functions" << std::endl;
    FAIL();
  }

  // f(0.351) = 0.05276717;
  // f'(0.351) = -0.149
  try
  {
    point[0] = 0.351;

    data = bspliner->EvaluateAtParametricPoint(point);
    EXPECT_NEAR(data[0], 0.05276717, 1e-5) << "Evaluate2: data is further away from the expected value.";

    gradient = bspliner->EvaluateGradientAtParametricPoint(point);
    EXPECT_NEAR(gradient(0, 0), -0.149, 1e-5) << "Evaluate2: gradient is further away from the expected value.";

    hessianComponent = bspliner->EvaluateHessianAtParametricPoint(point, 0);
    EXPECT_NEAR(hessianComponent(0, 0), 1.0, 1e-5) << "Evaluate2: hessian is further away from the expected value.";
  }
  catch (...)
  {
    std::cerr << "Error in evaluate functions" << std::endl;
    FAIL();
  }


  std::cout << "Test finished" << std::endl;
}
