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

#include "itkScalarImageToTextureFeaturesFilter.h"
#include "itkDenseFrequencyContainer2.h"
#include "itkGTest.h"

TEST(ScalarImageToTextureFeaturesFilter, ConvertedLegacyTest)
{

  // Data definitions
  constexpr unsigned int IMGWIDTH{ 5 };
  constexpr unsigned int IMGHEIGHT{ 5 };
  constexpr unsigned int NDIMENSION{ 2 };


  //------------------------------------------------------
  // Create a simple test images
  //------------------------------------------------------
  using InputImageType = itk::Image<unsigned char, NDIMENSION>;
  using MaskImageType = itk::Image<bool, NDIMENSION>;

  using InputImageIterator = itk::ImageRegionIterator<InputImageType>;
  using MaskImageIterator = itk::ImageRegionIterator<MaskImageType>;


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

  auto mask = MaskImageType::New();
  mask->SetRegions(region);
  mask->Allocate();

  // setup the iterator
  MaskImageIterator maskIt(mask, mask->GetBufferedRegion());
  maskIt.GoToBegin();
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; j++, ++maskIt)
    {
      maskIt.Set(true);
    }

  //--------------------------------------------------------------------------
  // Test the texFilter
  //--------------------------------------------------------------------------
  {

    using TextureFilterType = itk::Statistics::
      ScalarImageToTextureFeaturesFilter<InputImageType, itk::Statistics::DenseFrequencyContainer2, MaskImageType>;

    // First test: just use the defaults.
    auto texFilter = TextureFilterType::New();
    // Invoke update before adding an input. An exception should be
    // thrown.
    EXPECT_THROW(texFilter->Update(), itk::ExceptionObject)
      << "Failed to throw expected exception due to nullptr input: ";

    texFilter->ResetPipeline();

    EXPECT_EQ(texFilter->GetInput(), nullptr) << "GetInput() should return nullptr since the input is not set yet ";

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
    texFilter->SetMaskImage(mask);
    texFilter->Update();

    texFilter->Print(std::cout);

    // Test GetInput
    EXPECT_EQ(texFilter->GetInput(), image);

    // Test GetMaskImage
    EXPECT_EQ(texFilter->GetMaskImage(), mask);

    TextureFilterType::FeatureValueVectorPointer means = texFilter->GetFeatureMeans();
    TextureFilterType::FeatureValueVectorPointer stds = texFilter->GetFeatureStandardDeviations();

    constexpr double expectedMeans[6]{ 0.505, 0.992738, 0.625, 0.75, 0.0959999, 0.2688 };
    constexpr double expectedDeviations[6]{ 0.00866027, 0.0125788, 0.216506351, 0.433012702, 0.166277, 0.465575 };


    {
      TextureFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }

    {
      TextureFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
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

    constexpr double expectedMeans2[6]{ 0.5, 1.0, 0.5, 1.0, 0.0, 0.0 };
    constexpr double expectedDeviations2[6]{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    {
      TextureFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans2[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }

    {
      TextureFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
      for (int counter = 0; sIt != stds->End(); ++sIt, counter++)
      {
        EXPECT_NEAR(expectedDeviations2[counter], sIt.Value(), 0.0001) << "Deviation for feature " << counter;
      }
    }

    // Rerun the feature generation setting an offset
    TextureFilterType::OffsetType offset;
    offset[0] = -1;
    offset[1] = -1;

    TextureFilterType::OffsetVectorPointer offsets;

    offsets = TextureFilterType::OffsetVector::New();

    offsets->push_back(offset);
    texFilter->SetOffsets(offsets);

    const TextureFilterType::OffsetVector * offsets2 = texFilter->GetOffsets();

    for (TextureFilterType::OffsetVector::ConstIterator vIt = offsets->Begin(), vIt2 = offsets2->Begin();
         vIt != offsets->End();
         ++vIt, ++vIt2)
    {
      EXPECT_EQ(vIt.Value(), vIt2.Value()) << "Offsets not properly set";
    }

    texFilter->Update();

    means = texFilter->GetFeatureMeans();
    stds = texFilter->GetFeatureStandardDeviations();

    constexpr double expectedMeans3[6]{ 0.5, 1.0, 0.5, 1.0, 0.0, 0.0 };
    constexpr double expectedDeviations3[6]{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    {
      TextureFilterType::FeatureValueVector::ConstIterator mIt = means->Begin();
      for (int counter = 0; mIt != means->End(); ++mIt, counter++)
      {
        EXPECT_NEAR(expectedMeans3[counter], mIt.Value(), 0.0001) << "Mean for feature " << counter;
      }
    }

    {
      TextureFilterType::FeatureValueVector::ConstIterator sIt = stds->Begin();
      for (int counter = 0; sIt != stds->End(); ++sIt, counter++)
      {
        EXPECT_NEAR(expectedDeviations3[counter], sIt.Value(), 0.0001) << "Deviation for feature " << counter;
      }
    }

    // Test Set/Get Requested features
    const TextureFilterType::FeatureNameVectorPointer requestedFeatures = TextureFilterType::FeatureNameVector::New();

    requestedFeatures->push_back(
      static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Inertia));
    requestedFeatures->push_back(
      static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterShade));
    texFilter->SetRequestedFeatures(requestedFeatures);

    const TextureFilterType::FeatureNameVector * requestedFeatures2 = texFilter->GetRequestedFeatures();

    TextureFilterType::FeatureNameVector::ConstIterator fIt;

    fIt = requestedFeatures2->Begin();
    EXPECT_EQ(fIt.Value(),
              static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Inertia))
      << "Requested feature name not correctly set";
    ++fIt;

    EXPECT_EQ(
      fIt.Value(),
      static_cast<uint8_t>(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterShade))
      << "Requested feature name not correctly set";
  }
}
