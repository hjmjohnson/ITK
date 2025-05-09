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

#include "itkAffineTransform.h"
#include "itkDisplacementFieldTransformParametersAdaptor.h"
#include "itkEuclideanDistancePointSetToPointSetMetricv4.h"
#include "itkSyNImageRegistrationMethod.h"
#include "itkTestingMacros.h"

int
itkSyNPointSetRegistrationTest(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{
  constexpr unsigned int Dimension = 2;

  using PointSetType = itk::PointSet<unsigned int, Dimension>;

  using PointSetMetricType = itk::EuclideanDistancePointSetToPointSetMetricv4<PointSetType>;
  auto metric = PointSetMetricType::New();

  using PointSetType = PointSetMetricType::FixedPointSetType;
  using PointType = PointSetType::PointType;

  using PixelType = double;
  using FixedImageType = itk::Image<PixelType, Dimension>;
  using MovingImageType = itk::Image<PixelType, Dimension>;


  auto fixedPoints = PointSetType::New();

  auto movingPoints = PointSetType::New();

  // two circles with a small offset
  PointType offset;
  for (unsigned int d = 0; d < PointSetType::PointDimension; ++d)
  {
    offset[d] = 2.0;
  }
  unsigned long count = 0;
  for (float theta = 0; theta < 2.0 * itk::Math::pi; theta += 0.1)
  {
    auto label = static_cast<unsigned int>(1.5 + count / 100);

    PointType       fixedPoint;
    constexpr float radius = 100.0;
    fixedPoint[0] = radius * std::cos(theta);
    fixedPoint[1] = radius * std::sin(theta);
    if (PointSetType::PointDimension > 2)
    {
      fixedPoint[2] = radius * std::sin(theta);
    }
    fixedPoints->SetPoint(count, fixedPoint);
    fixedPoints->SetPointData(count, label);

    PointType movingPoint;
    movingPoint[0] = fixedPoint[0] + offset[0];
    movingPoint[1] = fixedPoint[1] + offset[1];
    if (PointSetType::PointDimension > 2)
    {
      movingPoint[2] = fixedPoint[2] + offset[2];
    }
    movingPoints->SetPoint(count, movingPoint);
    movingPoints->SetPointData(count, label);

    count++;
  }

  // virtual image domain is [-110,-110]  [110,110]

  FixedImageType::SizeType      fixedImageSize;
  FixedImageType::PointType     fixedImageOrigin;
  FixedImageType::DirectionType fixedImageDirection;
  FixedImageType::SpacingType   fixedImageSpacing;

  fixedImageSize.Fill(221);
  fixedImageOrigin.Fill(-110);
  fixedImageDirection.SetIdentity();
  fixedImageSpacing.Fill(1);

  auto fixedImage = FixedImageType::New();
  fixedImage->SetRegions(fixedImageSize);
  fixedImage->SetOrigin(fixedImageOrigin);
  fixedImage->SetDirection(fixedImageDirection);
  fixedImage->SetSpacing(fixedImageSpacing);
  fixedImage->Allocate();

  using AffineTransformType = itk::AffineTransform<double, PointSetType::PointDimension>;
  auto transform = AffineTransformType::New();
  transform->SetIdentity();

  metric->SetFixedPointSet(fixedPoints);
  metric->SetMovingPointSet(movingPoints);
  metric->SetVirtualDomainFromImage(fixedImage);
  metric->SetMovingTransform(transform);
  metric->Initialize();

  // Create the SyN deformable registration method

  using VectorType = itk::Vector<double, Dimension>;
  constexpr VectorType zeroVector{};

  using DisplacementFieldType = itk::Image<VectorType, Dimension>;
  auto displacementField = DisplacementFieldType::New();
  displacementField->CopyInformation(fixedImage);
  displacementField->SetRegions(fixedImage->GetBufferedRegion());
  displacementField->Allocate();
  displacementField->FillBuffer(zeroVector);

  auto inverseDisplacementField = DisplacementFieldType::New();
  inverseDisplacementField->CopyInformation(fixedImage);
  inverseDisplacementField->SetRegions(fixedImage->GetBufferedRegion());
  inverseDisplacementField->Allocate();
  inverseDisplacementField->FillBuffer(zeroVector);

  using DisplacementFieldRegistrationType = itk::SyNImageRegistrationMethod<FixedImageType, MovingImageType>;
  auto displacementFieldRegistration = DisplacementFieldRegistrationType::New();

  using OutputTransformType = DisplacementFieldRegistrationType::OutputTransformType;
  auto outputTransform = OutputTransformType::New();
  outputTransform->SetDisplacementField(displacementField);
  outputTransform->SetInverseDisplacementField(inverseDisplacementField);

  displacementFieldRegistration->SetInitialTransform(outputTransform);
  displacementFieldRegistration->InPlaceOn();

  using DisplacementFieldTransformAdaptorType = itk::DisplacementFieldTransformParametersAdaptor<OutputTransformType>;
  DisplacementFieldRegistrationType::TransformParametersAdaptorsContainerType adaptors;

  // Create the transform adaptors
  // For the gaussian displacement field, the specified variances are in image spacing terms
  // and, in normal practice, we typically don't change these values at each level.  However,
  // if the user wishes to add that option, they can use the class
  // GaussianSmoothingOnUpdateDisplacementFieldTransformAdaptor

  constexpr unsigned int numberOfLevels = 3;

  DisplacementFieldRegistrationType::NumberOfIterationsArrayType numberOfIterationsPerLevel;
  numberOfIterationsPerLevel.SetSize(3);
  numberOfIterationsPerLevel[0] = 1;
  numberOfIterationsPerLevel[1] = 1;
  numberOfIterationsPerLevel[2] = 50;

  constexpr double varianceForUpdateField = 5;
  constexpr double varianceForTotalField = 0.0;

  displacementFieldRegistration->SetGaussianSmoothingVarianceForTheUpdateField(varianceForUpdateField);
  displacementFieldRegistration->SetGaussianSmoothingVarianceForTheTotalField(varianceForTotalField);

  DisplacementFieldRegistrationType::ShrinkFactorsArrayType shrinkFactorsPerLevel;
  shrinkFactorsPerLevel.SetSize(3);
  shrinkFactorsPerLevel.Fill(1);

  DisplacementFieldRegistrationType::SmoothingSigmasArrayType smoothingSigmasPerLevel;
  smoothingSigmasPerLevel.SetSize(3);
  smoothingSigmasPerLevel.Fill(0);

  for (unsigned int level = 0; level < numberOfLevels; ++level)
  {
    // We use the shrink image filter to calculate the fixed parameters of the virtual
    // domain at each level.  To speed up calculation and avoid unnecessary memory
    // usage, we could calculate these fixed parameters directly.

    using ShrinkFilterType = itk::ShrinkImageFilter<DisplacementFieldType, DisplacementFieldType>;
    auto shrinkFilter = ShrinkFilterType::New();
    shrinkFilter->SetShrinkFactors(shrinkFactorsPerLevel[level]);
    shrinkFilter->SetInput(displacementField);
    shrinkFilter->Update();

    auto fieldTransformAdaptor = DisplacementFieldTransformAdaptorType::New();
    fieldTransformAdaptor->SetRequiredSpacing(shrinkFilter->GetOutput()->GetSpacing());
    fieldTransformAdaptor->SetRequiredSize(shrinkFilter->GetOutput()->GetBufferedRegion().GetSize());
    fieldTransformAdaptor->SetRequiredDirection(shrinkFilter->GetOutput()->GetDirection());
    fieldTransformAdaptor->SetRequiredOrigin(shrinkFilter->GetOutput()->GetOrigin());
    fieldTransformAdaptor->SetTransform(outputTransform);

    adaptors.emplace_back(fieldTransformAdaptor);
  }

  displacementFieldRegistration->SetFixedPointSet(fixedPoints);
  displacementFieldRegistration->SetMovingPointSet(movingPoints);
  displacementFieldRegistration->SetNumberOfLevels(3);
  displacementFieldRegistration->SetMovingInitialTransform(transform);
  displacementFieldRegistration->SetShrinkFactorsPerLevel(shrinkFactorsPerLevel);
  displacementFieldRegistration->SetSmoothingSigmasPerLevel(smoothingSigmasPerLevel);
  displacementFieldRegistration->SetMetric(metric);

  ITK_TRY_EXPECT_NO_EXCEPTION(displacementFieldRegistration->Update());


  // applying the resultant transform to moving points and verify result
  std::cout << "Fixed\tMoving\tMovingTransformed\tFixedTransformed\tDiff" << std::endl;
  constexpr PointType::ValueType tolerance = 0.1;

  float averageError = 0.0;
  for (unsigned int n = 0; n < movingPoints->GetNumberOfPoints(); ++n)
  {
    // compare the points in virtual domain
    PointType transformedMovingPoint =
      displacementFieldRegistration->GetModifiableTransform()->GetInverseTransform()->TransformPoint(
        movingPoints->GetPoint(n));
    PointType       fixedPoint = fixedPoints->GetPoint(n);
    const PointType transformedFixedPoint =
      displacementFieldRegistration->GetModifiableTransform()->TransformPoint(fixedPoints->GetPoint(n));
    PointType difference;
    difference[0] = transformedMovingPoint[0] - fixedPoint[0];
    difference[1] = transformedMovingPoint[1] - fixedPoint[1];
    std::cout << fixedPoints->GetPoint(n) << '\t' << movingPoints->GetPoint(n) << '\t' << transformedMovingPoint << '\t'
              << transformedFixedPoint << '\t' << difference << std::endl;

    averageError += ((difference.GetVectorFromOrigin()).GetSquaredNorm());
  }

  const unsigned int numberOfPoints = movingPoints->GetNumberOfPoints();
  if (numberOfPoints > 0)
  {
    averageError /= static_cast<float>(numberOfPoints);
    std::cout << "Average error: " << averageError << std::endl;
    if (averageError > tolerance)
    {
      std::cerr << "Results do not match truth within tolerance." << std::endl;
      return EXIT_FAILURE;
    }
  }
  else
  {
    std::cerr << "No points." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
