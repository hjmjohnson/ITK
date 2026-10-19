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


#include "itkThresholdLabelerImageFilter.h"
#include "itkGTest.h"
#include "itkImageRegionIterator.h"
#include "itkUnaryFunctorImageFilter.h"

namespace
{
void
ThresholdLabelerImageFilterTestHelper(bool useRealTypeThresholds)
{
  //
  //  The following code defines the input and output pixel types and their
  //  associated image types.
  //
  constexpr unsigned int Dimension{ 2 };

  using InputPixelType = float;
  using LabeledPixelType = unsigned long;

  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using LabeledImageType = itk::Image<LabeledPixelType, Dimension>;

  // Create an image with stripes to label
  InputImageType::IndexType  index = { { 0, 0 } };
  InputImageType::SizeType   size = { { 32, 32 } };
  InputImageType::RegionType region{ index, size };

  auto inputImage = InputImageType::New();
  inputImage->SetLargestPossibleRegion(region);
  inputImage->SetBufferedRegion(region);
  inputImage->Allocate();

  size[0] = 32;
  size[1] = 8;
  region.SetSize(size);

  // Stripe y indexes
  using IndexValueVectorType = std::vector<InputImageType::IndexType::IndexValueType>;
  IndexValueVectorType yindexes{ 0, 8, 16, 24 };

  // Set the values for each stripe
  std::vector<InputPixelType> values{ 0.5, 1.5, 2.5, 3.5 };

  // Set the value for the offset
  constexpr unsigned long offset{ 4 };

  //  Set the labels vector
  std::vector<LabeledPixelType> labels{ 0 + offset, 1 + offset, 2 + offset, 3 + offset };

  // Fill in the image
  {
    unsigned int i = 0;
    for (auto indexIter = yindexes.begin(); indexIter != yindexes.end(); ++indexIter, ++i)
    {
      index[0] = 0;
      index[1] = *indexIter;
      region.SetIndex(index);
      itk::ImageRegionIterator<InputImageType> iter(inputImage, region);
      for (iter.GoToBegin(); !iter.IsAtEnd(); ++iter)
      {
        iter.Set(values[i]);
      }
    }
  }

  // Apply labeler filter
  using LabelerFilterType = itk::ThresholdLabelerImageFilter<InputImageType, LabeledImageType>;
  auto labelerFilter = LabelerFilterType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(labelerFilter, ThresholdLabelerImageFilter, UnaryFunctorImageFilter);


  labelerFilter->SetInput(inputImage);

  // Test exception when providing unsorted thresholds
  std::vector<LabelerFilterType::RealThresholdType> unsrtThresholds{ 2.0, 1.0, 3.0 };

  labelerFilter->SetRealThresholds(unsrtThresholds);

  EXPECT_THROW(labelerFilter->Update(), itk::ExceptionObject);

  if (!useRealTypeThresholds)
  {
    // Set the thresholds between values
    std::vector<InputPixelType> thresholds{ 1.0, 2.0, 3.0 };

    labelerFilter->SetThresholds(thresholds);
    // ITK_TEST_SET_GET_VALUE( thresholds, labelerFilter->GetThresholds() );
  }
  else
  {
    // Set the thresholds between values
    std::vector<LabelerFilterType::RealThresholdType> thresholds{ 1.0, 2.0, 3.0 };

    labelerFilter->SetRealThresholds(thresholds);
    // ITK_TEST_SET_GET_VALUE( thresholds, labelerFilter->GetRealThresholds() );
  }

  labelerFilter->SetLabelOffset(offset);
  EXPECT_EQ(offset, labelerFilter->GetLabelOffset());


  ASSERT_NO_THROW(labelerFilter->SetFunctor(labelerFilter->GetFunctor()));


  ASSERT_NO_THROW(labelerFilter->Update());


  // Check if labels coincide with expected labels
  bool         passed = true;
  unsigned int i = 0;
  for (auto indexIter = yindexes.begin(); indexIter != yindexes.end(); ++indexIter, ++i)
  {
    index[0] = 0;
    index[1] = *indexIter;
    region.SetIndex(index);
    itk::ImageRegionConstIterator<LabeledImageType> iter(labelerFilter->GetOutput(), region);
    for (iter.GoToBegin(); !iter.IsAtEnd(); ++iter)
    {
      if (iter.Get() != labels[i])
      {
        passed = false;
        break;
      }
    }
    if (!passed)
    {
      break;
    }
  }

  EXPECT_TRUE(passed) << labelerFilter;
}
} // namespace

TEST(ThresholdLabelerImageFilter, ConvertedLegacyTest)
{
  bool useRealTypeThresholds = true;
  ThresholdLabelerImageFilterTestHelper(useRealTypeThresholds);

  useRealTypeThresholds = false;
  ThresholdLabelerImageFilterTestHelper(useRealTypeThresholds);
}
