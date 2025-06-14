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
#ifndef itkLabelStatisticsImageFilter_hxx
#define itkLabelStatisticsImageFilter_hxx

#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkImageScanlineConstIterator.h"
#include "itkTotalProgressReporter.h"
#include <algorithm> // For min and max.

namespace itk
{
template <typename TInputImage, typename TLabelImage>
LabelStatisticsImageFilter<TInputImage, TLabelImage>::LabelStatisticsImageFilter()
  : m_LowerBound(static_cast<RealType>(NumericTraits<PixelType>::NonpositiveMin()))
  , m_UpperBound(static_cast<RealType>(NumericTraits<PixelType>::max()))
{
  Self::AddRequiredInputName("LabelInput");
  m_NumBins.SetSize(1);
  m_NumBins[0] = 256;
  m_ValidLabelValues.clear();
}

template <typename TInputImage, typename TLabelImage>
void
LabelStatisticsImageFilter<TInputImage, TLabelImage>::SetHistogramParameters(const int numBins,
                                                                             RealType  lowerBound,
                                                                             RealType  upperBound)
{
  m_NumBins[0] = numBins;
  m_LowerBound = lowerBound;
  m_UpperBound = upperBound;
  m_UseHistograms = true;
}


template <typename TInputImage, typename TLabelImage>
void
LabelStatisticsImageFilter<TInputImage, TLabelImage>::MergeMap(MapType & m1, MapType & m2) const
{

  for (auto & m2_value : m2)
  {
    // does this label exist in the cumulative structure yet?
    auto m1It = m1.find(m2_value.first);
    if (m1It == m1.end())
    {
      // move m2 entry into m1, this reuses the histogram if needed.
      m1.emplace(m2_value.first, std::move(m2_value.second));
    }
    else
    {


      typename MapType::mapped_type & labelStats = m1It->second;

      // accumulate the information from this thread
      labelStats.m_Count += m2_value.second.m_Count;
      labelStats.m_Sum += m2_value.second.m_Sum;
      labelStats.m_SumOfSquares += m2_value.second.m_SumOfSquares;

      if (labelStats.m_Minimum > m2_value.second.m_Minimum)
      {
        labelStats.m_Minimum = m2_value.second.m_Minimum;
      }
      if (labelStats.m_Maximum < m2_value.second.m_Maximum)
      {
        labelStats.m_Maximum = m2_value.second.m_Maximum;
      }

      // bounding box is min,max pairs
      for (unsigned int ii = 0; ii < (ImageDimension * 2); ii += 2)
      {
        labelStats.m_BoundingBox[ii] = std::min(labelStats.m_BoundingBox[ii], m2_value.second.m_BoundingBox[ii]);
        labelStats.m_BoundingBox[ii + 1] =
          std::max(labelStats.m_BoundingBox[ii + 1], m2_value.second.m_BoundingBox[ii + 1]);
      }

      // if enabled, update the histogram for this label
      if (m_UseHistograms)
      {
        typename HistogramType::IndexType index;
        index.SetSize(1);
        for (unsigned int bin = 0; bin < m_NumBins[0]; ++bin)
        {
          index[0] = bin;
          labelStats.m_Histogram->IncreaseFrequency(bin, m2_value.second.m_Histogram->GetFrequency(bin));
        }
      }
    }
  }
}

template <typename TInputImage, typename TLabelImage>
void
LabelStatisticsImageFilter<TInputImage, TLabelImage>::AfterStreamedGenerateData()
{
  Superclass::AfterStreamedGenerateData();

  // compute the remainder of the statistics
  for (auto & mapValue : m_LabelStatistics)
  {
    typename MapType::mapped_type & labelStats = mapValue.second;

    labelStats.m_Mean = labelStats.m_Sum / static_cast<RealType>(labelStats.m_Count);

    // variance
    if (labelStats.m_Count > 1)
    {
      // unbiased estimate of variance
      LabelStatistics & ls = mapValue.second;
      const RealType    sumSquared = ls.m_Sum * ls.m_Sum;
      const auto        count = static_cast<RealType>(ls.m_Count);

      ls.m_Variance = (ls.m_SumOfSquares - sumSquared / count) / (count - 1.0);
    }
    else
    {
      labelStats.m_Variance = RealType{};
    }

    // sigma
    labelStats.m_Sigma = 0.0;
    if (labelStats.m_Variance >= 0.0)
    {
      labelStats.m_Sigma = std::sqrt(labelStats.m_Variance);
    }
  }

  {
    // Now update the cached vector of valid labels.
    m_ValidLabelValues.resize(0);
    m_ValidLabelValues.reserve(m_LabelStatistics.size());
    for (auto & mapValue : m_LabelStatistics)
    {
      m_ValidLabelValues.push_back(mapValue.first);
    }
  }
}

template <typename TInputImage, typename TLabelImage>
void
LabelStatisticsImageFilter<TInputImage, TLabelImage>::ThreadedStreamedGenerateData(
  const RegionType & outputRegionForThread)
{

  MapType localStatistics;

  typename HistogramType::IndexType             histogramIndex(1);
  typename HistogramType::MeasurementVectorType histogramMeasurement(1);

  const SizeValueType size0 = outputRegionForThread.GetSize(0);
  if (size0 == 0)
  {
    return;
  }

  ImageLinearConstIteratorWithIndex<TInputImage> it(this->GetInput(), outputRegionForThread);

  ImageScanlineConstIterator labelIt(this->GetLabelInput(), outputRegionForThread);

  auto mapIt = localStatistics.end();

  // do the work
  while (!it.IsAtEnd())
  {
    while (!it.IsAtEndOfLine())
    {
      const RealType & value = static_cast<RealType>(it.Get());

      const LabelPixelType & label = labelIt.Get();

      // is the label already in this thread?
      mapIt = localStatistics.find(label);
      if (mapIt == localStatistics.end())
      {
        // create a new statistics object
        if (m_UseHistograms)
        {
          mapIt = localStatistics.emplace(label, LabelStatistics(m_NumBins[0], m_LowerBound, m_UpperBound)).first;
        }
        else
        {
          mapIt = localStatistics.emplace(label, LabelStatistics()).first;
        }
      }

      typename MapType::mapped_type & labelStats = mapIt->second;

      // update the values for this label and this thread
      if (value < labelStats.m_Minimum)
      {
        labelStats.m_Minimum = value;
      }
      if (value > labelStats.m_Maximum)
      {
        labelStats.m_Maximum = value;
      }

      // bounding box is min,max pairs
      for (unsigned int i = 0; i < (2 * TInputImage::ImageDimension); i += 2)
      {
        const IndexType & index = it.GetIndex();
        labelStats.m_BoundingBox[i] = std::min(labelStats.m_BoundingBox[i], index[i / 2]);
        labelStats.m_BoundingBox[i + 1] = std::max(labelStats.m_BoundingBox[i + 1], index[i / 2]);
      }

      labelStats.m_Sum += value;
      labelStats.m_SumOfSquares += (value * value);
      labelStats.m_Count++;

      // if enabled, update the histogram for this label
      if (m_UseHistograms)
      {
        histogramMeasurement[0] = value;
        labelStats.m_Histogram->GetIndex(histogramMeasurement, histogramIndex);
        labelStats.m_Histogram->IncreaseFrequencyOfIndex(histogramIndex, 1);
      }


      ++labelIt;
      ++it;
    }
    labelIt.NextLine();
    it.NextLine();
  }


  // Merge localStatistics and m_LabelStatistics concurrently safe in a
  // local copy, this thread may do multiple merges.
  while (true)
  {
    MapType tomerge{};
    {
      const std::lock_guard<std::mutex> lockGuard(m_Mutex);

      if (m_LabelStatistics.empty())
      {
        swap(m_LabelStatistics, localStatistics);
        break;
      }

      // Move the data of the output map to the local `tomerge` and clear the output map.
      swap(m_LabelStatistics, tomerge);

    } // release lock, allow other threads to merge data

    // Merge tomerge into localStatistics, locally
    MergeMap(localStatistics, tomerge);
  }
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetMinimum(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return NumericTraits<PixelType>::max();
  }

  return mapIt->second.m_Minimum;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetMaximum(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return NumericTraits<PixelType>::NonpositiveMin();
  }

  return mapIt->second.m_Maximum;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetMean(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return PixelType{};
  }

  return mapIt->second.m_Mean;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetSum(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return PixelType{};
  }

  return mapIt->second.m_Sum;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetSigma(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return PixelType{};
  }

  return mapIt->second.m_Sigma;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetVariance(LabelPixelType label) const -> RealType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return PixelType{};
  }

  return mapIt->second.m_Variance;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetBoundingBox(LabelPixelType label) const -> BoundingBoxType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    BoundingBoxType emptyBox;
    // label does not exist, return a default value
    return emptyBox;
  }

  return mapIt->second.m_BoundingBox;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetRegion(LabelPixelType label) const -> RegionType
{
  const auto mapIt = m_LabelStatistics.find(label);

  if (mapIt == m_LabelStatistics.end())
  {
    const RegionType emptyRegion;
    // label does not exist, return a default value
    return emptyRegion;
  }

  BoundingBoxType bbox = this->GetBoundingBox(label);
  IndexType       index;
  SizeType        size;

  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    index[i] = bbox[2 * i];
    size[i] = bbox[2 * i + 1] - bbox[2 * i] + 1;
  }
  const RegionType region(index, size);

  return region;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetCount(LabelPixelType label) const -> MapSizeType
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return 0;
  }

  return mapIt->second.m_Count;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetMedian(LabelPixelType label) const -> RealType
{
  RealType   median = 0.0;
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end() || !m_UseHistograms)
  {
    // label does not exist OR histograms not enabled, return the default value
    return median;
  }

  typename HistogramType::SizeValueType bin = 0;

  typename HistogramType::IndexType index;
  index.SetSize(1);
  RealType total = 0;

  // count bins until just over half the distribution is counted
  while (total <= (mapIt->second.m_Count / 2) && (bin < m_NumBins[0]))
  {
    index[0] = bin;
    total += mapIt->second.m_Histogram->GetFrequency(index);
    ++bin;
  }
  --bin;
  index[0] = bin;

  // return center of bin range
  const RealType lowRange = mapIt->second.m_Histogram->GetBinMin(0, bin);
  const RealType highRange = mapIt->second.m_Histogram->GetBinMax(0, bin);
  median = lowRange + (highRange - lowRange) / 2;
  return median;
}

template <typename TInputImage, typename TLabelImage>
auto
LabelStatisticsImageFilter<TInputImage, TLabelImage>::GetHistogram(LabelPixelType label) const -> HistogramPointer
{
  const auto mapIt = m_LabelStatistics.find(label);
  if (mapIt == m_LabelStatistics.end())
  {
    // label does not exist, return a default value
    return nullptr;
  }

  // this will be zero if histograms have not been enabled
  return mapIt->second.m_Histogram;
}

template <typename TImage, typename TLabelImage>
void
LabelStatisticsImageFilter<TImage, TLabelImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  using namespace print_helper;

  Superclass::PrintSelf(os, indent);

  os << indent << "LabelStatistics: " << std::endl;
  for (const auto & pair : m_LabelStatistics)
  {
    os << indent.GetNextIndent() << "{" << pair.first << ": " << pair.second << "}" << std::endl;
  }

  os << indent << "ValidLabelValues: " << m_ValidLabelValues << std::endl;
  itkPrintSelfBooleanMacro(UseHistograms);
  os << indent << "NumBins: " << m_NumBins << std::endl;
  os << indent << "LowerBound: " << static_cast<typename NumericTraits<RealType>::PrintType>(m_LowerBound) << std::endl;
  os << indent << "UpperBound: " << static_cast<typename NumericTraits<RealType>::PrintType>(m_UpperBound) << std::endl;
}
} // end namespace itk
#endif
