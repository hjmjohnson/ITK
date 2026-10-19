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


#include "itkScalarImageToRunLengthMatrixFilter.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(ScalarImageToRunLengthMatrixFilter, ConvertedLegacyTest)
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

  InputImageType::RegionType region;

  region.SetSize(inputImageSize);

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

  {

    using FilterType = itk::Statistics::ScalarImageToRunLengthMatrixFilter<InputImageType>;

    auto filter = FilterType::New();

    filter->SetInput(image);

    constexpr InputImageType::OffsetType  offset1{ 0, -1 };
    constexpr InputImageType::OffsetType  offset2{ -1, 0 };
    const FilterType::OffsetVectorPointer offsetV = FilterType::OffsetVector::New();
    offsetV->push_back(offset1);
    offsetV->push_back(offset2);

    filter->SetOffsets(offsetV);
    filter->SetMaskImage(mask);
    // purposely setting the max value to max(Image)+1
    filter->SetPixelValueMinMax(0, 3);
    filter->SetDistanceValueMinMax(0, 8);
    filter->SetNumberOfBinsPerAxis(5);
    filter->Update();
    const FilterType::HistogramType * hist = filter->GetOutput();


    //--------------------------------------------------------------------------
    // Test the histogram.
    //--------------------------------------------------------------------------

    const unsigned int frequencies[5][5] = {
      { 0, 3, 0, 0, 0 }, { 0, 1, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }
    };

    for (unsigned int i = 0; i < 5; ++i)
    {
      for (unsigned int j = 0; j < 5; ++j)
      {
        using IndexType = FilterType::HistogramType::IndexType;
        IndexType index(hist->GetMeasurementVectorSize());
        index[0] = i;
        index[1] = j;
        EXPECT_EQ(hist->GetFrequency(index), frequencies[j][i]) << "(i,j)= " << '(' << i << ',' << j << ')';
      }
    }
    const unsigned int totalF = hist->GetTotalFrequency();
    EXPECT_EQ(totalF, 4u) << "Expected total frequency = 4";

    filter = FilterType::New();

    filter->SetInput(image);
    filter->SetOffsets(offsetV);
    filter->SetMaskImage(mask);
    filter->SetInsidePixelValue(0);
    // purposely setting the max value to max(Image)+1
    filter->SetPixelValueMinMax(0, 3);
    filter->SetDistanceValueMinMax(0, 8);
    filter->SetNumberOfBinsPerAxis(5);

    EXPECT_EQ(filter->GetInsidePixelValue(), 0) << "GetInsidePixelValue() is not returning the expected value";
    EXPECT_NE(filter->GetMaskImage(), nullptr) << "Mask should not be null.";
    EXPECT_EQ(filter->GetMin(), 0) << "GetMin() is not returning the expected value";
    EXPECT_EQ(filter->GetMax(), 3) << "GetMax() is not returning the expected value";
    EXPECT_EQ(filter->GetMinDistance(), 0.0) << "GetMinDistance() is not returning the expected value";
    EXPECT_EQ(filter->GetMaxDistance(), 8.0) << "GetMaxDistance() is not returning the expected value";

    const FilterType::OffsetVector * offsetVector = filter->GetOffsets();
    ASSERT_EQ(offsetVector->size(), 2u) << "GetOffsets() is not returning the correct offsets";
    EXPECT_EQ((*offsetVector)[0][0], 0) << "GetOffsets() is not returning the correct offsets";
    EXPECT_EQ((*offsetVector)[0][1], -1) << "GetOffsets() is not returning the correct offsets";
    EXPECT_EQ((*offsetVector)[1][0], -1) << "GetOffsets() is not returning the correct offsets";
    EXPECT_EQ((*offsetVector)[1][1], 0) << "GetOffsets() is not returning the correct offsets";
    EXPECT_EQ(filter->GetNumberOfBinsPerAxis(), 5u) << "GetNumberOfBinsPerAxis() is not returning the expected value";

    filter->Update();
    hist = filter->GetOutput();

    const unsigned int frequencies2[5][5] = {
      { 0, 12, 0, 10, 0 }, { 0, 0, 0, 0, 0 }, { 0, 3, 0, 2, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }
    };

    for (unsigned int i = 0; i < 5; ++i)
    {
      for (unsigned int j = 0; j < 5; ++j)
      {
        using IndexType = FilterType::HistogramType::IndexType;
        IndexType index(hist->GetMeasurementVectorSize());
        index[0] = i;
        index[1] = j;
        EXPECT_EQ(hist->GetFrequency(index), frequencies2[j][i]) << "(i,j)= " << '(' << i << ',' << j << ')';
      }
    }

    filter->Print(std::cout, 3);
  }
}
