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

#include "itkTimeVaryingVelocityFieldTransform.h"
#include "itkGTest.h"


TEST(TimeVaryingVelocityFieldTransform, ConvertedLegacyTest)
{
  constexpr unsigned int ComponentDimension{ 3 };
  constexpr unsigned int VelocityFieldDimension{ 4 };

  using ComponentType = double;

  using VectorType = itk::Vector<ComponentType, ComponentDimension>;
  using DisplacementFieldType = itk::Image<VectorType, ComponentDimension>;
  using TimeVaryingVelocityFieldType = itk::Image<VectorType, VelocityFieldDimension>;

  constexpr TimeVaryingVelocityFieldType::PointType origin{};

  auto spacing = itk::MakeFilled<TimeVaryingVelocityFieldType::SpacingType>(2.0);

  auto size = TimeVaryingVelocityFieldType::SizeType::Filled(25);

  auto displacement1 = itk::MakeFilled<VectorType>(0.1);

  auto timeVaryingVelocityField = TimeVaryingVelocityFieldType::New();

  timeVaryingVelocityField->SetOrigin(origin);
  timeVaryingVelocityField->SetSpacing(spacing);
  timeVaryingVelocityField->SetRegions(size);
  timeVaryingVelocityField->Allocate();
  timeVaryingVelocityField->FillBuffer(displacement1);

  using IntegratorType =
    itk::TimeVaryingVelocityFieldIntegrationImageFilter<TimeVaryingVelocityFieldType, DisplacementFieldType>;

  auto integrator = IntegratorType::New();
  integrator->SetInput(timeVaryingVelocityField);
  integrator->SetLowerTimeBound(0.3);
  integrator->SetUpperTimeBound(0.75);
  integrator->SetNumberOfIntegrationSteps(10);
  integrator->Update();

  integrator->Print(std::cout, 3);

  constexpr DisplacementFieldType::IndexType index{};

  // This integration should result in a constant image of value
  // 0.75 * 0.1 - 0.3 * 0.1 = 0.045 with ~epsilon deviation
  // due to numerical computations
  const DisplacementFieldType * displacementField = integrator->GetOutput();

  VectorType displacementPixel = displacementField->GetPixel(index);

  std::cout << "Estimated forward displacement vector: " << displacementPixel << std::endl;
  EXPECT_NEAR(displacementPixel[0], 0.045, 0.0001);

  auto inverseIntegrator = IntegratorType::New();
  inverseIntegrator->SetInput(timeVaryingVelocityField);
  inverseIntegrator->SetLowerTimeBound(1.0);
  inverseIntegrator->SetUpperTimeBound(0.0);
  inverseIntegrator->SetNumberOfIntegrationSteps(10);
  inverseIntegrator->Update();

  // This integration should result in a constant image of value
  // -( 0.1 * 1.0 - ( 0.1 * 0.0 ) ) = -0.1 with ~epsilon deviation
  // due to numerical computations
  const DisplacementFieldType * inverseField = inverseIntegrator->GetOutput();
  displacementPixel = inverseField->GetPixel(index);
  EXPECT_NEAR(displacementPixel[0], -0.101852, 0.01);

  // Now test the transform

  using TransformType = itk::TimeVaryingVelocityFieldTransform<ComponentType, ComponentDimension>;
  auto transform = TransformType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(transform, TimeVaryingVelocityFieldTransform, VelocityFieldTransform);

  transform->SetLowerTimeBound(0.0);
  transform->SetUpperTimeBound(1.0);

  EXPECT_THROW(transform->IntegrateVelocityField(), itk::ExceptionObject);


  transform->SetVelocityField(timeVaryingVelocityField);
  EXPECT_EQ(timeVaryingVelocityField, transform->GetModifiableTimeVaryingVelocityField());
  EXPECT_EQ(timeVaryingVelocityField, transform->GetTimeVaryingVelocityField());

  ASSERT_NO_THROW(transform->IntegrateVelocityField());


  // Now Clone the Transform and test transform again
  const TransformType::Pointer clone = transform->Clone();

  auto point = itk::MakeFilled<TransformType::InputPointType>(1.3);

  using OutputPointType = TransformType::OutputPointType;
  OutputPointType transformedPoint = transform->TransformPoint(point);
  OutputPointType cloneTransformedPoint = clone->TransformPoint(point);

  auto displacement = itk::MakeFilled<VectorType>(0.1);

  point += displacement;

  EXPECT_LE(point.EuclideanDistanceTo(transformedPoint), 0.01);
  EXPECT_LE(point.EuclideanDistanceTo(cloneTransformedPoint), 0.01);
  point -= displacement;

  TransformType::InputPointType point2;
  point2.CastFrom(transformedPoint);

  TransformType::InputPointType clonePoint2;
  clonePoint2.CastFrom(cloneTransformedPoint);

  using InverseTransformBasePointer = TransformType::InverseTransformBasePointer;
  const InverseTransformBasePointer inverseTransform = transform->GetInverseTransform();
  const InverseTransformBasePointer cloneInverseTransform = clone->GetInverseTransform();

  transformedPoint = inverseTransform->TransformPoint(point2);
  cloneTransformedPoint = cloneInverseTransform->TransformPoint(clonePoint2);

  EXPECT_LE(point.EuclideanDistanceTo(transformedPoint), 0.01);
  EXPECT_LE(point.EuclideanDistanceTo(cloneTransformedPoint), 0.01);

  transform->Print(std::cout, 3);
}
