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

#include "itkImageFileReader.h"
#include "itkVoronoiSegmentationRGBImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkMath.h"
#include "itkGTest.h"
#include "vnl/vnl_sample.h"

#include <algorithm> // For generate.
#include <iostream>
#include <random> // For mt19937.

// type alias for all functions
using PixelType = itk::RGBPixel<unsigned char>;
using PixelComponentType = PixelType::ComponentType;
using ImageType = itk::Image<PixelType, 2>;
using SegmentationType = itk::Image<unsigned char, 2>;
using ReaderType = itk::ImageFileReader<ImageType>;
using FilterType = itk::VoronoiSegmentationRGBImageFilter<ImageType, SegmentationType>;
using BinaryObjectImage = FilterType::BinaryObjectImage;

namespace
{

//
// global constants
//
constexpr unsigned int  width{ 256 };
constexpr unsigned int  height{ 256 };
constexpr unsigned char bgMean{ 64 };
constexpr unsigned char bgStd{ 10 };
constexpr unsigned char fgMean{ 128 };
constexpr unsigned char fgStd{ 5 };
constexpr unsigned int  objAStartX{ 30 };
constexpr unsigned int  objAEndX{ 94 };
constexpr unsigned int  objAStartY{ 30 };
constexpr unsigned int  objAEndY{ 94 };
constexpr unsigned int  objBStartX{ 150 };
constexpr unsigned int  objBEndX{ 214 };
constexpr unsigned int  objBStartY{ 150 };
constexpr unsigned int  objBEndY{ 214 };
constexpr double        minCorrectRate{ .875 }; // .875 is all classified as background


//
// Function to set up input image
//
ImageType::Pointer
SetUpInputImage()
{
  // initialize the test input image
  auto                          inputImage = ImageType::New();
  constexpr ImageType::SizeType size{ width, height };
  ImageType::RegionType         region;
  region.SetSize(size);
  inputImage->SetRegions(region);
  inputImage->Allocate();

  std::mt19937 randomNumberEngine{};

  // add background random field
  std::uniform_int_distribution<> backgroundRandomNumberDistribution(bgMean - bgStd, bgMean + bgStd);

  itk::ImageRegionIterator<ImageType> iter(inputImage, region);
  while (!iter.IsAtEnd())
  {
    PixelType px;
    std::generate(px.begin(), px.end(), [&randomNumberEngine, &backgroundRandomNumberDistribution] {
      return static_cast<PixelComponentType>(backgroundRandomNumberDistribution(randomNumberEngine));
    });
    iter.Set(px);
    ++iter;
  }

  // add objects to image
  std::uniform_int_distribution<> forgroundRandomNumberDistribution(fgMean - fgStd, fgMean + fgStd);

  for (unsigned int x = objAStartX; x < objAEndX; ++x)
  {
    for (unsigned int y = objAStartY; y < objAEndY; ++y)
    {
      ImageType::IndexType idx;
      idx[0] = x;
      idx[1] = y;

      PixelType px;
      std::generate(px.begin(), px.end(), [&randomNumberEngine, &forgroundRandomNumberDistribution] {
        return static_cast<PixelComponentType>(forgroundRandomNumberDistribution(randomNumberEngine));
      });
      inputImage->SetPixel(idx, px);
    }
  }
  for (unsigned int x = objBStartX; x < objBEndX; ++x)
  {
    for (unsigned int y = objBStartY; y < objBEndY; ++y)
    {
      ImageType::IndexType idx;
      idx[0] = x;
      idx[1] = y;

      PixelType px;
      std::generate(px.begin(), px.end(), [&randomNumberEngine, &forgroundRandomNumberDistribution] {
        return static_cast<PixelComponentType>(forgroundRandomNumberDistribution(randomNumberEngine));
      });
      inputImage->SetPixel(idx, px);
    }
  }

  return inputImage;
}


//
// Function to check the results
//
double
CheckResults(SegmentationType::Pointer outputImage)
{
  // walk the image and count the correctly segmented pixels
  unsigned int correctInterior = 0;
  unsigned int correctExterior = 0;
  unsigned int falseInterior = 0;
  unsigned int falseExterior = 0;
  for (unsigned int x = 0; x < width; ++x)
  {
    for (unsigned int y = 0; y < height; ++y)
    {
      SegmentationType::IndexType idx;
      idx[0] = x;
      idx[1] = y;

      bool inInterior = false;

      // check if in objA
      if (x >= objAStartX && x < objAEndX && y >= objAStartY && y < objAEndY)
      {
        inInterior = true;
      }

      // check if in objB
      else if (x >= objBStartX && x < objBEndX && y >= objBStartY && y < objBEndY)
      {
        inInterior = true;
      }

      if (inInterior)
      {
        if (outputImage->GetPixel(idx) == 1)
        {
          correctInterior++;
        }
        else
        {
          falseExterior++;
        }
      }
      else
      {
        if (outputImage->GetPixel(idx) == 0)
        {
          correctExterior++;
        }
        else
        {
          falseInterior++;
        }
      }
    }
  }

  // report the results and fail if too many incorrectly segmented
  std::cout << "Correct Interior: " << correctInterior << std::endl;
  std::cout << "Correct Exterior: " << correctExterior << std::endl;
  std::cout << "False Interior: " << falseInterior << std::endl;
  std::cout << "False Exterior: " << falseExterior << std::endl;
  const double percentCorrect =
    static_cast<double>(correctInterior + correctExterior) / static_cast<double>(width * height);
  std::cout << "Percent Correct = " << percentCorrect * 100 << '%' << std::endl;

  return percentCorrect;
}


//
// Test with no prior
//
void
TestNoPrior(ImageType::Pointer inputImage)
{

  std::cout << "Beginning no-prior test" << std::endl;

  // set up the filter
  auto filter = FilterType::New();
  std::cout << "Setting filter input" << std::endl;
  filter->SetInput(inputImage);

  // explicitly set mean and standard deviation
  std::cout << "Setting up mean and standard deviation for filter" << std::endl;
  double mean[6];
  mean[0] = fgMean;
  mean[1] = fgMean;
  mean[2] = fgMean;
  mean[3] = 0;
  mean[4] = 0;
  mean[5] = 50;
  filter->SetMean(mean);
  double standardDeviation[6];
  standardDeviation[0] = fgStd;
  standardDeviation[1] = fgStd;
  standardDeviation[2] = fgStd;
  standardDeviation[3] = 255;
  standardDeviation[4] = 10;
  standardDeviation[5] = 10;
  filter->SetSTD(standardDeviation);
  filter->SetNumberOfSeeds(400);
  filter->SetSteps(5);
  filter->SetMaxValueOfRGB(255);

  // test GetMaxValueOfRGB
  std::cout << "Checking GetMaxValueOfRGB" << std::endl;
  EXPECT_EQ(filter->GetMaxValueOfRGB(), 255) << "[FAILED] Didn't set max RGB correctly";

  // run the filter
  std::cout << "Running the filter" << std::endl;
  filter->Update();

  // check the results
  std::cout << "Checking the filter results" << std::endl;
  const double percentCorrect = CheckResults(filter->GetOutput());
  EXPECT_GT(percentCorrect, minCorrectRate)
    << "[FAILED] Did not segment over " << minCorrectRate * 100 << "% correctly";
}


//
// Test with a prior
//
void
TestWithPrior(ImageType::Pointer inputImage)
{
  // set up the filter
  std::cout << "Setting up the filter and image" << std::endl;
  auto filter = FilterType::New();
  filter->SetInput(inputImage);

  // set up the prior
  std::cout << "Setting up the prior image" << std::endl;
  auto                                  prior = BinaryObjectImage::New();
  constexpr BinaryObjectImage::SizeType size{ width, height };
  BinaryObjectImage::RegionType         region;
  region.SetSize(size);
  prior->SetRegions(region);
  prior->Allocate();

  // create prior as 100% segmentation
  for (unsigned int x = 0; x < width; ++x)
  {
    for (unsigned int y = 0; y < height; ++y)
    {
      SegmentationType::IndexType idx;
      idx[0] = x;
      idx[1] = y;

      bool inInterior = false;

      // check if in objA
      if (x >= objAStartX && x < objAEndX && y >= objAStartY && y < objAEndY)
      {
        inInterior = true;
      }

      // check if in objB
      else if (x >= objBStartX && x < objBEndX && y >= objBStartY && y < objBEndY)
      {
        inInterior = true;
      }

      if (inInterior)
      {
        prior->SetPixel(idx, 1);
      }
      else
      {
        prior->SetPixel(idx, 0);
      }
    }
  }

  // add prior to filter
  filter->TakeAPrior(prior);

  // run the filter
  std::cout << "Running the filter" << std::endl;
  filter->Update();

  // check the results
  std::cout << "Checking the results of the filter" << std::endl;
  const double percentCorrect = CheckResults(filter->GetOutput());
  EXPECT_GT(percentCorrect, minCorrectRate)
    << "[FAILED] Did not segment over " << minCorrectRate * 100 << "% correctly";
}

} // namespace


//
// Main test function
//
TEST(VoronoiSegmentationRGBImageFilter, ConvertedLegacyTest)
{
  // The legacy test driver reseeds vnl_sample before every test.
  vnl_sample_reseed(8775070);
  // set up the input image
  const ImageType::Pointer inputImage = SetUpInputImage();

  // test without prior
  std::cout << "[Running test without prior]" << std::endl;
  TestNoPrior(inputImage);
  std::cout << std::endl;

  // test with prior
  std::cout << "[Running test with prior]" << std::endl;
  TestWithPrior(inputImage);

  // test set/get TestMean
  auto filter = FilterType::New();
  filter->SetTestMean(fgMean, fgMean, fgMean);
  unsigned int testMean[3];
  filter->GetTestMean(testMean);
  EXPECT_EQ(testMean[0], fgMean);
  EXPECT_EQ(testMean[1], fgMean);
  EXPECT_EQ(testMean[2], fgMean);

  // test set/get TestSTD
  filter->SetTestSTD(fgStd, fgStd, fgStd);
  unsigned int testStd[3];
  filter->GetTestSTD(testStd);
  EXPECT_EQ(testStd[0], fgStd);
  EXPECT_EQ(testStd[1], fgStd);
  EXPECT_EQ(testStd[2], fgStd);

  // test set/get MeanPercentError
  double meanPercentErrorIn[6] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
  filter->SetMeanPercentError(meanPercentErrorIn);
  double meanPercentErrorOut[6];
  filter->GetMeanPercentError(meanPercentErrorOut);
  EXPECT_EQ(meanPercentErrorOut[0], 0.1);
  EXPECT_EQ(meanPercentErrorOut[1], 0.1);
  EXPECT_EQ(meanPercentErrorOut[2], 0.1);
  EXPECT_EQ(meanPercentErrorOut[3], 0.1);
  EXPECT_EQ(meanPercentErrorOut[4], 0.1);
  EXPECT_EQ(meanPercentErrorOut[5], 0.1);

  // test set/get STDPercentError
  double stdPercentErrorIn[6] = { 0.1, 0.1, 0.1, 0.1, 0.1, 0.1 };
  filter->SetSTDPercentError(stdPercentErrorIn);
  double stdPercentErrorOut[6];
  filter->GetSTDPercentError(stdPercentErrorOut);
  EXPECT_EQ(stdPercentErrorOut[0], 0.1);
  EXPECT_EQ(stdPercentErrorOut[1], 0.1);
  EXPECT_EQ(stdPercentErrorOut[2], 0.1);
  EXPECT_EQ(stdPercentErrorOut[3], 0.1);
  EXPECT_EQ(stdPercentErrorOut[4], 0.1);
  EXPECT_EQ(stdPercentErrorOut[5], 0.1);

  // test get mean/std tolerance
  double meanTolerance[6];
  filter->GetMeanTolerance(meanTolerance);
  std::cout << "Mean Tolerance = (" << meanTolerance[0] << ',' << meanTolerance[1] << ',' << meanTolerance[2] << ','
            << meanTolerance[3] << ',' << meanTolerance[4] << ',' << meanTolerance[5] << ')' << std::endl;
  double stdTolerance[6];
  filter->GetSTDTolerance(stdTolerance);
  std::cout << "STD Tolerance = (" << stdTolerance[0] << ',' << stdTolerance[1] << ',' << stdTolerance[2] << ','
            << stdTolerance[3] << ',' << stdTolerance[4] << ',' << stdTolerance[5] << ')' << std::endl;

  // test type information
  EXPECT_STREQ(filter->GetNameOfClass(), "VoronoiSegmentationRGBImageFilter");

  // test printing
  std::cout << filter << std::endl;
}
