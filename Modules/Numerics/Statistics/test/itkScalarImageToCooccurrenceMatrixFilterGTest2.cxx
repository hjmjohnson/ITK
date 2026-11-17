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

// Insight classes
#include "itkImageRegionIterator.h"


#include "itkScalarImageToCooccurrenceMatrixFilter.h"
#include "itkGTest.h"

TEST(ScalarImageToCooccurrenceMatrixFilter, ConvertedLegacyTest2)
{

  // Data definitions
  constexpr unsigned int IMGWIDTH{ 5 };
  constexpr unsigned int IMGHEIGHT{ 5 };
  constexpr unsigned int NDIMENSION{ 2 };


  //------------------------------------------------------
  // Create a simple test images
  //------------------------------------------------------
  using InputImageType = itk::Image<unsigned char, NDIMENSION>;

  using InputImageIterator = itk::ImageRegionIterator<InputImageType>;


  auto image = InputImageType::New();
  auto mask = InputImageType::New();


  constexpr InputImageType::SizeType inputImageSize{ IMGWIDTH, IMGHEIGHT };

  InputImageType::RegionType region{ inputImageSize };

  //--------------------------------------------------------------------------
  // Set up the image first. It looks like:
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //  1 2 1 2 1
  //--------------------------------------------------------------------------

  image->SetRegions(region);
  image->Allocate();

  // setup the iterator
  InputImageIterator imageIt(image, image->GetBufferedRegion());

  imageIt.GoToBegin();

  for (unsigned int i = 0; i < 5; ++i)
  {
    for (unsigned int j = 0; j < 5; j++, ++imageIt)
    {
      imageIt.Set(j % 2 + 1);
    }
  }

  //--------------------------------------------------------------------------
  // Set up the mask next. It looks like:
  //  0 0 0 0 0
  //  0 0 1 0 0
  //  0 0 1 0 0
  //  0 0 1 0 0
  //  0 0 0 0 0
  //--------------------------------------------------------------------------

  mask->SetRegions(region);
  mask->Allocate();

  // setup the iterator
  InputImageIterator maskIt(mask, mask->GetBufferedRegion());
  maskIt.GoToBegin();
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; j++, ++maskIt)
    {
      if (j == 2 && i > 0 && i < 4)
      {
        maskIt.Set(1);
      }
      else
      {
        maskIt.Set(0);
      }
    }

  //--------------------------------------------------------------------------
  // Generate the histogram. It should look like this:
  //
  //     0 1 2 ...
  //     -----
  //  0 |0 0 0
  //  1 |0 4 0
  //  2 |0 0 0
  //  .
  //  .
  //  .
  // with zeroes elsewhere.
  //--------------------------------------------------------------------------

  {

    using FilterType = itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<InputImageType>;

    auto filter = FilterType::New();

    filter->SetInput(image);

    constexpr InputImageType::OffsetType  offset1{ 0, 1 };
    constexpr InputImageType::OffsetType  offset2{ 1, 0 };
    const FilterType::OffsetVectorPointer offsetV = FilterType::OffsetVector::New();
    offsetV->push_back(offset1);
    offsetV->push_back(offset2);

    filter->SetOffsets(offsetV);
    filter->SetMaskImage(mask);
    filter->Update();
    const FilterType::HistogramType * hist = filter->GetOutput();

    //--------------------------------------------------------------------------
    // Test the histogram.
    //--------------------------------------------------------------------------
    using IndexType = FilterType::HistogramType::IndexType;
    IndexType one_one(hist->GetMeasurementVectorSize());
    IndexType one_two(hist->GetMeasurementVectorSize());
    IndexType two_one(hist->GetMeasurementVectorSize());
    IndexType two_two(hist->GetMeasurementVectorSize());

    one_one[0] = 1;
    one_one[1] = 1;

    one_two[0] = 1;
    one_two[1] = 2;

    two_one[0] = 2;
    two_one[1] = 1;

    two_two[0] = 2;
    two_two[1] = 2;

    float ooF = hist->GetFrequency(one_one);
    float otF = hist->GetFrequency(one_two);
    float toF = hist->GetFrequency(two_one);
    float ttF = hist->GetFrequency(two_two);
    float totalF = hist->GetTotalFrequency();

    EXPECT_FLOAT_EQ(ooF, 4.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF, totalF) << "The histogram was calculated incorrectly";

    //--------------------------------------------------------------------------
    // Test the histogram with "0" as the "inside" value instead of "1"
    // It should look like this:
    //
    //     0 1  2 ...
    //     ------
    //  0 |0 0  0
    //  1 |0 18 14
    //  2 |0 14 18
    //  .
    //  .
    //  .
    // with zeroes elsewhere.
    //--------------------------------------------------------------------------
    filter = FilterType::New();

    filter->SetInput(image);
    filter->SetOffsets(offsetV);
    filter->SetMaskImage(mask);
    filter->SetInsidePixelValue(0);
    filter->Update();
    hist = filter->GetOutput();

    ooF = hist->GetFrequency(one_one);
    otF = hist->GetFrequency(one_two);
    toF = hist->GetFrequency(two_one);
    ttF = hist->GetFrequency(two_two);
    totalF = hist->GetTotalFrequency();

    EXPECT_FLOAT_EQ(ooF, 16.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 16.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 14.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 14.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF + ttF + otF + toF, totalF) << "The histogram was calculated incorrectly";

    EXPECT_EQ(filter->GetInsidePixelValue(), 0) << "GetInsidePixelValue() is not returning the expected value";

    //--------------------------------------------------------------------------
    // Generate the histogram with no mask. The un-normalized, un-masked histogram
    // should look like this:
    //
    //     0 1  2 ...
    //     ------
    //  0 |0 0  0
    //  1 |0 24 20
    //  2 |0 20 16
    //  3 |0 0  0
    //  .
    //  .
    // with zeroes elsewhere.
    //--------------------------------------------------------------------------

    filter = FilterType::New();

    filter->SetInput(image);
    filter->SetOffsets(offsetV);
    filter->Update();
    hist = filter->GetOutput();

    ooF = hist->GetFrequency(one_one);
    otF = hist->GetFrequency(one_two);
    toF = hist->GetFrequency(two_one);
    ttF = hist->GetFrequency(two_two);
    totalF = hist->GetTotalFrequency();


    EXPECT_FLOAT_EQ(ooF, 24.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 16.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 20.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 20.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF + ttF + otF + toF, totalF) << "The histogram was calculated incorrectly";

    auto filter2 = FilterType::New();

    filter2->SetInput(image);
    filter2->SetMaskImage(mask);
    filter2->SetPixelValueMinMax(0, 1);
    filter2->SetOffsets(offsetV);
    filter2->Update();
    hist = filter2->GetOutput();

    ooF = hist->GetFrequency(one_one);
    otF = hist->GetFrequency(one_two);
    toF = hist->GetFrequency(two_one);
    ttF = hist->GetFrequency(two_two);
    totalF = hist->GetTotalFrequency();

    EXPECT_FLOAT_EQ(ooF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(totalF, 4.0f) << "The histogram was calculated incorrectly";

    // fill the mask buffer to one
    mask->FillBuffer(1);
    filter2->SetInsidePixelValue(1);
    filter2->SetPixelValueMinMax(0, 1);
    filter2->Update();

    ooF = hist->GetFrequency(one_one);
    otF = hist->GetFrequency(one_two);
    toF = hist->GetFrequency(two_one);
    ttF = hist->GetFrequency(two_two);
    totalF = hist->GetTotalFrequency();

    EXPECT_FLOAT_EQ(ooF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 0.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(totalF, 24.0f) << "The histogram was calculated incorrectly";
  }
}
