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
#include "itkTestingHashImageFilter.h"
#include "itkImage.h"
#include "itkTestingExtractSliceImageFilter.h"
#include "itkGTest.h"

TEST(TestingExtractSliceImageFilter, ConvertedLegacyTest)
{

  using PixelType = unsigned char;
  constexpr unsigned int InputDimension{ 3 };
  constexpr unsigned int OutputDimension{ 2 };

  using InputImageType = itk::Image<PixelType, InputDimension>;
  using OutputImageType = itk::Image<PixelType, OutputDimension>;

  using FilterType = itk::Testing::ExtractSliceImageFilter<InputImageType, OutputImageType>;

  auto filter = FilterType::New();

  auto size = InputImageType::SizeType::Filled(20);

  InputImageType::RegionType region;
  region.SetSize(size);

  auto inputImage = InputImageType::CreateInitialized(region);

  InputImageType::DirectionType direction;
  direction[0][0] = 1.0;
  direction[0][1] = 0.5;
  direction[0][2] = 0.0;
  direction[1][0] = 0.5;
  direction[1][1] = 1.0;
  direction[1][2] = 0.5;
  direction[2][0] = 0.5;
  direction[2][1] = 0.5;
  direction[2][2] = 1.0;

  inputImage->SetDirection(direction);

  InputImageType::SpacingType spacing;
  spacing[0] = 2.5;
  spacing[1] = 1.5;
  spacing[2] = 3.5;

  inputImage->SetSpacing(spacing);

  filter->SetInput(inputImage);

  FilterType::InputImageRegionType extractRegion = inputImage->GetBufferedRegion();

  InputImageType::SizeType regionSize = extractRegion.GetSize();

  // expect exception, because for output dimension = 2, one of the size
  // components must be zero.
  EXPECT_THROW(filter->SetExtractionRegion(extractRegion), itk::ExceptionObject);

  // Set properly, one of the size components to zero.
  regionSize[2] = 0;
  extractRegion.SetSize(regionSize);

  // Now it should be good, with the zero inserted.
  EXPECT_NO_THROW(filter->SetExtractionRegion(extractRegion));
  EXPECT_EQ(extractRegion, filter->GetExtractionRegion());

  FilterType::DIRECTIONCOLLAPSESTRATEGY strategy =
    itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::DIRECTIONCOLLAPSETOUNKOWN;

  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_THROW(filter->Update(), itk::ExceptionObject);

  EXPECT_THROW(
    filter->SetDirectionCollapseToStrategy(itk::Testing::ExtractSliceImageFilterEnums::
                                             TestExtractSliceImageFilterCollapseStrategy::DIRECTIONCOLLAPSETOUNKOWN),
    itk::ExceptionObject);

  filter->SetDirectionCollapseToIdentity();
  strategy = itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
    DIRECTIONCOLLAPSETOIDENTITY;
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  filter->SetDirectionCollapseToGuess();
  strategy =
    itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::DIRECTIONCOLLAPSETOGUESS;
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  filter->SetDirectionCollapseToSubmatrix();
  strategy = itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
    DIRECTIONCOLLAPSETOSUBMATRIX;
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  strategy = itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
    DIRECTIONCOLLAPSETOIDENTITY;
  filter->SetDirectionCollapseToStrategy(strategy);
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  strategy =
    itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::DIRECTIONCOLLAPSETOGUESS;
  filter->SetDirectionCollapseToStrategy(strategy);
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  strategy = itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
    DIRECTIONCOLLAPSETOSUBMATRIX;
  filter->SetDirectionCollapseToStrategy(strategy);
  EXPECT_EQ(strategy, filter->GetDirectionCollapseToStrategy());
  EXPECT_NO_THROW(filter->Update());

  EXPECT_NO_THROW(filter->Update());

  // Test streaming enumeration for HashImageFilterEnums::HashFunction elements
  const std::set<itk::Testing::HashImageFilterEnums::HashFunction> allHashFunction{
    itk::Testing::HashImageFilterEnums::HashFunction::MD5
  };
  for (const auto & ee : allHashFunction)
  {
    std::cout << "STREAMED ENUM VALUE HashImageFilterEnums::HashFunction: " << ee << std::endl;
  }

  // Test streaming enumeration for ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy elements
  const std::set<itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy>
    allTestExtractSliceImageFilterCollapseStrategy{
      itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
        DIRECTIONCOLLAPSETOUNKOWN,
      itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
        DIRECTIONCOLLAPSETOIDENTITY,
      itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::
        DIRECTIONCOLLAPSETOSUBMATRIX,
      itk::Testing::ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy::DIRECTIONCOLLAPSETOGUESS
    };
  for (const auto & ee : allTestExtractSliceImageFilterCollapseStrategy)
  {
    std::cout << "STREAMED ENUM VALUE ExtractSliceImageFilterEnums::TestExtractSliceImageFilterCollapseStrategy: " << ee
              << std::endl;
  }

  // Exercise PrintSelf()
  filter->Print(std::cout);
}
