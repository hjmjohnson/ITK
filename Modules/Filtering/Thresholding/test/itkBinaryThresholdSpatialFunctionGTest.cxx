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

#include "itkBinaryThresholdSpatialFunction.h"
#include "itkGTest.h"
#include "itkSphereSignedDistanceFunction.h"

#include "itkFloodFilledSpatialFunctionConditionalConstIterator.h"

/**
 * This module tests the sphereality of the
 * BinaryThresholdSpatialFunction class.
 *
 * In particular, it creates a SphereSignedDistanceFunction object
 * connect it to a BinaryThresholdSpatialFunction class.
 *
 * The sphere parameters are set at radius of 5 and center of (0,0).
 * Membership (i.e. with user specified threshold) is evaluated at
 * several point and compared to expected values.
 * The test fails if the evaluated results is not the same as expected
 * results.
 *
 */

TEST(BinaryThresholdSpatialFunction, ConvertedLegacyTest)
{
  using CoordRep = double;
  constexpr unsigned int Dimension{ 2 };

  using SphereFunctionType = itk::SphereSignedDistanceFunction<CoordRep, Dimension>;
  using FunctionType = itk::BinaryThresholdSpatialFunction<SphereFunctionType>;
  using PointType = SphereFunctionType::PointType;
  using ParametersType = SphereFunctionType::ParametersType;

  auto sphere = SphereFunctionType::New();

  // We must initialize the sphere before use
  sphere->Initialize();

  ParametersType parameters(sphere->GetNumberOfParameters(), 0.0);
  parameters[0] = 5.0;

  sphere->SetParameters(parameters);

  std::cout << "SphereParameters: " << sphere->GetParameters() << std::endl;

  // Create a binary threshold function
  auto function = FunctionType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(function, BinaryThresholdSpatialFunction, SpatialFunction);


  // Connect the sphere function
  function->SetFunction(sphere);

  // Set the thresholds
  constexpr double lowerThreshold{ -3.0 };
  constexpr double upperThreshold{ 4.0 };
  function->SetLowerThreshold(lowerThreshold);
  EXPECT_EQ(lowerThreshold, function->GetLowerThreshold());
  function->SetUpperThreshold(upperThreshold);
  EXPECT_EQ(upperThreshold, function->GetUpperThreshold());

  PointType point;

  for (double p = 0.0; p < 10.0; p += 1.0)
  {
    point.Fill(p);
    const FunctionType::OutputType output = function->Evaluate(point);
    std::cout << "f(" << point << ") = " << output;
    std::cerr << " [" << function->GetFunction()->Evaluate(point);
    std::cout << "] " << std::endl;

    // Check results
    const CoordRep val = p * std::sqrt(2.0) - parameters[0];
    const bool     expected = (lowerThreshold <= val && upperThreshold >= val);
    EXPECT_EQ(output, expected) << "Error at point: " << point;
  }

  //
  // In the following, we demonstrate how BinaryThresholdSpatialFunction
  // can be used to iterate over pixels whose signed distance is
  // within [lowerThreshold, upperThreshold] of the zero level set defining
  // the sphere.
  //

  // Set up a dummy image
  using ImageType = itk::Image<unsigned char, Dimension>;
  auto image = ImageType::New();
  auto size = ImageType::SizeType::Filled(10);
  image->SetRegions(size);
  image->Allocate();
  image->FillBuffer(255);

  // Set up the conditional iterator
  using IteratorType = itk::FloodFilledSpatialFunctionConditionalConstIterator<ImageType, FunctionType>;

  IteratorType iterator(image, function);
  iterator.SetOriginInclusionStrategy();

  // Add a seed that already inside the region
  ImageType::IndexType index;
  index[0] = 0;
  index[1] = 3;
  iterator.AddSeed(index);

  // Get the seeds and display them
  std::cout << "Iterator seeds";
  for (auto seed : iterator.GetSeeds())
  {
    std::cout << ' ' << seed;
  }
  std::cout << std::endl;

  iterator.GoToBegin();

  while (!iterator.IsAtEnd())
  {
    index = iterator.GetIndex();
    image->TransformIndexToPhysicalPoint(index, point);
    const double value = sphere->Evaluate(point);

    // Check if value is within range
    EXPECT_GE(value, lowerThreshold) << "Error at index: " << index;
    EXPECT_LE(value, upperThreshold) << "Error at index: " << index;

    ++iterator;
  }
}
