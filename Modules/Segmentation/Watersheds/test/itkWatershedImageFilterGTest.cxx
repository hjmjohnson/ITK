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

#include "itkWatershedImageFilter.h"
#include "itkWatershedEquivalenceRelabeler.h"
#include "itkWatershedBoundaryResolver.h"
#include "itkSimpleFilterWatcher.h"
#include "itkGTest.h"


TEST(WatershedImageFilter, ConvertedLegacyTest)
{

  constexpr unsigned int Dimension{ 2 };

  using PixelType = float;
  using ImageType2D = itk::Image<PixelType, Dimension>;
  using LongImageType2D = itk::Image<itk::IdentifierType, Dimension>;

  constexpr itk::Size<Dimension> size{ 314, 314 };
  itk::Index<Dimension>          origin{};
  itk::ImageRegion<Dimension>    region = { origin, size };

  auto image2D = ImageType2D::New();
  image2D->SetRegions(region);
  image2D->Allocate();

  auto longimage2D = LongImageType2D::CreateInitialized(region);

  itk::ImageRegionIterator<ImageType2D> it2D(image2D, image2D->GetRequestedRegion());

  for (float q = 0.00f; !it2D.IsAtEnd(); ++it2D)
  {
    it2D.Value() = std::sin(q);
    q += 0.10f;
  }

  // Test various objects associated to itk::WatershedImageFilter
  //

  // Test EquivalenceRelabeler
  const itk::EquivalencyTable::Pointer table = itk::EquivalencyTable::New();

  const itk::watershed::EquivalenceRelabeler<LongImageType2D::PixelType, Dimension>::Pointer eq =
    itk::watershed::EquivalenceRelabeler<LongImageType2D::PixelType, Dimension>::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(eq, EquivalenceRelabeler, ProcessObject);


  eq->SetInputImage(longimage2D);

  eq->SetEquivalencyTable(table);
  EXPECT_EQ(table, eq->GetEquivalencyTable());


  ASSERT_NO_THROW(eq->Update());

  // Test WatershedMiniPipelineProgressCommand
  // Forcing the execution of the const Execute method which is not normally called.
  const itk::WatershedMiniPipelineProgressCommand::Pointer wmppc = itk::WatershedMiniPipelineProgressCommand::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(wmppc, WatershedMiniPipelineProgressCommand, Command);

  constexpr double count{ 2.0 };
  wmppc->SetCount(count);
  EXPECT_EQ(count, wmppc->GetCount());

  constexpr unsigned int numberOfFilters{ 2 };
  wmppc->SetNumberOfFilters(numberOfFilters);
  EXPECT_EQ(numberOfFilters, wmppc->GetNumberOfFilters());

  wmppc->SetFilter(eq);
  EXPECT_EQ(eq, wmppc->GetFilter());

  const itk::ProcessObject * constp = eq.GetPointer();
  wmppc->Execute(constp, itk::ProgressEvent());
  wmppc->Execute(eq, itk::ProgressEvent());

  // Test watershed::BoundaryResolver
  const itk::watershed::BoundaryResolver<PixelType, Dimension>::Pointer br =
    itk::watershed::BoundaryResolver<PixelType, Dimension>::New();
  ASSERT_FALSE(br.IsNull());

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(br, BoundaryResolver, ProcessObject);

  const itk::watershed::Boundary<PixelType, 1>::Pointer boundaryA = itk::watershed::Boundary<PixelType, 1>::New();
  ASSERT_FALSE(boundaryA.IsNull());

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(boundaryA, Boundary, DataObject);

  const itk::watershed::Boundary<PixelType, 1>::Pointer boundaryB = itk::watershed::Boundary<PixelType, 1>::New();
  EXPECT_FALSE(boundaryB.IsNull());


  const itk::WatershedImageFilter<ImageType2D>::Pointer watershedFilter = itk::WatershedImageFilter<ImageType2D>::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(watershedFilter, WatershedImageFilter, ImageToImageFilter);

  const itk::SimpleFilterWatcher watchIt(watershedFilter, "WatershedImageFilter");

  constexpr double threshold{ .05 };
  watershedFilter->SetThreshold(threshold);
  EXPECT_EQ(threshold, watershedFilter->GetThreshold());

  constexpr double level{ 1.0 };
  watershedFilter->SetLevel(level);
  EXPECT_EQ(level, watershedFilter->GetLevel());

  unsigned int inputId = 1;
  EXPECT_THROW(watershedFilter->SetInput(inputId, image2D), itk::ExceptionObject);

  watershedFilter->SetInput(image2D);
  const ImageType2D * input = watershedFilter->GetInput();

  inputId = 0;
  watershedFilter->SetInput(inputId, image2D);
  EXPECT_EQ(input, watershedFilter->GetInput());


  ASSERT_NO_THROW(watershedFilter->Update());


  std::cout << "Test finished." << std::endl;
}
