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

#include "itkListSample.h"
#include "itkHistogram.h"
#include "itkSampleToHistogramFilter.h"
#include "itkGTest.h"

TEST(SampleToHistogramFilter, ConvertedLegacyTest2)
{

  constexpr unsigned int numberOfComponents{ 3 };
  using MeasurementType = float;

  using MeasurementVectorType = itk::Array<MeasurementType>;
  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using HistogramType = itk::Statistics::Histogram<MeasurementType, itk::Statistics::DenseFrequencyContainer2>;

  using FilterType = itk::Statistics::SampleToHistogramFilter<SampleType, HistogramType>;

  using HistogramSizeType = FilterType::HistogramSizeType;
  using HistogramMeasurementVectorType = FilterType::HistogramMeasurementVectorType;

  auto filter = FilterType::New();
  auto sample = SampleType::New();

  HistogramMeasurementVectorType minimum(numberOfComponents);
  HistogramMeasurementVectorType maximum(numberOfComponents);

  minimum[0] = -17.5;
  minimum[1] = -19.5;
  minimum[2] = -24.5;

  maximum[0] = 17.5;
  maximum[1] = 19.5;
  maximum[2] = 24.5;

  HistogramSizeType histogramSize(numberOfComponents);

  histogramSize[0] = 35;
  histogramSize[1] = 39;
  histogramSize[2] = 49;

  MeasurementVectorType measure(numberOfComponents);

  sample->SetMeasurementVectorSize(numberOfComponents);

  // Populate the Sample
  for (unsigned int i = 0; i < histogramSize[0]; ++i)
  {
    measure[0] = minimum[0] + 0.5 + i;
    for (unsigned int j = 0; j < histogramSize[1]; ++j)
    {
      measure[1] = minimum[1] + 0.5 + j;
      for (unsigned int k = 0; k < histogramSize[2]; ++k)
      {
        measure[2] = minimum[2] + 0.5 + k;
        sample->PushBack(measure);
      }
    }
  }


  filter->SetInput(sample);


  // Test exception when calling Update() without having
  // defined the size of the histogram in the filter.
  EXPECT_THROW(filter->Update(), itk::ExceptionObject)
    << "Failure to throw expected exception due to lack" << " of calling SetHistogramSize() in the filter ";


  const HistogramType * histogram = filter->GetOutput();

  EXPECT_EQ(histogram->Size(), 0u) << "Histogram Size should have been zero";


  filter->SetHistogramSize(histogramSize);

  EXPECT_NO_THROW(filter->Update());

  const unsigned int expectedHistogramSize1 = histogramSize[0] * histogramSize[1] * histogramSize[2];

  EXPECT_EQ(histogram->Size(), expectedHistogramSize1) << "Histogram Size error";


  HistogramType::ConstIterator histogramItr = histogram->Begin();
  HistogramType::ConstIterator histogramEnd = histogram->End();

  constexpr unsigned int expectedFrequency1{ 1 };
  while (histogramItr != histogramEnd)
  {
    EXPECT_EQ(histogramItr.GetFrequency(), expectedFrequency1)
      << "Histogram bin error for measure " << histogramItr.GetMeasurementVector();
    ++histogramItr;
  }


  // Now resize the histogram, to see is the frequencies
  // are relocated correctly into the new size bins.
  //
  histogramSize[0] = 7;
  histogramSize[1] = 39;
  histogramSize[2] = 49;

  filter->SetHistogramSize(histogramSize);

  EXPECT_NO_THROW(filter->Update());

  const unsigned int expectedHistogramSize2 = histogramSize[0] * histogramSize[1] * histogramSize[2];

  EXPECT_EQ(histogram->Size(), expectedHistogramSize2) << "Histogram Size error";


  histogramItr = histogram->Begin();
  histogramEnd = histogram->End();

  constexpr unsigned int expectedFrequency2{ 5 };
  while (histogramItr != histogramEnd)
  {
    EXPECT_EQ(histogramItr.GetFrequency(), expectedFrequency2)
      << "Histogram bin error for measure " << histogramItr.GetMeasurementVector();
    ++histogramItr;
  }


  // Now resize the histogram, to see is the frequencies
  // are relocated correctly into the new size bins.
  //
  histogramSize[0] = 7;
  histogramSize[1] = 13;
  histogramSize[2] = 49;

  filter->SetHistogramSize(histogramSize);

  EXPECT_NO_THROW(filter->Update());

  const unsigned int expectedHistogramSize3 = histogramSize[0] * histogramSize[1] * histogramSize[2];

  EXPECT_EQ(histogram->Size(), expectedHistogramSize3) << "Histogram Size error";


  histogramItr = histogram->Begin();
  histogramEnd = histogram->End();

  constexpr unsigned int expectedFrequency3{ 15 };
  while (histogramItr != histogramEnd)
  {
    EXPECT_EQ(histogramItr.GetFrequency(), expectedFrequency3)
      << "Histogram bin error for measure " << histogramItr.GetMeasurementVector();
    ++histogramItr;
  }


  // Now resize the histogram, to see is the frequencies
  // are relocated correctly into the new size bins.
  //
  histogramSize[0] = 7;
  histogramSize[1] = 13;
  histogramSize[2] = 7;

  filter->SetHistogramSize(histogramSize);

  EXPECT_NO_THROW(filter->Update());

  const unsigned int expectedHistogramSize4 = histogramSize[0] * histogramSize[1] * histogramSize[2];

  EXPECT_EQ(histogram->Size(), expectedHistogramSize4) << "Histogram Size error";


  histogramItr = histogram->Begin();
  histogramEnd = histogram->End();

  constexpr unsigned int expectedFrequency4{ 105 };
  while (histogramItr != histogramEnd)
  {
    EXPECT_EQ(histogramItr.GetFrequency(), expectedFrequency4)
      << "Histogram bin error for measure " << histogramItr.GetMeasurementVector();
    ++histogramItr;
  }
}
