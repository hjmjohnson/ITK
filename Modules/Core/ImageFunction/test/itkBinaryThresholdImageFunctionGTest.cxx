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

#include "itkImageRegionIterator.h"

#include "itkBinaryThresholdImageFunction.h"
#include "itkGTest.h"

TEST(BinaryThresholdImageFunction, ConvertedLegacyTest)
{
  using FloatImage = itk::Image<float, 3>;

  auto                  size = FloatImage::SizeType::Filled(64);
  FloatImage::IndexType index{};

  FloatImage::RegionType region = { index, size };

  auto image = FloatImage::CreateInitialized(region);

  for (unsigned int i = 0; i < FloatImage::ImageDimension; ++i)
  {
    size[i] -= 20;
    index[i] += 10;
  }
  region = { index, size };

  itk::ImageRegionIterator<FloatImage> it(image, region);
  while (!it.IsAtEnd())
  {
    it.Set(100.0);
    ++it;
  }

  // Try the function inside and outside the region
  using ImageFunction = itk::BinaryThresholdImageFunction<FloatImage>;
  auto threshold = ImageFunction::New();

  ImageFunction::PointType           point;
  ImageFunction::ContinuousIndexType continuousIndex;

  threshold->SetInputImage(image);

  threshold->ThresholdBelow(100.0);
  index[0] = 11;
  index[1] = 11;
  index[2] = 11;

  EXPECT_TRUE(threshold->EvaluateAtIndex(index));

  threshold->ThresholdAbove(100.0);
  EXPECT_TRUE(threshold->EvaluateAtIndex(index));

  threshold->ThresholdAbove(101.0);
  EXPECT_FALSE(threshold->EvaluateAtIndex(index));

  threshold->ThresholdBetween(100.0, 100.0);
  EXPECT_TRUE(threshold->EvaluateAtIndex(index));

  threshold->ThresholdBetween(-100.0, 0.0);
  EXPECT_FALSE(threshold->EvaluateAtIndex(index));

  index[0] = 8;
  index[1] = 8;
  index[2] = 8;
  threshold->ThresholdBetween(100.0, 200.0);
  EXPECT_FALSE(threshold->EvaluateAtIndex(index));

  std::cout << threshold;

  // Test Evaluate
  point[0] = 5;
  point[1] = 5;
  point[2] = 5;
  threshold->Evaluate(point);

  // Test EvaluateAtContinuousIndex
  continuousIndex[0] = 9;
  continuousIndex[1] = 9;
  continuousIndex[2] = 9;
  threshold->EvaluateAtContinuousIndex(continuousIndex);
}
