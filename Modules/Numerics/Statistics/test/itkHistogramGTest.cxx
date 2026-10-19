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

#include <set>
#include "itkHistogramToRunLengthFeaturesFilter.h"
#include "itkMath.h"
#include "itkHistogram.h"
#include "itkSample.h"
#include "itkGTest.h"

TEST(Histogram, ConvertedLegacyTest)
{
  using MeasurementType = float;
  constexpr unsigned int numberOfComponents{ 3 };

  // create a histogram with 3 components measurement vectors
  using HistogramType = itk::Statistics::Histogram<MeasurementType, itk::Statistics::DenseFrequencyContainer2>;
  auto histogram = HistogramType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(histogram, Histogram, Sample);

  using MeasurementVectorType = HistogramType::MeasurementVectorType;
  using InstanceIdentifier = HistogramType::InstanceIdentifier;
  using IndexType = HistogramType::IndexType;

  // initializes a 64 x 64 x 64 histogram with equal size interval
  HistogramType::SizeType size(numberOfComponents, 64);
  const unsigned long     totalSize = size[0] * size[1] * size[2];

  MeasurementVectorType lowerBound(numberOfComponents);
  MeasurementVectorType upperBound(numberOfComponents);

  lowerBound.Fill(0);
  upperBound.Fill(1024);

  // Test exceptions

  // Call Initialize() before calling SetMeasurementVectorSize()
  EXPECT_THROW(histogram->Initialize(size), itk::ExceptionObject);

  histogram->SetMeasurementVectorSize(numberOfComponents);
  EXPECT_EQ(histogram->GetMeasurementVectorSize(), numberOfComponents);

  histogram->Initialize(size, lowerBound, upperBound);

  histogram->SetToZero();

  double interval = (upperBound[0] - lowerBound[0]) / static_cast<HistogramType::MeasurementType>(size[0]);

  MeasurementVectorType measurements(numberOfComponents, 512);

  IndexType index(numberOfComponents);
  IndexType ind(numberOfComponents);
  index.Fill(32);

  histogram->GetIndex(measurements, ind);
  EXPECT_EQ(ind, index);

  InstanceIdentifier id = histogram->GetInstanceIdentifier(index);
  EXPECT_EQ(histogram->GetIndex(id), index);

  // Test for outside
  index.Fill(-5);
  EXPECT_TRUE(histogram->IsIndexOutOfBounds(index));

  // Test for inside
  index.Fill(32);
  EXPECT_FALSE(histogram->IsIndexOutOfBounds(index));

  // Test for outside
  index.Fill(100);
  EXPECT_TRUE(histogram->IsIndexOutOfBounds(index));

  EXPECT_EQ(histogram->Size(), totalSize);
  EXPECT_EQ(histogram->GetSize(), size);

  // Query the bounds of the bin using the index of the bin.

  const MeasurementType & expectedValMeasType1 = lowerBound[0] + interval * 31;
  const MeasurementType & obtainedValMeasType1 = histogram->GetBinMin(0, 31);
  EXPECT_FLOAT_EQ(obtainedValMeasType1, expectedValMeasType1) << "Error in itk::Statistics::Histogram::GetBinMin";

  const MeasurementType & expectedValMeasType2 = lowerBound[0] + interval * 32;
  const MeasurementType & obtainedValMeasType2 = histogram->GetBinMax(0, 31);
  EXPECT_FLOAT_EQ(obtainedValMeasType2, expectedValMeasType2) << "Error in itk::Statistics::Histogram::GetBinMax";

  // Query the histogram bin extremes using a value within the bin

  const MeasurementType & expectedValMeasType3 = lowerBound[0] + interval * 31;
  const MeasurementType & obtainedValMeasType3 = histogram->GetBinMinFromValue(0, lowerBound[0] + interval * 31.5);
  EXPECT_FLOAT_EQ(obtainedValMeasType3, expectedValMeasType3)
    << "Error in itk::Statistics::Histogram::GetBinMinFromValue";

  const MeasurementType & expectedValMeasType4 = lowerBound[0];
  const MeasurementType & obtainedValMeasType4 = histogram->GetBinMinFromValue(0, itk::NumericTraits<float>::min());
  EXPECT_FLOAT_EQ(obtainedValMeasType4, expectedValMeasType4)
    << "Error in itk::Statistics::Histogram::GetBinMinFromValue";

  const MeasurementType & expectedValMeasType5 = lowerBound[0] + interval * (size[0] - 1);
  const MeasurementType & obtainedValMeasType5 = histogram->GetBinMinFromValue(0, itk::NumericTraits<float>::max());
  EXPECT_FLOAT_EQ(obtainedValMeasType5, expectedValMeasType5)
    << "Error in itk::Statistics::Histogram::GetBinMinFromValue";

  const MeasurementType & expectedValMeasType6 = lowerBound[0] + interval * 32;
  const MeasurementType & obtainedValMeasType6 = histogram->GetBinMaxFromValue(0, lowerBound[0] + interval * 31.5);
  EXPECT_FLOAT_EQ(obtainedValMeasType6, expectedValMeasType6)
    << "Error in itk::Statistics::Histogram::GetBinMaxFromValue";

  const MeasurementType & expectedValMeasType7 = lowerBound[0] + interval;
  const MeasurementType & obtainedValMeasType7 = histogram->GetBinMaxFromValue(0, itk::NumericTraits<float>::min());
  EXPECT_FLOAT_EQ(obtainedValMeasType7, expectedValMeasType7)
    << "Error in itk::Statistics::Histogram::GetBinMaxFromValue";

  const MeasurementType & expectedValMeasType8 = upperBound[0];
  const MeasurementType & obtainedValMeasType8 = histogram->GetBinMaxFromValue(0, itk::NumericTraits<float>::max());
  EXPECT_FLOAT_EQ(obtainedValMeasType8, expectedValMeasType8)
    << "Error in itk::Statistics::Histogram::GetBinMaxFromValue";

  index.Fill(31);
  const MeasurementType & expectedValMeasType9 = lowerBound[0] + interval * 31;
  const MeasurementType & obtainedValMeasType9 = histogram->GetHistogramMinFromIndex(index)[0];
  EXPECT_FLOAT_EQ(obtainedValMeasType9, expectedValMeasType9)
    << "Error in itk::Statistics::Histogram::GetHistogramMinFromIndex";

  const MeasurementType & expectedValMeasType10 = lowerBound[0] + interval * 32;
  const MeasurementType & obtainedValMeasType10 = histogram->GetHistogramMaxFromIndex(index)[0];
  EXPECT_FLOAT_EQ(obtainedValMeasType10, expectedValMeasType10)
    << "Error in itk::Statistics::Histogram::GetHistogramMaxFromIndex";

  for (id = 0; id < static_cast<InstanceIdentifier>(totalSize); ++id)
  {
    histogram->SetFrequency(id, 1);
    histogram->IncreaseFrequency(id, 1);

    EXPECT_EQ(histogram->GetFrequency(id), 2u);
  }

  // Quantile 1
  double expectedValD = 307.2;
  double obtainedValD = histogram->Quantile(0, 0.3);
  EXPECT_DOUBLE_EQ(obtainedValD, expectedValD) << "Error in itk::Statistics::Histogram::Quantile";

  // Quantile 2
  expectedValD = 512.0;
  obtainedValD = histogram->Quantile(0, 0.5);
  EXPECT_DOUBLE_EQ(obtainedValD, expectedValD) << "Error in itk::Statistics::Histogram::Quantile";

  // Quantile 3
  expectedValD = 716.8;
  obtainedValD = histogram->Quantile(0, 0.7);
  EXPECT_DOUBLE_EQ(obtainedValD, expectedValD) << "Error in itk::Statistics::Histogram::Quantile";


  // Histogram with SparseFrequencyContainer2
  using SparseHistogramType = itk::Statistics::Histogram<MeasurementType, itk::Statistics::SparseFrequencyContainer2>;
  auto sparseHistogram = SparseHistogramType::New();

  sparseHistogram->SetMeasurementVectorSize(numberOfComponents);

  // initializes a 64 x 64 x 64 histogram with equal size interval
  sparseHistogram->Initialize(size, lowerBound, upperBound);
  sparseHistogram->SetToZero();
  interval = (upperBound[0] - lowerBound[0]) / static_cast<SparseHistogramType::MeasurementType>(size[0]);

  measurements.Fill(512);
  index.Fill(32);
  sparseHistogram->GetIndex(measurements, ind);
  EXPECT_EQ(ind, index);

  id = sparseHistogram->GetInstanceIdentifier(index);
  EXPECT_EQ(sparseHistogram->GetIndex(id), index);

  index.Fill(100);
  EXPECT_TRUE(sparseHistogram->IsIndexOutOfBounds(index));
  EXPECT_EQ(sparseHistogram->Size(), totalSize);
  EXPECT_EQ(sparseHistogram->GetSize(), size);

  const MeasurementType & expectedValMeasType11 = lowerBound[0] + interval * 31;
  const MeasurementType & obtainedValMeasType11 = sparseHistogram->GetBinMin(0, 31);
  EXPECT_FLOAT_EQ(obtainedValMeasType11, expectedValMeasType11) << "Error in itk::Statistics::Histogram::GetBinMin";

  const MeasurementType & expectedValMeasType12 = lowerBound[0] + interval * 32;
  const MeasurementType & obtainedValMeasType12 = sparseHistogram->GetBinMax(0, 31);
  EXPECT_FLOAT_EQ(obtainedValMeasType12, expectedValMeasType12) << "Error in itk::Statistics::Histogram::GetBinMax";


  for (id = 0; id < static_cast<SparseHistogramType::InstanceIdentifier>(totalSize); ++id)
  {
    EXPECT_TRUE(sparseHistogram->SetFrequency(id, 1));
    EXPECT_TRUE(sparseHistogram->IncreaseFrequency(id, 1));
    EXPECT_EQ(sparseHistogram->GetFrequency(id), 2u);
  }

  expectedValD = 512.0;
  obtainedValD = sparseHistogram->Quantile(0, 0.5);
  EXPECT_DOUBLE_EQ(obtainedValD, expectedValD) << "Error in itk::Statistics::Histogram::Quantile";

  auto clipBinsAtEnds = true;
  ITK_GTEST_SET_GET_BOOLEAN(histogram, ClipBinsAtEnds, clipBinsAtEnds);

  clipBinsAtEnds = false;
  ITK_GTEST_SET_GET_BOOLEAN(histogram, ClipBinsAtEnds, clipBinsAtEnds);

  EXPECT_EQ(histogram->GetMeasurementVectorSize(), numberOfComponents);

  constexpr unsigned int measurementVectorSize{ 17 };
  EXPECT_THROW(histogram->SetMeasurementVectorSize(measurementVectorSize), itk::ExceptionObject);

  index.Fill(0);
  MeasurementVectorType measurement = histogram->GetMeasurementVector(index);
  for (unsigned int kid0 = 0; kid0 < numberOfComponents; ++kid0)
  {
    constexpr float expectedValF{ 8.0 };
    const float     obtainedValF = measurement[kid0];
    EXPECT_FLOAT_EQ(obtainedValF, expectedValF)
      << "Error in itk::Statistics::Histogram::GetMeasurementVector at index [" << index << "]";
  }

  histogram->SetClipBinsAtEnds(true);

  measurement = histogram->GetMeasurementVector(index);
  for (unsigned int kid1 = 0; kid1 < numberOfComponents; ++kid1)
  {
    constexpr float expectedValF{ 8.0 };
    const float     obtainedValF = measurement[kid1];
    EXPECT_FLOAT_EQ(obtainedValF, expectedValF)
      << "Error in itk::Statistics::Histogram::GetMeasurementVector at index [" << index << "]";
  }

  constexpr InstanceIdentifier instanceId{ 0 };
  measurement = histogram->GetMeasurementVector(instanceId);
  for (unsigned int kid2 = 0; kid2 < numberOfComponents; ++kid2)
  {
    constexpr float expectedValF{ 8.0 };
    const float     obtainedValF = measurement[kid2];
    EXPECT_FLOAT_EQ(obtainedValF, expectedValF)
      << "Error in itk::Statistics::Histogram::GetMeasurementVector at index [" << index << "]";
  }

  // Test GetIndex with different settings of SetClipBinsAtEnds
  MeasurementVectorType outOfLowerRange(numberOfComponents);
  MeasurementVectorType outOfUpperRange(numberOfComponents);

  for (unsigned int k = 0; k < numberOfComponents; ++k)
  {
    outOfLowerRange[k] = lowerBound[k] - 13;
    outOfUpperRange[k] = upperBound[k] + 23;
  }

  histogram->SetClipBinsAtEnds(false);

  IndexType index1(numberOfComponents);
  bool      getindex1 = histogram->GetIndex(outOfLowerRange, index1);

  std::cout << "GetIndex() with SetClipBinsAtEnds() = false " << std::endl;
  std::cout << "Boolean " << getindex1 << " Index " << index1 << std::endl;

  EXPECT_TRUE(getindex1);

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(index1[k1], 0);
  }


  histogram->SetClipBinsAtEnds(true);

  getindex1 = histogram->GetIndex(outOfLowerRange, index1);

  std::cout << "GetIndex() with SetClipBinsAtEnds() = true " << std::endl;
  std::cout << "Boolean " << getindex1 << " Index " << index1 << std::endl;

  EXPECT_FALSE(getindex1);

  histogram->SetClipBinsAtEnds(false);

  IndexType index2(numberOfComponents);
  bool      getindex2 = histogram->GetIndex(outOfUpperRange, index2);

  std::cout << "GetIndex() with SetClipBinsAtEnds() = false " << std::endl;
  std::cout << "Boolean " << getindex2 << " Index " << index2 << std::endl;

  EXPECT_TRUE(getindex2);

  for (unsigned int k2 = 0; k2 < numberOfComponents; ++k2)
  {
    EXPECT_EQ(index2[k2], static_cast<long>(size[k2]) - 1);
  }


  histogram->SetClipBinsAtEnds(true);

  getindex2 = histogram->GetIndex(outOfUpperRange, index2);

  std::cout << "GetIndex() with SetClipBinsAtEnds() = true " << std::endl;
  std::cout << "Boolean " << getindex2 << " Index " << index2 << std::endl;

  EXPECT_FALSE(getindex2);

  // Test GetIndex() for values that are above the median value of the bin.
  IndexType             pindex(numberOfComponents, 32);
  MeasurementVectorType measurementVector = histogram->GetMeasurementVector(pindex);

  for (unsigned int gik1 = 0; gik1 < numberOfComponents; ++gik1)
  {
    measurementVector[gik1] += 0.3;
  }

  IndexType gindex;
  histogram->GetIndex(measurementVector, gindex);

  for (unsigned int gik2 = 0; gik2 < numberOfComponents; ++gik2)
  {
    EXPECT_EQ(gindex[gik2], 32);
  }

  // Test GetIndex() for values that are below the median value of the bin.
  for (unsigned int gik3 = 0; gik3 < numberOfComponents; ++gik3)
  {
    measurementVector[gik3] -= 0.6;
  }

  histogram->GetIndex(measurementVector, gindex);

  for (unsigned int gik4 = 0; gik4 < numberOfComponents; ++gik4)
  {
    EXPECT_EQ(gindex[gik4], 32);
  }

  // Test GetIndex on the upper and lower bounds
  IndexType upperIndex(numberOfComponents);
  EXPECT_TRUE(histogram->GetIndex(upperBound, upperIndex));

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(upperIndex[k1], 63);
  }

  IndexType lowerIndex(numberOfComponents);
  EXPECT_TRUE(histogram->GetIndex(lowerBound, lowerIndex));

  for (unsigned int k1 = 0; k1 < numberOfComponents; ++k1)
  {
    EXPECT_EQ(lowerIndex[k1], 0);
  }

  // Test GetIndex above the upper bound of a bin
  histogram->SetClipBinsAtEnds(false);
  MeasurementVectorType measurementVectorAbove(numberOfComponents);
  for (unsigned int gupk1 = 0; gupk1 < numberOfComponents; ++gupk1)
  {
    measurementVectorAbove[gupk1] = 129.9;
  }

  IndexType aboveUpperIndex(numberOfComponents);
  EXPECT_TRUE(histogram->GetIndex(measurementVectorAbove, aboveUpperIndex));

  // Get the mean value for a dimension
  constexpr unsigned int dimension{ 0 };
  const double           mean = histogram->Mean(dimension);
  std::cout << "Mean value along dimension " << dimension << " : " << mean << std::endl;

  HistogramType::Iterator itr = histogram->Begin();
  HistogramType::Iterator end = histogram->End();

  const HistogramType::TotalAbsoluteFrequencyType totalFrequency = histogram->GetTotalFrequency();

  const InstanceIdentifier histogramSize = histogram->Size();

  while (itr != end)
  {
    itr.SetFrequency(itr.GetFrequency() + 1);
    ++itr;
  }

  const HistogramType::TotalAbsoluteFrequencyType newTotalFrequency = histogram->GetTotalFrequency();
  EXPECT_EQ(newTotalFrequency, histogramSize + totalFrequency);

  // Exercise GetIndex() method in the iterator.
  std::cout << "TEST GetIndex() and GetFrequency() in the iterator" << std::endl;
  itr = histogram->Begin();
  end = histogram->End();

  // Print out only some of them, the first 10...
  for (unsigned int kk = 0; kk < 10 && itr != end; ++itr, ++kk)
  {
    std::cout << itr.GetIndex() << " : " << itr.GetFrequency() << std::endl;
  }


  // Exercise GetMin / GetMax methods
  {
    constexpr double        epsilon{ 1e-6 };
    HistogramType::SizeType size2 = histogram->GetSize();

    HistogramType::BinMinContainerType binMinimums = histogram->GetMins();

    for (unsigned int dim = 0; dim < numberOfComponents; ++dim)
    {
      HistogramType::BinMinVectorType binDimensionMinimums = histogram->GetDimensionMins(dim);
      for (unsigned int k = 0; k < size2[dim]; ++k)
      {
        const HistogramType::MeasurementType minA = binMinimums[dim][k];
        const HistogramType::MeasurementType minB = binDimensionMinimums[k];
        EXPECT_NEAR(minA, minB, epsilon) << "Error in itk:Statistics::Histogram::GetMins/GetDimensionMins at index ["
                                         << k << "]";

        const HistogramType::MeasurementType minC = histogram->GetBinMin(dim, k);
        EXPECT_NEAR(minA, minC, epsilon) << "Error in itk:Statistics::Histogram::GetMins/GetBinMin at index [" << k
                                         << "]";
      }
    }

    HistogramType::BinMaxContainerType binMaximums = histogram->GetMaxs();

    for (unsigned int dim = 0; dim < numberOfComponents; ++dim)
    {
      HistogramType::BinMaxVectorType binDimensionMaximums = histogram->GetDimensionMaxs(dim);
      for (unsigned int k = 0; k < size2[dim]; ++k)
      {
        const HistogramType::MeasurementType maxA = binMaximums[dim][k];
        const HistogramType::MeasurementType maxB = binDimensionMaximums[k];
        EXPECT_NEAR(maxA, maxB, epsilon) << "Error in itk:Statistics::Histogram::GetMaxs/GetDimensionMaxs at index ["
                                         << k << "]";

        const HistogramType::MeasurementType maxC = histogram->GetBinMax(dim, k);
        EXPECT_NEAR(maxA, maxC, epsilon) << "Error in itk:Statistics::Histogram::GetMaxs/GetBinMax at index [" << k
                                         << "]";
      }
    }
  }


  // Test methods specific to Iterators
  {
    using IteratorType = HistogramType::Iterator;
    const IteratorType iter = histogram->Begin();
    IteratorType       iter2 = histogram->End();

    iter2 = iter;
    EXPECT_EQ(iter, iter2);

    IteratorType iter3(histogram);
    EXPECT_EQ(histogram->Begin(), iter3);

    unsigned int counter = 0;
    while (iter3 != histogram->End())
    {
      ++iter3;
      counter++;
    }

    EXPECT_EQ(counter, histogram->Size());

    const IteratorType iter4(iter2);
    EXPECT_EQ(iter4, iter2);

    const IteratorType iter5 = iter2;
    EXPECT_EQ(iter5, iter2);

    constexpr itk::Statistics::Sample<HistogramType::MeasurementVectorType>::InstanceIdentifier id2 = 7;
    const IteratorType                                                                          iter6(id2, histogram);
    EXPECT_EQ(iter6.GetInstanceIdentifier(), id2);
  }

  // Test methods specific to ConstIterators
  {
    using ConstIteratorType = HistogramType::ConstIterator;
    const ConstIteratorType iter = histogram->Begin();
    ConstIteratorType       iter2 = histogram->End();

    iter2 = iter;
    EXPECT_FALSE(iter != iter2);
    EXPECT_EQ(iter, iter2);

    const ConstIteratorType iter3(iter2);
    EXPECT_EQ(iter3, iter2);

    const HistogramType * constHistogram = histogram.GetPointer();

    const ConstIteratorType iter4(constHistogram->Begin());
    const ConstIteratorType iter5(histogram->Begin());
    EXPECT_EQ(iter5, iter4);

    const ConstIteratorType iter6(constHistogram);
    const ConstIteratorType iter7(histogram);
    EXPECT_EQ(iter6, iter7);

    const ConstIteratorType                                                                     iter8(histogram);
    constexpr itk::Statistics::Sample<HistogramType::MeasurementVectorType>::InstanceIdentifier id3 = 0;
    EXPECT_EQ(iter8.GetInstanceIdentifier(), id3);

    unsigned int      counter = 0;
    ConstIteratorType iter10(constHistogram);
    EXPECT_EQ(constHistogram->Begin(), iter10);

    while (iter10 != constHistogram->End())
    {
      ++iter10;
      counter++;
    }

    EXPECT_EQ(counter, constHistogram->Size());
  }

  // Test streaming enumeration for HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature elements
  const std::set<itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature> allRunLengthFeature{
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::ShortRunEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::LongRunEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::GreyLevelNonuniformity,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::RunLengthNonuniformity,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::LowGreyLevelRunEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::HighGreyLevelRunEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::ShortRunLowGreyLevelEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::ShortRunHighGreyLevelEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::LongRunLowGreyLevelEmphasis,
    itk::Statistics::HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature::LongRunHighGreyLevelEmphasis
  };
  for (const auto & ee : allRunLengthFeature)
  {
    std::cout << "STREAMED ENUM VALUE HistogramToRunLengthFeaturesFilterEnums::RunLengthFeature: " << ee << std::endl;
  }
}
