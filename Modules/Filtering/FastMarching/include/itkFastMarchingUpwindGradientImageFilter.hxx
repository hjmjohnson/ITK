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
#ifndef itkFastMarchingUpwindGradientImageFilter_hxx
#define itkFastMarchingUpwindGradientImageFilter_hxx

#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"
#include "itkMath.h"
#include <algorithm>

namespace itk
{

template <typename TLevelSet, typename TSpeedImage>
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::FastMarchingUpwindGradientImageFilter()
  : m_TargetPoints(nullptr)
  , m_ReachedTargetPoints(nullptr)
  , m_GradientImage(GradientImageType::New())
  , m_TargetOffset(1.0)
  , m_TargetReachedMode(TargetConditionEnum::NoTargets)
{}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  itkPrintSelfObjectMacro(TargetPoints);
  itkPrintSelfObjectMacro(ReachedTargetPoints);
  itkPrintSelfObjectMacro(GradientImage);

  itkPrintSelfBooleanMacro(GenerateGradientImage);
  os << indent << "TargetOffset: " << m_TargetOffset << std::endl;
  os << indent << "TargetReachedMode: " << m_TargetReachedMode << std::endl;
  os << indent << "TargetValue: " << m_TargetValue << std::endl;
  os << indent
     << "NumberOfTargets: " << static_cast<typename NumericTraits<SizeValueType>::PrintType>(m_NumberOfTargets)
     << std::endl;
}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::VerifyPreconditions() const
{
  Superclass::VerifyPreconditions();

  switch (this->m_TargetReachedMode)
  {
    case TargetConditionEnum::AllTargets:
      this->VerifyTargetReachedModeConditions(this->m_NumberOfTargets);
      break;
    case TargetConditionEnum::OneTarget:
      this->VerifyTargetReachedModeConditions(1);
      break;
    case TargetConditionEnum::SomeTargets:
      this->VerifyTargetReachedModeConditions(this->m_NumberOfTargets);
      break;
    case TargetConditionEnum::NoTargets:
      break;
    default:
      break;
  }
}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::Initialize(LevelSetImageType * output)
{
  Superclass::Initialize(output);

  // allocate memory for the GradientImage if requested
  if (m_GenerateGradientImage)
  {
    m_GradientImage->CopyInformation(this->GetInput());
    m_GradientImage->SetBufferedRegion(output->GetBufferedRegion());
    m_GradientImage->Allocate();
  }

  // set all gradient vectors to zero
  if (m_GenerateGradientImage)
  {
    using GradientIterator = ImageRegionIterator<GradientImageType>;

    GradientIterator gradientIt(m_GradientImage, m_GradientImage->GetBufferedRegion());

    GradientPixelType zeroGradient;
    using GradientPixelValueType = typename GradientPixelType::ValueType;
    zeroGradient.Fill(GradientPixelValueType{});
    for (gradientIt.GoToBegin(); !gradientIt.IsAtEnd(); ++gradientIt)
    {
      gradientIt.Set(zeroGradient);
    }
  }

  // Need to reset the target value.
  m_TargetValue = 0.0;

  // Even if there are no targets, a new NodeContainer should be created
  // so that querying this structure does not crash.
  m_ReachedTargetPoints = NodeContainer::New();
}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::GenerateData()
{
  // cache the original stopping value that was set by the user
  // because this subclass may change it once a target point is
  // reached in order to control the execution of the superclass.
  const double stoppingValue = this->GetStoppingValue();

  // run the GenerateData() method of the superclass
  try
  {
    Superclass::GenerateData();
  }
  catch (const ProcessAborted &)
  {
    // process was aborted, clean up the state of the filter
    // (most of the cleanup will have already been done by the
    // superclass)

    // restore the original stopping value
    this->SetStoppingValue(stoppingValue);
    throw;
  }

  // restore the original stopping value
  this->SetStoppingValue(stoppingValue);
}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::UpdateNeighbors(const IndexType &      index,
                                                                               const SpeedImageType * speedImage,
                                                                               LevelSetImageType *    output)
{
  Superclass::UpdateNeighbors(index, speedImage, output);

  if (m_GenerateGradientImage)
  {
    this->ComputeGradient(index, output, this->GetLabelImage(), m_GradientImage);
  }

  AxisNodeType node;

  // Only check for reached targets if the mode is not TargetConditionEnum::NoTargets and
  // there is at least one TargetPoint.
  if (m_TargetReachedMode != TargetConditionEnum::NoTargets && m_TargetPoints)
  {
    bool targetReached = false;

    if (m_TargetReachedMode == TargetConditionEnum::OneTarget)
    {
      typename NodeContainer::ConstIterator       pointsIter = m_TargetPoints->Begin();
      const typename NodeContainer::ConstIterator pointsEnd = m_TargetPoints->End();
      for (; pointsIter != pointsEnd; ++pointsIter)
      {
        node = pointsIter.Value();
        if (node.GetIndex() == index)
        {
          m_ReachedTargetPoints->InsertElement(m_ReachedTargetPoints->Size(), node);
          targetReached = true;
          break;
        }
      }
    }
    else if (m_TargetReachedMode == TargetConditionEnum::SomeTargets)
    {
      typename NodeContainer::ConstIterator       pointsIter = m_TargetPoints->Begin();
      const typename NodeContainer::ConstIterator pointsEnd = m_TargetPoints->End();
      for (; pointsIter != pointsEnd; ++pointsIter)
      {
        node = pointsIter.Value();

        if (node.GetIndex() == index)
        {
          m_ReachedTargetPoints->InsertElement(m_ReachedTargetPoints->Size(), node);
          break;
        }
      }

      if (static_cast<SizeValueType>(m_ReachedTargetPoints->Size()) == m_NumberOfTargets)
      {
        targetReached = true;
      }
    }
    else if (m_TargetReachedMode == TargetConditionEnum::AllTargets)
    {
      typename NodeContainer::ConstIterator       pointsIter = m_TargetPoints->Begin();
      const typename NodeContainer::ConstIterator pointsEnd = m_TargetPoints->End();
      for (; pointsIter != pointsEnd; ++pointsIter)
      {
        node = pointsIter.Value();

        if (node.GetIndex() == index)
        {
          m_ReachedTargetPoints->InsertElement(m_ReachedTargetPoints->Size(), node);
          break;
        }
      }

      if (m_ReachedTargetPoints->Size() == m_TargetPoints->Size())
      {
        targetReached = true;
      }
    }

    if (targetReached)
    {
      m_TargetValue = static_cast<double>(output->GetPixel(index));
      const double newStoppingValue = m_TargetValue + m_TargetOffset;
      if (newStoppingValue < this->GetStoppingValue())
      {
        // This changes the stopping value that may have been set by
        // the user.  Therefore, the value set by the user needs to be
        // cached in GenerateUpdate() so that it will be correct for
        // future Update() commands.
        this->SetStoppingValue(newStoppingValue);
      }
    }
  }
  else
  {
    m_TargetValue = static_cast<double>(output->GetPixel(index));
  }
}

template <typename TLevelSet, typename TSpeedImage>
void
FastMarchingUpwindGradientImageFilter<TLevelSet, TSpeedImage>::ComputeGradient(
  const IndexType &         index,
  const LevelSetImageType * output,
  const LabelImageType *    itkNotUsed(labelImage),
  GradientImageType *       gradientImage)
{
  IndexType neighIndex = index;

  using LevelSetPixelType = typename TLevelSet::PixelType;
  LevelSetPixelType centerPixel;
  LevelSetPixelType dx_forward;
  LevelSetPixelType dx_backward;
  GradientPixelType gradientPixel;

  const LevelSetIndexType & lastIndex = this->GetLastIndex();
  const LevelSetIndexType & startIndex = this->GetStartIndex();

  constexpr LevelSetPixelType ZERO{};

  OutputSpacingType spacing = this->GetOutput()->GetSpacing();

  unsigned int xStride[Self::SetDimension];

  for (unsigned int j = 0; j < SetDimension; ++j)
  {
    centerPixel = output->GetPixel(index);

    neighIndex = index;

    // Set stride of one in each direction
    xStride[j] = 1;

    // Compute one-sided finite differences with alive neighbors
    // (the front can only come from there)
    dx_backward = 0.0;
    neighIndex[j] = index[j] - xStride[j];

    if (!(neighIndex[j] > lastIndex[j] || neighIndex[j] < startIndex[j]))
    {
      if (this->GetLabelImage()->GetPixel(neighIndex) == Superclass::LabelEnum::AlivePoint)
      {
        dx_backward = centerPixel - output->GetPixel(neighIndex);
      }
    }

    dx_forward = 0.0;
    neighIndex[j] = index[j] + xStride[j];

    if (!(neighIndex[j] > lastIndex[j] || neighIndex[j] < startIndex[j]))
    {
      if (this->GetLabelImage()->GetPixel(neighIndex) == Superclass::LabelEnum::AlivePoint)
      {
        dx_forward = output->GetPixel(neighIndex) - centerPixel;
      }
    }

    // Compute upwind finite differences
    if (std::max<LevelSetPixelType>(dx_backward, -dx_forward) < ZERO)
    {
      gradientPixel[j] = ZERO;
    }
    else if (dx_backward > -dx_forward)
    {
      gradientPixel[j] = dx_backward;
    }
    else
    {
      gradientPixel[j] = dx_forward;
    }
    gradientPixel[j] /= spacing[j];
  }

  gradientImage->SetPixel(index, gradientPixel);
}
} // namespace itk

#endif
