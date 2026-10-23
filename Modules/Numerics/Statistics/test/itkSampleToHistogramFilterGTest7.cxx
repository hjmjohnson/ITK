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

TEST(SampleToHistogramFilter, ConvertedLegacyTest7)
{

  constexpr unsigned int numberOfComponents{ 3 };
  using MeasurementType = int; // Exercise an integer type for the samples

  using MeasurementVectorType = itk::VariableLengthVector<float>;

  using SampleType = itk::Statistics::ListSample<MeasurementVectorType>;

  using HistogramType = itk::Statistics::Histogram<MeasurementType, itk::Statistics::DenseFrequencyContainer2>;

  using FilterType = itk::Statistics::SampleToHistogramFilter<SampleType, HistogramType>;

  using HistogramSizeType = FilterType::HistogramSizeType;
  using HistogramMeasurementVectorType = FilterType::HistogramMeasurementVectorType;

  auto filter = FilterType::New();
  auto sample = SampleType::New();


  HistogramMeasurementVectorType minimum(numberOfComponents);
  HistogramMeasurementVectorType maximum(numberOfComponents);

  minimum[0] = -17;
  minimum[1] = -19;
  minimum[2] = -24;

  maximum[0] = 17;
  maximum[1] = 19;
  maximum[2] = 24;

  HistogramSizeType histogramSize(numberOfComponents);

  histogramSize[0] = 36;
  histogramSize[1] = 40;
  histogramSize[2] = 50;

  MeasurementVectorType measure(numberOfComponents);

  sample->SetMeasurementVectorSize(numberOfComponents);

  // Populate the Sample
  for (unsigned int i = 0; i < histogramSize[0]; ++i)
  {
    measure[0] = minimum[0] + static_cast<double>(i);
    for (unsigned int j = 0; j < histogramSize[1]; ++j)
    {
      measure[1] = minimum[1] + static_cast<double>(j);
      for (unsigned int k = 0; k < histogramSize[2]; ++k)
      {
        measure[2] = minimum[2] + static_cast<double>(k);
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


  HistogramType::ConstIterator       histogramItr = histogram->Begin();
  const HistogramType::ConstIterator histogramEnd = histogram->End();

  constexpr unsigned int expectedFrequency1{ 1 };
  while (histogramItr != histogramEnd)
  {
    EXPECT_EQ(histogramItr.GetFrequency(), expectedFrequency1)
      << "Histogram bin error for measure " << histogramItr.GetMeasurementVector();
    ++histogramItr;
  }

  // Exercise the saturation of the maximum
  maximum[0] = itk::NumericTraits<MeasurementType>::max();
  maximum[1] = itk::NumericTraits<MeasurementType>::max();
  maximum[2] = itk::NumericTraits<MeasurementType>::max();

  minimum[0] = itk::NumericTraits<MeasurementType>::min();
  minimum[1] = itk::NumericTraits<MeasurementType>::min();
  minimum[2] = itk::NumericTraits<MeasurementType>::min();

  filter->SetHistogramBinMaximum(maximum);
  filter->SetHistogramBinMinimum(minimum);
  filter->SetAutoMinimumMaximum(true);

  EXPECT_NO_THROW(filter->Update());


  filter->SetAutoMinimumMaximum(false);

  // Add a sample that will exercise the overflow code
  //
  measure[0] = static_cast<float>(itk::NumericTraits<MeasurementType>::max());
  measure[1] = static_cast<float>(itk::NumericTraits<MeasurementType>::max());
  measure[2] = static_cast<float>(itk::NumericTraits<MeasurementType>::max());

  sample->PushBack(measure);
  sample->Modified();

  EXPECT_NO_THROW(filter->Update());


  filter->SetAutoMinimumMaximum(true);


  EXPECT_NO_THROW(filter->Update());
}
