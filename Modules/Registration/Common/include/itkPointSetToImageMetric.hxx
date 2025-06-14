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
#ifndef itkPointSetToImageMetric_hxx
#define itkPointSetToImageMetric_hxx


namespace itk
{

template <typename TFixedPointSet, typename TMovingImage>
PointSetToImageMetric<TFixedPointSet, TMovingImage>::PointSetToImageMetric()
  : m_FixedPointSet(nullptr)
  , m_MovingImage(nullptr)
  , m_Transform(nullptr)
  , m_Interpolator(nullptr)
  , m_ComputeGradient(true)
  , m_GradientImage(nullptr)
{
  // metric computes gradient by default
  // computed at initialization
}

template <typename TFixedPointSet, typename TMovingImage>
void
PointSetToImageMetric<TFixedPointSet, TMovingImage>::SetTransformParameters(const ParametersType & parameters) const
{
  if (!m_Transform)
  {
    itkExceptionMacro("Transform has not been assigned");
  }
  m_Transform->SetParameters(parameters);
}

template <typename TFixedPointSet, typename TMovingImage>
void
PointSetToImageMetric<TFixedPointSet, TMovingImage>::Initialize()
{
  if (!m_Transform)
  {
    itkExceptionMacro("Transform is not present");
  }

  if (!m_Interpolator)
  {
    itkExceptionMacro("Interpolator is not present");
  }

  if (!m_MovingImage)
  {
    itkExceptionMacro("MovingImage is not present");
  }

  if (!m_FixedPointSet)
  {
    itkExceptionMacro("FixedPointSet is not present");
  }

  // If the image is provided by a source, update the source.
  m_MovingImage->UpdateSource();

  // If the point set is provided by a source, update the source.
  m_FixedPointSet->UpdateSource();

  m_Interpolator->SetInputImage(m_MovingImage);

  if (m_ComputeGradient)
  {
    const GradientImageFilterPointer gradientFilter = GradientImageFilterType::New();

    gradientFilter->SetInput(m_MovingImage);

    const typename MovingImageType::SpacingType & spacing = m_MovingImage->GetSpacing();
    double                                        maximumSpacing = 0.0;
    for (unsigned int i = 0; i < MovingImageDimension; ++i)
    {
      if (spacing[i] > maximumSpacing)
      {
        maximumSpacing = spacing[i];
      }
    }
    gradientFilter->SetSigma(maximumSpacing);
    gradientFilter->SetNormalizeAcrossScale(true);

    gradientFilter->Update();

    m_GradientImage = gradientFilter->GetOutput();
  }
}

template <typename TFixedPointSet, typename TMovingImage>
void
PointSetToImageMetric<TFixedPointSet, TMovingImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "NumberOfPixelsCounted: "
     << static_cast<typename NumericTraits<SizeValueType>::PrintType>(m_NumberOfPixelsCounted) << std::endl;

  itkPrintSelfObjectMacro(FixedPointSet);
  itkPrintSelfObjectMacro(MovingImage);
  itkPrintSelfObjectMacro(Transform);
  itkPrintSelfObjectMacro(Interpolator);

  itkPrintSelfBooleanMacro(ComputeGradient);

  itkPrintSelfObjectMacro(GradientImage);
}
} // end namespace itk

#endif
