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
#ifndef itkConvolutionImageFilterBase_hxx
#define itkConvolutionImageFilterBase_hxx


namespace itk
{
template <typename TInputImage, typename TKernelImage, typename TOutputImage>
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::ConvolutionImageFilterBase()
  : m_BoundaryCondition(&m_DefaultBoundaryCondition)
{
  this->AddRequiredInputName("KernelImage");
}

template <typename TInputImage, typename TKernelImage, typename TOutputImage>
void
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::GenerateOutputInformation()
{
  // Call the superclass' implementation of this method. Default
  // behavior corresponds to SAME output region mode.
  Superclass::GenerateOutputInformation();

  if (m_OutputRegionMode == ConvolutionImageFilterBaseEnums::ConvolutionImageFilterOutputRegion::VALID)
  {
    const OutputRegionType validRegion = this->GetValidRegion();

    const typename OutputImageType::Pointer outputPtr = this->GetOutput();
    outputPtr->SetLargestPossibleRegion(validRegion);
  }
}

template <typename TInputImage, typename TKernelImage, typename TOutputImage>
auto
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::GetValidRegion() const -> OutputRegionType
{
  const typename InputImageType::ConstPointer inputPtr = this->GetInput();

  const InputRegionType inputLargestPossibleRegion = inputPtr->GetLargestPossibleRegion();

  OutputIndexType validIndex = inputLargestPossibleRegion.GetIndex();
  OutputSizeType  validSize = inputLargestPossibleRegion.GetSize();

  // Shrink the output largest possible region by the kernel radius.
  KernelSizeType kernelSize = this->GetKernelImage()->GetLargestPossibleRegion().GetSize();
  KernelSizeType radius;
  for (unsigned int i = 0; i < ImageDimension; ++i)
  {
    radius[i] = kernelSize[i] / 2;
    if (validSize[i] < 2 * radius[i])
    {
      validIndex[i] = 0;
      validSize[i] = 0;
    }
    else
    {
      validIndex[i] = validIndex[i] + static_cast<typename OutputIndexType::IndexValueType>(radius[i]);
      validSize[i] = validSize[i] - 2 * radius[i];

      // If the kernel is has an even size in one dimension, then we
      // need to expand the image size by one and subtract one from
      // the index in that dimension to account for the zero-padding
      // on the low-index side of the image.
      if (kernelSize[i] % 2 == 0)
      {
        validIndex[i] -= 1;
        validSize[i] += 1;
      }
    }
  }

  const OutputRegionType validRegion(validIndex, validSize);

  return validRegion;
}

template <typename TInputImage, typename TKernelImage, typename TOutputImage>
void
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::SetOutputRegionModeToSame()
{
  this->SetOutputRegionMode(ConvolutionImageFilterBaseEnums::ConvolutionImageFilterOutputRegion::SAME);
}

template <typename TInputImage, typename TKernelImage, typename TOutputImage>
void
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::SetOutputRegionModeToValid()
{
  this->SetOutputRegionMode(ConvolutionImageFilterBaseEnums::ConvolutionImageFilterOutputRegion::VALID);
}

template <typename TInputImage, typename TKernelImage, typename TOutputImage>
void
ConvolutionImageFilterBase<TInputImage, TKernelImage, TOutputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Normalize: " << m_Normalize << std::endl;
  os << indent << "DefaultBoundaryCondition: ";
  m_DefaultBoundaryCondition.Print(os, indent);
  os << indent << "BoundaryCondition: ";
  if (m_BoundaryCondition)
  {
    m_BoundaryCondition->Print(os, indent);
  }
  else
  {
    os << indent << "nullptr" << std::endl;
  }
  os << indent << "OutputRegionMode: " << m_OutputRegionMode << std::endl;
}
} // namespace itk
#endif
