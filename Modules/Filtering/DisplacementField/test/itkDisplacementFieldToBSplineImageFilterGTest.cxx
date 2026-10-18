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

#include "itkDisplacementFieldToBSplineImageFilter.h"
#include "itkGTest.h"

TEST(DisplacementFieldToBSplineImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int ImageDimension{ 2 };

  using VectorType = itk::Vector<float, ImageDimension>;
  using DisplacementFieldType = itk::Image<VectorType, ImageDimension>;
  using PointSetType = itk::PointSet<VectorType, ImageDimension>;

  // Create a displacement field
  DisplacementFieldType::PointType     origin{};
  auto                                 spacing = itk::MakeFilled<DisplacementFieldType::SpacingType>(0.5);
  auto                                 size = itk::MakeFilled<DisplacementFieldType::SizeType>(100);
  DisplacementFieldType::DirectionType direction;

  direction.SetIdentity();

  auto ones = itk::MakeFilled<VectorType>(1);

  auto field = DisplacementFieldType::New();
  field->SetOrigin(origin);
  field->SetSpacing(spacing);
  field->SetRegions(size);
  field->SetDirection(direction);
  field->Allocate();
  field->FillBuffer(ones);

  using BSplineFilterType = itk::DisplacementFieldToBSplineImageFilter<DisplacementFieldType, PointSetType>;
  using RealImageType = BSplineFilterType::RealImageType;

  auto confidenceImage = RealImageType::New();
  confidenceImage->CopyInformation(field);
  confidenceImage->SetRegions(size);
  confidenceImage->Allocate();
  confidenceImage->FillBuffer(1.0);

  auto pointSet = PointSetType::New();

  auto ones_points = itk::MakeFilled<VectorType>(1.0);

  // Assign some random points within the b-spline domain
  PointSetType::PointType point1;
  point1[0] = 23.75;
  point1[1] = 5.125;
  pointSet->SetPoint(0, point1);
  pointSet->SetPointData(0, ones_points);

  PointSetType::PointType point2;
  point2[0] = 1.75;
  point2[1] = 45.125;
  pointSet->SetPoint(1, point2);
  pointSet->SetPointData(1, ones_points);

  PointSetType::PointType point3;
  point3[0] = 45.75;
  point3[1] = 2.125;
  pointSet->SetPoint(2, point3);
  pointSet->SetPointData(2, ones_points);

  auto numberOfControlPoints = itk::MakeFilled<BSplineFilterType::ArrayType>(4);

  auto bspliner = BSplineFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(bspliner, DisplacementFieldToBSplineImageFilter, ImageToImageFilter);


  bspliner->SetDisplacementField(field);
  EXPECT_EQ(field, bspliner->GetDisplacementField());

  bspliner->SetConfidenceImage(confidenceImage);
  EXPECT_EQ(confidenceImage, bspliner->GetConfidenceImage());

  bspliner->SetPointSet(pointSet);
  EXPECT_EQ(pointSet, bspliner->GetPointSet());

  ITK_GTEST_SET_GET_BOOLEAN(bspliner, UseInputFieldToDefineTheBSplineDomain, true);

  bspliner->SetNumberOfControlPoints(numberOfControlPoints);
  EXPECT_EQ(numberOfControlPoints, bspliner->GetNumberOfControlPoints());

  constexpr unsigned int splineOrder{ 3 };
  bspliner->SetSplineOrder(splineOrder);
  EXPECT_EQ(splineOrder, bspliner->GetSplineOrder());

  BSplineFilterType::ArrayType::ValueType numberOfFittingLevelsVal = 8;
  auto numberOfFittingLevels = itk::MakeFilled<BSplineFilterType::ArrayType>(numberOfFittingLevelsVal);
  bspliner->SetNumberOfFittingLevels(numberOfFittingLevelsVal);
  EXPECT_EQ(numberOfFittingLevels, bspliner->GetNumberOfFittingLevels());

  bspliner->SetNumberOfFittingLevels(numberOfFittingLevels);
  EXPECT_EQ(numberOfFittingLevels, bspliner->GetNumberOfFittingLevels());

  ITK_GTEST_SET_GET_BOOLEAN(bspliner, EnforceStationaryBoundary, false);

  ITK_GTEST_SET_GET_BOOLEAN(bspliner, EstimateInverse, false);

  constexpr BSplineFilterType::OriginType::ValueType bSplineDomainOriginVal = 0.0;
  auto bSplineDomainOrigin = itk::MakeFilled<BSplineFilterType::OriginType>(bSplineDomainOriginVal);
  EXPECT_EQ(bSplineDomainOrigin, bspliner->GetBSplineDomainOrigin());

  constexpr BSplineFilterType::SpacingType::ValueType bSplineDomainSpacingVal = 1.0;
  auto bSplineDomainSpacing = itk::MakeFilled<BSplineFilterType::SpacingType>(bSplineDomainSpacingVal);
  EXPECT_EQ(bSplineDomainSpacing, bspliner->GetBSplineDomainSpacing());

  constexpr BSplineFilterType::SizeType::value_type bSplineDomainSizeVal = 0;
  auto bSplineDomainSize = BSplineFilterType::SizeType::Filled(bSplineDomainSizeVal);
  EXPECT_EQ(bSplineDomainSize, bspliner->GetBSplineDomainSize());

  BSplineFilterType::DirectionType bSplineDomainDirection;
  bSplineDomainDirection.SetIdentity();
  EXPECT_EQ(bSplineDomainDirection, bspliner->GetBSplineDomainDirection());

  try
  {
    bspliner->Update();
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Exception thrown " << std::endl;
    std::cerr << excp << std::endl;
  }

  bSplineDomainOrigin = field->GetOrigin();
  EXPECT_EQ(bSplineDomainOrigin, bspliner->GetBSplineDomainOrigin());

  bSplineDomainSpacing = field->GetSpacing();
  EXPECT_EQ(bSplineDomainSpacing, bspliner->GetBSplineDomainSpacing());

  bSplineDomainSize = field->GetRequestedRegion().GetSize();
  EXPECT_EQ(bSplineDomainSize, bspliner->GetBSplineDomainSize());

  bSplineDomainDirection = field->GetDirection();
  EXPECT_EQ(bSplineDomainDirection, bspliner->GetBSplineDomainDirection());

  DisplacementFieldType::IndexType index;
  index[0] = 50;
  index[1] = 50;

  VectorType v = bspliner->GetOutput()->GetPixel(index);

  EXPECT_LT(itk::Math::Absolute(v.GetNorm() - 1.414214), 0.01);

  numberOfFittingLevelsVal = 5;
  bspliner->SetNumberOfFittingLevels(numberOfFittingLevelsVal);
  bspliner->EstimateInverseOn();

  bspliner->Update();

  v = bspliner->GetOutput()->GetPixel(index);

  EXPECT_LT(itk::Math::Absolute(v.GetNorm() - 1.414214), 0.01);

  /** do a second run using only the point set. */

  auto bspliner2 = BSplineFilterType::New();
  bspliner2->SetPointSet(pointSet);

  bspliner2->UseInputFieldToDefineTheBSplineDomainOff();

  bspliner2->SetBSplineDomainFromImage(field);

  EXPECT_EQ(bSplineDomainOrigin, bspliner2->GetBSplineDomainOrigin());
  EXPECT_EQ(bSplineDomainSpacing, bspliner2->GetBSplineDomainSpacing());
  EXPECT_EQ(bSplineDomainSize, bspliner2->GetBSplineDomainSize());
  EXPECT_EQ(bSplineDomainDirection, bspliner2->GetBSplineDomainDirection());

  bspliner2->SetNumberOfControlPoints(numberOfControlPoints);
  bspliner2->SetSplineOrder(splineOrder);

  numberOfFittingLevelsVal = 8;
  bspliner2->SetNumberOfFittingLevels(numberOfFittingLevelsVal);

  bspliner2->EnforceStationaryBoundaryOff();

  bspliner2->EstimateInverseOff();

  try
  {
    bspliner2->Update();
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Exception thrown " << std::endl;
    std::cerr << excp << std::endl;
  }
}
