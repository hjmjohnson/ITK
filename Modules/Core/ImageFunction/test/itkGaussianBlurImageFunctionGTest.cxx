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

#include "itkMath.h"
#include "itkGaussianBlurImageFunction.h"
#include "itkGTest.h"

TEST(GaussianBlurImageFunction, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 2 };
  using PixelType = float;
  using ImageType = itk::Image<PixelType, Dimension>;
  using GFunctionType = itk::GaussianBlurImageFunction<ImageType>;

  // Create and allocate the image
  constexpr ImageType::SizeType size{ 50, 50 };
  ImageType::RegionType         region = { size };

  auto image = ImageType::CreateInitialized(region);

  // Fill the image with a straight line
  for (unsigned int i = 0; i < 50; ++i)
  {
    ImageType::IndexType ind{ i, 25 };
    image->SetPixel(ind, 1);
    ind[1] = 26;
    image->SetPixel(ind, 1);
  }

  // Test the derivative of Gaussian image function
  auto gaussianFunction = GFunctionType::New();
  gaussianFunction->SetInputImage(image);
  auto index = itk::Index<2>::Filled(25);

  // Testing Set/GetVariance()
  gaussianFunction->SetSigma(5.0);
  const GFunctionType::SigmaArrayType & sigma = gaussianFunction->GetSigma();

  for (unsigned int i = 0; i < Dimension; ++i)
  {
    EXPECT_EQ(sigma[i], 5.0);
  }

  gaussianFunction->SetSigma(sigma);
  EXPECT_EQ(sigma, gaussianFunction->GetSigma());

  // Testing Set/GetExtent()
  gaussianFunction->SetExtent(5.0);
  const GFunctionType::ExtentArrayType & ext = gaussianFunction->GetExtent();

  for (unsigned int i = 0; i < Dimension; ++i)
  {
    EXPECT_EQ(ext[i], 5.0);
  }

  gaussianFunction->SetExtent(ext);
  EXPECT_EQ(ext, gaussianFunction->GetExtent());


  // Testing Set/GetMaximumError()
  {
    auto setError = itk::MakeFilled<GFunctionType::ErrorArrayType>(0.05);
    gaussianFunction->SetMaximumError(setError);

    const GFunctionType::ErrorArrayType & readError = gaussianFunction->GetMaximumError();

    for (unsigned int i = 0; i < Dimension; ++i)
    {
      EXPECT_NEAR(setError[i], readError[i], 1e-6);
    }
  }

  // Testing Set/GetMaximumKernelWidth()
  {
    constexpr int setKernelWidth{ 47 };

    gaussianFunction->SetMaximumKernelWidth(setKernelWidth);

    const int readKernelWidth = gaussianFunction->GetMaximumKernelWidth();

    EXPECT_EQ(readKernelWidth, setKernelWidth);
  }

  // Testing Set/GetUseImageSpacing()
  {
    bool useImageSpacing = true;

    gaussianFunction->SetUseImageSpacing(useImageSpacing);
    EXPECT_EQ(gaussianFunction->GetUseImageSpacing(), useImageSpacing) << "Set/GetUseImageSpacing() FAILED !";

    useImageSpacing = false;

    gaussianFunction->SetUseImageSpacing(useImageSpacing);
    EXPECT_EQ(gaussianFunction->GetUseImageSpacing(), useImageSpacing) << "Set/GetUseImageSpacing() FAILED !";

    gaussianFunction->UseImageSpacingOn();
    EXPECT_TRUE(gaussianFunction->GetUseImageSpacing()) << "Set/GetUseImageSpacing() FAILED !";

    gaussianFunction->UseImageSpacingOff();
    EXPECT_FALSE(gaussianFunction->GetUseImageSpacing()) << "Set/GetUseImageSpacing() FAILED !";


    gaussianFunction->UseImageSpacingOn(); // leave it ON for the next test.
  }


  const GFunctionType::OutputType blurredvalue_index = gaussianFunction->EvaluateAtIndex(index);

  GFunctionType::PointType pt;
  pt[0] = 25.0;
  pt[1] = 25.0;
  const GFunctionType::OutputType blurredvalue_point = gaussianFunction->Evaluate(pt);


  auto                            continuousIndex = itk::MakeFilled<GFunctionType::ContinuousIndexType>(25);
  const GFunctionType::OutputType blurredvalue_continuousIndex =
    gaussianFunction->EvaluateAtContinuousIndex(continuousIndex);


  // Testing Evaluate(), EvaluateAtIndex() and EvaluateIndex
  EXPECT_NEAR(blurredvalue_index, blurredvalue_point, 0.01)
    << blurredvalue_index << " : " << blurredvalue_point << " : " << blurredvalue_continuousIndex;
  EXPECT_DOUBLE_EQ(blurredvalue_point, blurredvalue_continuousIndex)
    << blurredvalue_index << " : " << blurredvalue_point << " : " << blurredvalue_continuousIndex;

  // Testing Evaluate()
  EXPECT_NEAR(blurredvalue_point, 0.158, 0.1);

  gaussianFunction->Print(std::cout);
}
