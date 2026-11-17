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

#include "itkScalarImageToRunLengthFeaturesFilter.h"
#include "itkGTest.h"

TEST(ScalarImageToRunLengthFeaturesFilter, ConvertedLegacyTest)
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

  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; j++, ++imageIt)
    {
      imageIt.Set(j % 2 + 1);
    }

  //--------------------------------------------------------------------------
  // Set up the mask next. It looks like:
  //  1 1 1 1 1
  //  1 1 1 1 1
  //  1 1 1 1 1
  //  1 1 1 1 1
  //  1 1 1 1 1
  //--------------------------------------------------------------------------

  auto mask = InputImageType::New();
  mask->SetRegions(region);
  mask->Allocate();

  // setup the iterator
  InputImageIterator maskIt(mask, mask->GetBufferedRegion());
  maskIt.GoToBegin();
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; j++, ++maskIt)
    {
      maskIt.Set(1);
    }

  //--------------------------------------------------------------------------
  // Test the texFilter
  //--------------------------------------------------------------------------
  {
    using RunLengthFilterType = itk::Statistics::ScalarImageToRunLengthFeaturesFilter<InputImageType>;

    // First test: just use the defaults.
    auto texFilter = RunLengthFilterType::New();

    // Invoke update before adding an input. An exception should be
    // thrown.
    EXPECT_THROW(texFilter->Update(), itk::ExceptionObject)
      << "Failed to throw expected exception due to nullptr input: ";

    texFilter->ResetPipeline();

    EXPECT_EQ(texFilter->GetInput(), nullptr) << "GetInput() should return nullptr since the input is  not set yet ";

    EXPECT_EQ(texFilter->GetMaskImage(), nullptr)
      << "GetMaskImage() should return nullptr since the mask image is not set yet ";

    // Invoke update with a nullptr input. An exception should be
    // thrown.
    texFilter->SetInput(nullptr);
    EXPECT_THROW(texFilter->Update(), itk::ExceptionObject)
      << "Failed to throw expected exception due to nullptr input: ";

    texFilter->ResetPipeline();

    EXPECT_EQ(texFilter->GetInput(), nullptr);

    // Test the Use_PixelContainer boolean
    texFilter->SetFastCalculations(false);
    EXPECT_FALSE(texFilter->GetFastCalculations()) << "Error in Set/Get FastCalculations methods";

    texFilter->FastCalculationsOn();
    EXPECT_TRUE(texFilter->GetFastCalculations()) << "Error in Set/Get FastCalculationsOn method";

    texFilter->FastCalculationsOff();
    texFilter->SetInput(image);
    texFilter->SetPixelValueMinMax(0, 2);
    texFilter->SetDistanceValueMinMax(0, 5.0);
    texFilter->SetNumberOfBinsPerAxis(5);
    texFilter->SetMaskImage(mask);
    texFilter->Update();

    texFilter->Print(std::cout);

    // Test GetInput
    EXPECT_EQ(texFilter->GetInput(), image);

    // Test GetMaskImage
    EXPECT_EQ(texFilter->GetMaskImage(), mask);

    RunLengthFilterType::FeatureValueVectorPointer means = texFilter->GetFeatureMeans();
    RunLengthFilterType::FeatureValueVectorPointer stds = texFilter->GetFeatureStandardDeviations();

    constexpr double expectedMeans[10]{ 0.76, 7, 10.4, 20, 0.0826667, 15.4, 0.0628267, 11.704, 0.578667, 107.8 };

    {
      RunLengthFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }
    {
      constexpr double expectedDeviations[10]{ 0.415692, 10.3923,   4.50333, 8.66025,  0,
                                               0,        0.0343639, 6.40166, 0.859097, 160.041494 };
      RunLengthFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
      for (int counter = 0; sIt != stds->End(); ++sIt, counter++)
      {
        EXPECT_NEAR(expectedDeviations[counter], sIt.Value(), 0.0001) << "Deviation for feature " << counter;
      }
    }
    // Rerun the feature generation with fast calculations on
    texFilter->FastCalculationsOn();
    texFilter->Update();
    means = texFilter->GetFeatureMeans();
    stds = texFilter->GetFeatureStandardDeviations();

    constexpr double expectedMeans2[10]{ 1, 1, 13, 25, 0.0826667, 15.4, 0.0826667, 15.4, 0.0826667, 15.4 };
    constexpr double expectedDeviations2[10]{ 0 };

    {
      RunLengthFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans2[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }
    {
      RunLengthFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
      for (int counter = 0; sIt != stds->End(); ++sIt, counter++)
      {
        EXPECT_NEAR(expectedDeviations2[counter], sIt.Value(), 0.0001) << "Deviation for feature " << counter;
      }
    }
    //    //Rerun the feature generation setting an offset
    RunLengthFilterType::OffsetType offset;
    offset[0] = -1;
    offset[1] = -1;

    RunLengthFilterType::OffsetVectorPointer offsets;

    offsets = RunLengthFilterType::OffsetVector::New();

    offsets->push_back(offset);
    texFilter->SetOffsets(offsets);

    const RunLengthFilterType::OffsetVector * offsets2 = texFilter->GetOffsets();

    for (RunLengthFilterType::OffsetVector::ConstIterator vIt = offsets->Begin(), vIt2 = offsets2->Begin();
         vIt != offsets->End();
         ++vIt, ++vIt2)
    {
      EXPECT_EQ(vIt.Value(), vIt2.Value()) << "Offsets not properly set";
    }

    texFilter->Update();

    EXPECT_NE(texFilter->GetMaskImage(), nullptr) << "Mask should not be null.";

    means = texFilter->GetFeatureMeans();
    stds = texFilter->GetFeatureStandardDeviations();

    constexpr double expectedMeans3[10]{ 1, 1, 13, 25, 0.0826667, 15.4, 0.0826667, 15.4, 0.0826667, 15.4 };
    constexpr double expectedDeviations3[10]{ 0 };
    {
      RunLengthFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans3[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }

    {
      RunLengthFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
      for (int counter = 0; sIt != stds->End(); ++sIt, counter++)
      {
        EXPECT_NEAR(expectedDeviations3[counter], sIt.Value(), 0.0001) << "Deviation for feature " << counter;
      }
    }

    // Test Set/Get Requested features
    const RunLengthFilterType::FeatureNameVectorPointer requestedFeatures =
      RunLengthFilterType::FeatureNameVector::New();

    requestedFeatures->push_back(static_cast<uint8_t>(itk::Statistics::RunLengthFeatureEnum::ShortRunEmphasis));
    requestedFeatures->push_back(static_cast<uint8_t>(itk::Statistics::RunLengthFeatureEnum::GreyLevelNonuniformity));
    texFilter->SetRequestedFeatures(requestedFeatures);

    texFilter->Print(std::cout, 3);

    const RunLengthFilterType::FeatureNameVector * requestedFeatures2 = texFilter->GetRequestedFeatures();

    RunLengthFilterType::FeatureNameVector::ConstIterator fIt = requestedFeatures2->Begin();
    EXPECT_EQ(fIt.Value(), static_cast<uint8_t>(itk::Statistics::RunLengthFeatureEnum::ShortRunEmphasis))
      << "Requested feature name not correctly set";
    ++fIt;

    EXPECT_EQ(fIt.Value(), static_cast<uint8_t>(itk::Statistics::RunLengthFeatureEnum::GreyLevelNonuniformity))
      << "Requested feature name not correctly set";
  }
}
