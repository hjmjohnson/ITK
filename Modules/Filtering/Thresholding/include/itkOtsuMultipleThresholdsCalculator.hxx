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
#ifndef itkOtsuMultipleThresholdsCalculator_hxx
#define itkOtsuMultipleThresholdsCalculator_hxx

#include "itkMath.h"

namespace itk
{
template <typename TInputHistogram>
OtsuMultipleThresholdsCalculator<TInputHistogram>::OtsuMultipleThresholdsCalculator()

{
  m_Output.resize(m_NumberOfThresholds);
  std::fill(m_Output.begin(), m_Output.end(), MeasurementType{});
}

template <typename TInputHistogram>
auto
OtsuMultipleThresholdsCalculator<TInputHistogram>::GetOutput() -> const OutputType &
{
  return m_Output;
}

template <typename TInputHistogram>
bool
OtsuMultipleThresholdsCalculator<TInputHistogram>::IncrementThresholds(InstanceIdentifierVectorType & thresholdIndexes,
                                                                       MeanType                       globalMean,
                                                                       MeanVectorType &               classMean,
                                                                       FrequencyVectorType &          classFrequency)
{
  const typename TInputHistogram::ConstPointer histogram = this->GetInputHistogram();

  const SizeValueType numberOfHistogramBins = histogram->Size();
  const auto          numberOfClasses = static_cast<const SizeValueType>(classMean.size());

  // From the upper threshold down
  for (int j = static_cast<int>(m_NumberOfThresholds - 1); j >= 0; j--)
  {
    // If this threshold can be incremented (i.e. we're not at the end of the
    // histogram)
    if (thresholdIndexes[j] < numberOfHistogramBins - 2 - (m_NumberOfThresholds - 1 - j))
    {
      // Increment it and update mean and frequency of the class bounded by the
      // threshold
      ++thresholdIndexes[j];

      const MeanType      meanOld = classMean[j];
      const FrequencyType freqOld = classFrequency[j];

      classFrequency[j] += histogram->GetFrequency(thresholdIndexes[j]);

      if (NumericTraits<FrequencyType>::IsPositive(classFrequency[j]))
      {
        classMean[j] = (meanOld * static_cast<MeanType>(freqOld) +
                        static_cast<MeanType>(histogram->GetMeasurementVector(thresholdIndexes[j])[0]) *
                          static_cast<MeanType>(histogram->GetFrequency(thresholdIndexes[j]))) /
                       static_cast<MeanType>(classFrequency[j]);
      }
      else
      {
        classMean[j] = MeanType{};
      }

      // Set higher thresholds adjacent to their previous ones, and update mean
      // and frequency of the respective classes
      for (unsigned int k = j + 1; k < m_NumberOfThresholds; ++k)
      {
        thresholdIndexes[k] = thresholdIndexes[k - 1] + 1;
        classFrequency[k] = histogram->GetFrequency(thresholdIndexes[k]);
        if (NumericTraits<FrequencyType>::IsPositive(classFrequency[k]))
        {
          classMean[k] = static_cast<MeanType>(histogram->GetMeasurementVector(thresholdIndexes[k])[0]);
        }
        else
        {
          classMean[k] = MeanType{};
        }
      }

      // Update mean and frequency of the highest class
      classFrequency[numberOfClasses - 1] = histogram->GetTotalFrequency();
      classMean[numberOfClasses - 1] = globalMean * histogram->GetTotalFrequency();

      for (unsigned int k = 0; k < numberOfClasses - 1; ++k)
      {
        classFrequency[numberOfClasses - 1] -= classFrequency[k];
        classMean[numberOfClasses - 1] -= classMean[k] * static_cast<MeanType>(classFrequency[k]);
      }

      if (NumericTraits<FrequencyType>::IsPositive(classFrequency[numberOfClasses - 1]))
      {
        classMean[numberOfClasses - 1] /= static_cast<MeanType>(classFrequency[numberOfClasses - 1]);
      }
      else
      {
        classMean[numberOfClasses - 1] = MeanType{};
      }

      // Exit the for loop if a threshold has been incremented
      break;
    }
    // If this threshold can't be incremented
    // If it's the lowest threshold
    if (j == 0)
    {
      // We couldn't increment because we're done
      return false;
    }
  }
  // We incremented
  return true;
}

template <typename TInputHistogram>
void
OtsuMultipleThresholdsCalculator<TInputHistogram>::Compute()
{
  const typename TInputHistogram::ConstPointer histogram = this->GetInputHistogram();

  // TODO: as an improvement, the class could accept multi-dimensional
  // histograms
  // and the user could specify the dimension to apply the algorithm to.
  if (histogram->GetSize().Size() != 1)
  {
    itkExceptionMacro("Histogram must be 1-dimensional.");
  }

  // Compute global mean
  typename TInputHistogram::ConstIterator       iter = histogram->Begin();
  const typename TInputHistogram::ConstIterator end = histogram->End();

  MeanType            globalMean{};
  const FrequencyType globalFrequency = histogram->GetTotalFrequency();
  while (iter != end)
  {
    globalMean += static_cast<MeanType>(iter.GetMeasurementVector()[0]) * static_cast<MeanType>(iter.GetFrequency());
    ++iter;
  }
  globalMean /= static_cast<MeanType>(globalFrequency);

  const SizeValueType numberOfClasses = m_NumberOfThresholds + 1;

  // Initialize thresholds
  InstanceIdentifierVectorType thresholdIndexes(m_NumberOfThresholds);
  for (SizeValueType j = 0; j < m_NumberOfThresholds; ++j)
  {
    thresholdIndexes[j] = j;
  }

  InstanceIdentifierVectorType maxVarThresholdIndexes = thresholdIndexes;

  // Compute frequency and mean of initial classes
  FrequencyType       freqSum{};
  FrequencyVectorType classFrequency(numberOfClasses);
  for (SizeValueType j = 0; j < numberOfClasses - 1; ++j)
  {
    classFrequency[j] = histogram->GetFrequency(thresholdIndexes[j]);
    freqSum += classFrequency[j];
  }
  classFrequency[numberOfClasses - 1] = globalFrequency - freqSum;

  // Convert the frequencies to probabilities (i.e. normalize the histogram).
  const SizeValueType histSize = histogram->GetSize()[0];
  WeightVectorType    imgPDF(histSize);
  for (SizeValueType j = 0; j < histSize; ++j)
  {
    imgPDF[j] = (WeightType)histogram->GetFrequency(j) / (WeightType)globalFrequency;
  }

  MeanType       meanSum{};
  MeanVectorType classMean(numberOfClasses);
  for (SizeValueType j = 0; j < numberOfClasses - 1; ++j)
  {
    if (NumericTraits<FrequencyType>::IsPositive(classFrequency[j]))
    {
      classMean[j] = static_cast<MeanType>(histogram->GetMeasurementVector(j)[0]);
    }
    else
    {
      classMean[j] = MeanType{};
    }
    meanSum += classMean[j] * static_cast<MeanType>(classFrequency[j]);
  }

  if (NumericTraits<FrequencyType>::IsPositive(classFrequency[numberOfClasses - 1]))
  {
    classMean[numberOfClasses - 1] = (globalMean * static_cast<MeanType>(globalFrequency) - meanSum) /
                                     static_cast<MeanType>(classFrequency[numberOfClasses - 1]);
  }
  else
  {
    classMean[numberOfClasses - 1] = MeanType{};
  }

  //
  // The "volatile" modifier is used here for preventing the variable from
  // being kept in 80 bit FPU registers when using 32-bit x86 processors with
  // SSE instructions disabled. A case that arose in the Debian 32-bits
  // distribution.
  //
#ifndef ITK_COMPILER_SUPPORTS_SSE2_32
  volatile VarianceType maxVarBetween{};
#else
  VarianceType maxVarBetween{};
#endif
  //
  // The introduction of the "volatile" modifier forces the compiler to keep
  // the variable in memory and therefore store it in the IEEE float/double
  // format. In this way making numerical results consistent across platforms.
  //

  for (SizeValueType j = 0; j < numberOfClasses; ++j)
  {
    maxVarBetween +=
      (static_cast<VarianceType>(classFrequency[j])) * static_cast<VarianceType>((classMean[j]) * (classMean[j]));
  }
  maxVarBetween /= static_cast<VarianceType>(globalFrequency);

  // Sum the relevant weights for valley emphasis
  WeightType valleyEmphasisFactor{};
  if (m_ValleyEmphasis)
  {
    for (SizeValueType j = 0; j < numberOfClasses - 1; ++j)
    {
      valleyEmphasisFactor = imgPDF[thresholdIndexes[j]];
    }
    valleyEmphasisFactor = 1.0 - valleyEmphasisFactor;
    maxVarBetween = maxVarBetween * valleyEmphasisFactor;
  }

  // Explore all possible threshold configurations and choose the one that
  // yields maximum between-class variance
  while (Self::IncrementThresholds(thresholdIndexes, globalMean, classMean, classFrequency))
  {

    //
    // The "volatile" modifier is used here for preventing the variable from
    // being kept in 80 bit FPU registers when using 32-bit x86 processors with
    // SSE instructions disabled. A case that arose in the Debian 32-bits
    // distribution.
    //
#ifndef ITK_COMPILER_SUPPORTS_SSE2_32
    volatile VarianceType varBetween{};
#else
    VarianceType varBetween{};
#endif
    //
    // The introduction of the "volatile" modifier forces the compiler to keep
    // the variable in memory and therefore store it in the IEEE float/double
    // format. In this way making numerical results consistent across platforms.
    //

    for (SizeValueType j = 0; j < numberOfClasses; ++j)
    {
      // The true between-class variance \sigma_B^2 for any number of classes is defined as:
      // \sigma_B^2 = \sum_{k=1}^{M} \omega_k (\mu_k - \mu_T)^2
      // where \omega_k = classFrequency[j]/globalFrequency is the probability of the class,
      // \mu_k = classMean[j] is the mean of the class,
      // \mu_T = globalMean is the overall mean,
      // and M is the number of classes.
      // However, in the paper "A Fast Algorithm for Multilevel Thresholding" by Liao, Chen, and Chung,
      // it was shown that this can be simplified to
      // (\sum_{k=1}^{M} \omega_k \mu_k^2) - \mu_T^2
      // Since we are looking for the argmax, the second term can be ignored because it is a constant, leading to the
      // simpler
      // (\sum_{k=1}^{M} \omega_k \mu_k^2), which is what is implemented here.
      // Although this is no longer truly a "between class variance", we keep that name since it is only different by a
      // constant.
      varBetween +=
        (static_cast<VarianceType>(classFrequency[j])) * static_cast<VarianceType>((classMean[j]) * (classMean[j]));
    }
    varBetween /= static_cast<VarianceType>(globalFrequency);

    if (m_ValleyEmphasis)
    {
      // Sum relevant weights to get valley emphasis factor
      valleyEmphasisFactor = WeightType{};
      for (SizeValueType j = 0; j < numberOfClasses - 1; ++j)
      {
        valleyEmphasisFactor += imgPDF[thresholdIndexes[j]];
      }
      valleyEmphasisFactor = 1.0 - valleyEmphasisFactor;
      varBetween = varBetween * valleyEmphasisFactor;
    }

    constexpr unsigned int maxUlps = 1;
    if (varBetween > maxVarBetween && !Math::FloatAlmostEqual(maxVarBetween, varBetween, maxUlps))
    {
      maxVarBetween = varBetween;
      maxVarThresholdIndexes = thresholdIndexes;
    }
  }

  // Copy corresponding bin max to threshold vector
  m_Output.resize(m_NumberOfThresholds);

  for (SizeValueType j = 0; j < m_NumberOfThresholds; ++j)
  {
    if (m_ReturnBinMidpoint)
    {
      m_Output[j] = histogram->GetMeasurement(maxVarThresholdIndexes[j], 0);
    }
    else
    {
      m_Output[j] = histogram->GetMaxs()[0][maxVarThresholdIndexes[j]];
    }
  }
}

template <typename TInputHistogram>
void
OtsuMultipleThresholdsCalculator<TInputHistogram>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "NumberOfThresholds: " << m_NumberOfThresholds;

  os << indent << "Output: ";
  for (SizeValueType j = 0; j < m_NumberOfThresholds; ++j)
  {
    os << m_Output[j] << ' ';
  }
  os << std::endl;
}
} // end namespace itk

#endif
