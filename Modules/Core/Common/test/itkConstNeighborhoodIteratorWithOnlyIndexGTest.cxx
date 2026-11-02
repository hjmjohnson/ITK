/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "itkConstNeighborhoodIteratorWithOnlyIndex.h"
#include "itkNeighborhoodIteratorTestCommon.hxx"
#include "itkGTest.h"

namespace
{

template <typename TImage>
typename TImage::Pointer
itkConstNeighborhoodIteratorWithOnlyIndexTestGetTestImage(int d1, int d2, int d3, int d4)
{
  itk::Size<4> sizeND;
  sizeND[0] = d1;
  sizeND[1] = d2;
  sizeND[2] = d3;
  sizeND[3] = d4;

  const itk::ImageRegion<4> RegionND{ sizeND };

  auto imageND = TImage::New();
  imageND->SetRegions(RegionND);

  return imageND;
}

template <typename TImage>
void
itkConstNeighborhoodIteratorWithOnlyIndexTestRun()
{
  const typename TImage::Pointer img = itkConstNeighborhoodIteratorWithOnlyIndexTestGetTestImage<TImage>(10, 10, 5, 3);

  using ImageType = TImage;
  using ConstNeighborhoodIteratorType = itk::ConstNeighborhoodIteratorWithOnlyIndex<ImageType>;
  using IndexType = typename ConstNeighborhoodIteratorType::IndexType;

  IndexType loc{ 4, 4, 2, 1 };

  typename ConstNeighborhoodIteratorType::RadiusType         radius{ 1, 1, 1, 1 };
  constexpr typename ConstNeighborhoodIteratorType::SizeType sz{ 10, 10, 5, 1 };
  constexpr IndexType                                        idx{ 0, 0, 0, 1 };
  typename ConstNeighborhoodIteratorType::RegionType         reg = { idx, sz };

  std::cout << "Creating ConstNeighborhoodIterator" << std::endl;
  ConstNeighborhoodIteratorType it(radius, img, reg);

  std::cout << "Moving iterator using SetLocation() to loc: " << loc << std::endl;
  it.SetLocation(loc);
  it.Print(std::cout);
  EXPECT_EQ(it.GetIndex(), loc) << "Error with SetLocation.";

  std::cout << "Test GetIndex( NeighborhoodIndex )" << std::endl;
  EXPECT_EQ(it.GetIndex(it.GetCenterNeighborhoodIndex()), loc) << "Error getting index from center nhood index.";
  IndexType truthIndex;
  for (unsigned int i = 0; i < 4; ++i)
  {
    truthIndex[i] = loc[i] - radius[i];
  }
  if (it.GetIndex(0) != truthIndex)
  {
    std::cerr << "Error getting index from nhood index 0. Returned " << it.GetIndex(0) << std::endl;
  }

  std::cout << "Testing GoToBegin()" << std::endl;
  it.GoToBegin();
  it.Print(std::cout);
  EXPECT_EQ(it.GetIndex(), idx) << "Error with GoToBegin.";

  std::cout << "Testing IsAtBegin()" << std::endl;
  std::cout << it.IsAtBegin() << std::endl;
  EXPECT_TRUE(it.IsAtBegin()) << "Error with IsAtBegin.";

  std::cout << "Testing GoToEnd()" << std::endl;
  it.GoToEnd();
  it.Print(std::cout);

  std::cout << "Testing IsAtEnd()" << std::endl;
  std::cout << it.IsAtEnd() << std::endl;
  EXPECT_TRUE(it.IsAtEnd()) << "Error with either IsAtEnd or GoToEnd.";

  std::cout << "Testing forward iteration" << std::endl;
  it.GoToBegin();
  IndexType index = it.GetIndex();
  ++it;
  EXPECT_EQ(it.GetIndex()[0], index[0] + 1) << "Error with fwd iteration";
  while (!it.IsAtEnd())
  {
    ++it;
  }

  // fwd iterate by a line
  it.GoToBegin();
  index = it.GetIndex();
  for (unsigned int i = 0; i < sz[0]; ++i)
  {
    ++it;
  }
  EXPECT_EQ(it.GetIndex()[0], index[0]) << "Error with fwd iteration by one line.";
  EXPECT_EQ(it.GetIndex()[1], index[1] + 1) << "Error with fwd iteration by one line.";

  // fwd iterate by a slice
  index = it.GetIndex();
  for (unsigned int i = 0; i < sz[0] * sz[1]; ++i)
  {
    ++it;
  }
  EXPECT_EQ(it.GetIndex()[0], index[0]) << "Error with fwd iteration by one slice.";
  EXPECT_EQ(it.GetIndex()[1], index[1]) << "Error with fwd iteration by one slice.";
  EXPECT_EQ(it.GetIndex()[2], index[2] + 1) << "Error with fwd iteration by one slice.";

  std::cout << "Testing reverse iteration" << std::endl;
  it.GoToEnd();
  index = it.GetIndex();
  --it;
  EXPECT_EQ(it.GetIndex()[3], index[3] - 1) << "Error with reverse iteration";

  index = it.GetIndex();
  for (unsigned int i = 0; i < sz[0]; ++i)
  {
    --it;
  }
  EXPECT_EQ(it.GetIndex()[0], index[0]) << "Error with reverse iteration by one line.";
  EXPECT_EQ(it.GetIndex()[1], index[1] - 1) << "Error with reverse iteration by one line.";

  index = it.GetIndex();
  for (unsigned int i = 0; i < sz[0] * sz[1]; ++i)
  {
    --it;
  }
  EXPECT_EQ(it.GetIndex()[0], index[0]) << "Error with reverse iteration by one slice.";
  EXPECT_EQ(it.GetIndex()[1], index[1]) << "Error with reverse iteration by one slice.";
  EXPECT_EQ(it.GetIndex()[2], index[2] - 1) << "Error with reverse iteration by one slice.";

  std::cout << "Moving iterator using SetLocation()" << std::endl;
  it.SetLocation(loc);
  it.Print(std::cout);

  std::cout << "Testing GetIndex()" << std::endl;
  std::cout << it.GetIndex() << std::endl;

  std::cout << "Testing GetBoundingBoxAsImageRegion" << std::endl;
  std::cout << it.GetBoundingBoxAsImageRegion() << std::endl;

  ////

  std::cout << "Testing random access iteration" << std::endl;

  const typename ImageType::Pointer ra_img =
    itkConstNeighborhoodIteratorWithOnlyIndexTestGetTestImage<TImage>(10, 10, 5, 3);
  loc[0] = 4;
  loc[1] = 4;
  loc[2] = 2;
  loc[3] = 1;

  radius[0] = radius[1] = radius[2] = radius[3] = 1;

  std::cout << "Creating ConstNeighborhoodIterator" << std::endl;
  ConstNeighborhoodIteratorType ra_it(radius, ra_img, ra_img->GetRequestedRegion());
  ConstNeighborhoodIteratorType copy_it = ra_it;

  std::cout << "Test copying." << std::endl;
  EXPECT_FALSE(copy_it != ra_it) << "Failure with copying or equality comparison.";
  EXPECT_EQ(copy_it, ra_it) << "Failure with copying or equality comparison.";
  EXPECT_GE(copy_it, ra_it) << "Failure with copying or >= or <= comparison.";
  EXPECT_LE(copy_it, ra_it) << "Failure with copying or >= or <= comparison.";

  std::cout << "Testing random access" << std::endl;
  ra_it.SetLocation(loc);

  std::cout << "Adding [1, 1, 1, 1]" << std::endl;
  auto a_off = itk::MakeFilled<OffsetType>(1);
  ra_it += a_off;
  for (unsigned int i = 0; i < 4; ++i)
  {
    IndexType ind = ra_it.GetIndex();
    EXPECT_EQ(ind[i], loc[i] + 1) << "Error with adding offset " << a_off;
  }

  std::cout << "Test iterator comparisons" << std::endl;
  EXPECT_LT(copy_it, ra_it) << "Error with < or <=.";
  EXPECT_LE(copy_it, ra_it) << "Error with < or <=.";
  EXPECT_LT(copy_it, ra_it) << "Error with < or <=.";
  EXPECT_LE(copy_it, ra_it) << "Error with < or <=.";

  std::cout << "Subtracting [1, 1, 1, 1]" << std::endl;
  ra_it -= a_off;
  for (unsigned int i = 0; i < 4; ++i)
  {
    IndexType ind = ra_it.GetIndex();
    EXPECT_EQ(ind[i], loc[i]) << "Error with subtracting offset " << a_off;
  }

  copy_it = ra_it;

  std::cout << "Adding [0 0 0 2]" << std::endl;
  a_off.Fill(0);
  a_off[3] = 2;
  ra_it += a_off;
  IndexType truth = loc;
  truth += a_off;
  for (unsigned int i = 0; i < 4; ++i)
  {
    IndexType ind = ra_it.GetIndex();
    EXPECT_EQ(ind[i], truth[i]) << "Error with adding offset " << a_off;
  }

  EXPECT_FALSE(ra_it < copy_it) << "Error with > or >= comparison after adding offset.";
  EXPECT_FALSE(ra_it <= copy_it) << "Error with > or >= comparison after adding offset.";
  EXPECT_FALSE(copy_it > ra_it) << "Error with > or >= comparison after adding offset.";
  EXPECT_FALSE(copy_it >= ra_it) << "Error with > or >= comparison after adding offset.";

  copy_it = ra_it;

  std::cout << "Adding [0 8 0 0]" << std::endl;
  a_off.Fill(0);
  a_off[1] = 8;
  ra_it += a_off;
  truth += a_off;
  for (unsigned int i = 0; i < 4; ++i)
  {
    IndexType ind = ra_it.GetIndex();
    EXPECT_EQ(ind[i], truth[i]) << "Error with adding offset " << a_off;
  }

  EXPECT_FALSE(ra_it < copy_it) << "Error with comparison after adding offset " << a_off;
  EXPECT_FALSE(ra_it <= copy_it) << "Error with comparison after adding offset " << a_off;
  EXPECT_FALSE(copy_it > ra_it) << "Error with comparison after adding offset " << a_off;
  EXPECT_FALSE(copy_it >= ra_it) << "Error with comparison after adding offset " << a_off;

  copy_it = ra_it;

  std::cout << "Adding [5 -3 2 -1]" << std::endl;
  a_off[0] = 5;
  a_off[1] = -3;
  a_off[2] = 2;
  a_off[3] = -1;
  ra_it += a_off;
  truth += a_off;
  for (unsigned int i = 0; i < 4; ++i)
  {
    IndexType ind = ra_it.GetIndex();
    EXPECT_EQ(ind[i], truth[i]) << "Error with adding offset " << a_off;
  }

  EXPECT_FALSE(ra_it > copy_it) << "Error with comparison after adding offset.";
  EXPECT_FALSE(ra_it >= copy_it) << "Error with comparison after adding offset.";
  EXPECT_FALSE(copy_it < ra_it) << "Error with comparison after adding offset.";
  EXPECT_FALSE(copy_it <= ra_it) << "Error with comparison after adding offset.";

  //
  // Test IndexInBounds
  //
  std::cout << "Testing IndexInBounds" << std::endl;
  constexpr int                     dims[4]{ 13, 11, 9, 7 };
  const typename ImageType::Pointer iib_img =
    itkConstNeighborhoodIteratorWithOnlyIndexTestGetTestImage<TImage>(dims[0], dims[1], dims[2], dims[3]);
  radius[0] = 4;
  radius[1] = 3;
  radius[2] = 2;
  radius[3] = 1;

  std::cout << "Creating ConstNeighborhoodIterator" << std::endl;
  using IteratorType = ConstNeighborhoodIteratorType;
  IteratorType                      iib_it(radius, iib_img, iib_img->GetRequestedRegion());
  typename IteratorType::OffsetType resultOffset;
  typename IteratorType::OffsetType internalIndex;

  typename IteratorType::IndexType centerLoc;
  centerLoc[0] = static_cast<typename IteratorType::IndexType::IndexValueType>(dims[0] / 2);
  centerLoc[1] = static_cast<typename IteratorType::IndexType::IndexValueType>(dims[1] / 2);
  centerLoc[2] = static_cast<typename IteratorType::IndexType::IndexValueType>(dims[2] / 2);
  centerLoc[3] = static_cast<typename IteratorType::IndexType::IndexValueType>(dims[3] / 2);

  iib_it.GoToBegin();
  bool inside = iib_it.IndexInBounds(0, internalIndex, resultOffset);
  EXPECT_FALSE(inside) << "IndexInBounds failed for index 0, expected false.";
  for (unsigned int n = 0; n < 4; ++n)
  {
    EXPECT_EQ(resultOffset[n], static_cast<itk::OffsetValueType>(radius[n]))
      << "IndexInBounds failed. Expected resultOffset of " << radius << ", but got " << resultOffset;
  }
  inside = iib_it.IndexInBounds(iib_it.Size() - 1, internalIndex, resultOffset);
  EXPECT_TRUE(inside) << "IndexInBounds failed for index size-1, expected true.";
  for (unsigned int n = 0; n < 4; ++n)
  {
    EXPECT_EQ(resultOffset[n], 0) << "IndexInBounds failed. Expected resultOffset of 0, but got " << resultOffset;
  }

  // Test min boundary by dimension
  for (unsigned int n = 0; n < 4; ++n)
  {
    typename IteratorType::IndexType boundaryLoc = centerLoc;
    boundaryLoc[n] = 0;
    iib_it.SetLocation(boundaryLoc);
    EXPECT_FALSE(iib_it.IndexInBounds(0, internalIndex, resultOffset))
      << "IndexInBounds failed for min boundaryLoc: " << boundaryLoc << " and dimension: " << n << ". Expected false.";
  }

  // Test max boundary by dimension
  for (unsigned int n = 0; n < 4; ++n)
  {
    typename IteratorType::IndexType boundaryLoc = centerLoc;
    boundaryLoc[n] = dims[n] - 1;
    iib_it.SetLocation(boundaryLoc);
    EXPECT_FALSE(iib_it.IndexInBounds(iib_it.Size() - 1, internalIndex, resultOffset))
      << "IndexInBounds failed for max boundaryLoc: " << boundaryLoc << " and dimension: " << n << ". Expected false.";
  }

  // Test center
  iib_it.SetLocation(centerLoc);
  inside = iib_it.IndexInBounds(0, internalIndex, resultOffset);
  EXPECT_TRUE(inside) << "IndexInBounds failed for index 0, expected true.";
}
} // namespace

TEST(ConstNeighborhoodIteratorWithOnlyIndex, ConvertedLegacyTest)
{
  std::cout << "*** Testing with itk::Image" << std::endl << std::endl;
  {
    SCOPED_TRACE("itk::Image");
    itkConstNeighborhoodIteratorWithOnlyIndexTestRun<itk::Image<signed char, 4>>();
  }

  std::cout << std::endl << std::endl << "*** Testing with itk::ImageBase" << std::endl << std::endl;
  {
    SCOPED_TRACE("itk::ImageBase");
    itkConstNeighborhoodIteratorWithOnlyIndexTestRun<itk::ImageBase<4>>();
  }
}
