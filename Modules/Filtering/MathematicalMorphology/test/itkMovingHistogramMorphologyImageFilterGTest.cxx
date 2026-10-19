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

#include "itkBinaryBallStructuringElement.h"
#include "itkMorphologyHistogram.h"
#include "itkMovingHistogramMorphologyImageFilter.h"
#include "itkGTest.h"


TEST(MovingHistogramMorphologyImageFilter, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };

  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;
  using KernelType = itk::BinaryBallStructuringElement<PixelType, Dimension>;
  using HistogramType = itk::Function::MorphologyHistogram<PixelType, std::greater<PixelType>>;

  using FilterType = itk::MovingHistogramMorphologyImageFilter<ImageType, ImageType, KernelType, HistogramType>;
  auto filter = FilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(filter, MovingHistogramMorphologyImageFilter, MovingHistogramImageFilter);


  constexpr typename FilterType::InputImagePixelType boundary = 255;
  filter->SetBoundary(boundary);
  EXPECT_EQ(boundary, filter->GetBoundary());
}
