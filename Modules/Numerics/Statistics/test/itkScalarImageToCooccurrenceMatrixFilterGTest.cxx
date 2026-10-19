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
#include "itkMath.h"

#include "itkScalarImageToCooccurrenceMatrixFilter.h"
#include "itkGTest.h"

TEST(ScalarImageToCooccurrenceMatrixFilter, ConvertedLegacyTest)
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
  // Generate the histogram. The un-normalized histogram should look like this:
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

  {

    using FilterType = itk::Statistics::ScalarImageToCooccurrenceMatrixFilter<InputImageType>;

    auto filter = FilterType::New();

    // Invoke update before adding an input. An exception should be
    // thrown.
    EXPECT_THROW(filter->Update(), itk::ExceptionObject) << "Failed to throw expected exception due to nullptr input: ";

    filter->ResetPipeline();

    EXPECT_EQ(filter->GetInput(), nullptr) << "GetInput() should return nullptr since the input is not set yet ";

    EXPECT_EQ(filter->GetMaskImage(), nullptr)
      << "GetMaskImage() should return nullptr since the mask image is not set yet ";


    // Invoke update with a nullptr input. An exception should be
    // thrown.
    filter->SetInput(nullptr);
    EXPECT_THROW(filter->Update(), itk::ExceptionObject) << "Failed to throw expected exception due to nullptr input: ";

    filter->ResetPipeline();

    EXPECT_EQ(filter->GetInput(), nullptr);


    filter->SetInput(image);

    constexpr InputImageType::OffsetType  offset1{ 0, 1 };
    constexpr InputImageType::OffsetType  offset2{ 1, 0 };
    const FilterType::OffsetVectorPointer offsetV = FilterType::OffsetVector::New();
    offsetV->push_back(offset1);
    offsetV->push_back(offset2);

    filter->SetOffsets(offsetV);


    filter->Update();


    const FilterType::HistogramType * hist = filter->GetOutput();

    //--------------------------------------------------------------------------
    // Test the histogram.
    //--------------------------------------------------------------------------

    // First make sure the bins are sized properly:

    const float max = hist->GetBinMax(0, 255);
    const float min = hist->GetBinMin(0, 255);

    EXPECT_FLOAT_EQ(max, 256) << "The calculated bin sizes are incorrect";
    EXPECT_FLOAT_EQ(min, 255) << "The calculated bin sizes are incorrect";

    // Now make sure the contents of the bins are correct:
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

    EXPECT_FLOAT_EQ(ooF, 24.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ttF, 16.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(otF, 20.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(toF, 20.0f) << "The histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF + ttF + otF + toF, totalF) << "The histogram was calculated incorrectly";

    //--------------------------------------------------------------------------
    // Test the histogram with normalization
    //--------------------------------------------------------------------------


    auto filter0 = FilterType::New();

    filter0->SetInput(image);
    filter0->SetOffsets(offsetV);
    filter0->NormalizeOn();

    EXPECT_TRUE(filter0->GetNormalize()) << "Normalize boolean is not set correctly";

    filter0->Update();
    const FilterType::HistogramType * hist0 = filter0->GetOutput();

    ooF = hist0->GetFrequency(one_one);
    otF = hist0->GetFrequency(one_two);
    toF = hist0->GetFrequency(two_one);
    ttF = hist0->GetFrequency(two_two);

    EXPECT_LE(ooF - 24 / 80., 0.001) << "The histogram was calculated incorrectly";
    EXPECT_LE(ttF - 16 / 80., 0.001) << "The histogram was calculated incorrectly";
    EXPECT_LE(otF - 20 / 80., 0.001) << "The histogram was calculated incorrectly";
    EXPECT_LE(toF - 20 / 80., 0.001) << "The histogram was calculated incorrectly";
    EXPECT_LE(ooF + ttF + otF + toF - 1, 0.001) << "The histogram was calculated incorrectly";


    //--------------------------------------------------------------------------
    // Generate some variant histograms and test them
    //--------------------------------------------------------------------------

    // First a histogram with 2 bins per axis
    auto filter2 = FilterType::New();

    filter2->SetInput(image);
    constexpr InputImageType::OffsetType offset3{ 0, 1 };

    filter2->SetOffset(offset3);
    filter2->SetNumberOfBinsPerAxis(2);

    EXPECT_EQ(filter2->GetNumberOfBinsPerAxis(), 2u) << "GetNumberOfBinsPerAxis() is not returning the expected value";

    filter2->Update();
    const FilterType::HistogramType * hist2 = filter2->GetOutput();

    IndexType zero_zero(hist2->GetMeasurementVectorSize());
    zero_zero[0] = 0;
    zero_zero[1] = 0;

    float zzF = hist2->GetFrequency(zero_zero);
    totalF = hist2->GetTotalFrequency();

    EXPECT_FLOAT_EQ(zzF, 40.0f) << "The degenerate histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(zzF, totalF) << "The degenerate histogram was calculated incorrectly";


    // Next a histogram with a smaller range.
    auto filter3 = FilterType::New();

    filter3->SetInput(image);
    constexpr InputImageType::OffsetType offset4{ 1, 1 };

    filter3->SetOffset(offset4);

    filter3->SetPixelValueMinMax(1, 2);

    EXPECT_EQ(filter3->GetMin(), 1) << "GetMin() is not returning the value that is expected: 1";

    EXPECT_EQ(filter3->GetMax(), 2) << "GetMin() is not returning the value that is expected: 2";


    filter3->SetNumberOfBinsPerAxis(2);

    filter3->Update();
    const FilterType::HistogramType * hist3 = filter3->GetOutput();

    IndexType zero_one(hist3->GetMeasurementVectorSize());
    IndexType one_zero(hist3->GetMeasurementVectorSize());

    zero_one[0] = 0;
    zero_one[1] = 1;

    one_zero[0] = 1;
    one_zero[1] = 0;

    zzF = hist3->GetFrequency(zero_zero);
    float zoF = hist3->GetFrequency(zero_one);
    float ozF = hist3->GetFrequency(one_zero);
    ooF = hist3->GetFrequency(one_one);
    totalF = hist3->GetTotalFrequency();

    EXPECT_FLOAT_EQ(zzF, 0.0f) << "The small size histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(zoF, 16.0f) << "The small size histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ozF, 16.0f) << "The small size histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF, 0.0f) << "The small size histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(zzF + zoF + ozF + ooF, totalF) << "The small size histogram was calculated incorrectly";

    // Next a histogram with a truncated range.
    auto filter4 = FilterType::New();

    filter4->SetInput(image);
    filter4->SetOffsets(offsetV);

    EXPECT_EQ(filter4->GetOffsets(), offsetV) << "GetOffsets() is not returning the expected offset vector: ";

    filter4->SetPixelValueMinMax(0, 1);
    filter4->SetNumberOfBinsPerAxis(2);

    filter4->Update();
    const FilterType::HistogramType * hist4 = filter4->GetOutput();

    zzF = hist4->GetFrequency(zero_zero);
    zoF = hist4->GetFrequency(zero_one);
    ozF = hist4->GetFrequency(one_zero);
    ooF = hist4->GetFrequency(one_one);
    totalF = hist4->GetTotalFrequency();

    EXPECT_FLOAT_EQ(zzF, 0.0f) << "The truncated range histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(zoF, 0.0f) << "The truncated range histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ozF, 0.0f) << "The truncated range histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(ooF, 24.0f) << "The truncated range histogram was calculated incorrectly";
    EXPECT_FLOAT_EQ(zzF + zoF + ozF + ooF, totalF) << "The truncated range histogram was calculated incorrectly";
  }
}
