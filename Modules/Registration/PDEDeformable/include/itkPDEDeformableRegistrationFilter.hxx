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
#ifndef itkPDEDeformableRegistrationFilter_hxx
#define itkPDEDeformableRegistrationFilter_hxx


#include "itkImageRegionIterator.h"
#include "itkImageLinearIteratorWithIndex.h"
#include "itkDataObject.h"

#include "itkGaussianOperator.h"
#include "itkVectorNeighborhoodOperatorImageFilter.h"

#include "itkMath.h"

namespace itk
{

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::PDEDeformableRegistrationFilter()
{
  Self::RemoveRequiredInputName("Primary");

  // #0 "InitialDisplacementField" optional
  Self::AddOptionalInputName("InitialDisplacementField", 0);

  // #1 "FixedImage" required
  Self::AddRequiredInputName("FixedImage", 1);

  // #2 "MovingImage" required
  Self::AddRequiredInputName("MovingImage", 2);

  this->SetNumberOfIterations(10);
  for (unsigned int j = 0; j < ImageDimension; ++j)
  {
    m_StandardDeviations[j] = 1.0;
    m_UpdateFieldStandardDeviations[j] = 1.0;
  }

  m_TempField = DisplacementFieldType::New();
  m_MaximumError = 0.1;
  m_MaximumKernelWidth = 30;
  m_StopRegistrationFlag = false;

  m_SmoothDisplacementField = true;
  m_SmoothUpdateField = false;
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
std::vector<SmartPointer<DataObject>>::size_type
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::GetNumberOfValidRequiredInputs() const
{
  typename std::vector<SmartPointer<DataObject>>::size_type num = 0;

  if (this->GetFixedImage())
  {
    ++num;
  }

  if (this->GetMovingImage())
  {
    ++num;
  }

  return num;
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::SetStandardDeviations(double value)
{
  if (ContainerFillWithCheck(m_StandardDeviations, value, ImageDimension))
  {
    this->Modified();
  }
}

/*
 * Set the standard deviations.
 */
template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::SetUpdateFieldStandardDeviations(
  double value)
{
  if (ContainerFillWithCheck(m_StandardDeviations, value, ImageDimension))
  {
    this->Modified();
  }
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::PrintSelf(std::ostream & os,
                                                                                          Indent         indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "StandardDeviations: " << m_StandardDeviations << std::endl;
  os << indent << "UpdateFieldStandardDeviations: " << m_UpdateFieldStandardDeviations << std::endl;

  itkPrintSelfBooleanMacro(SmoothDisplacementField);
  itkPrintSelfBooleanMacro(SmoothUpdateField);

  itkPrintSelfObjectMacro(TempField);

  os << indent << "MaximumError: " << m_MaximumError << std::endl;
  os << indent << "MaximumKernelWidth: " << m_MaximumKernelWidth << std::endl;
  itkPrintSelfBooleanMacro(StopRegistrationFlag);
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::InitializeIteration()
{
  const MovingImageConstPointer movingPtr = this->GetMovingImage();
  const FixedImageConstPointer  fixedPtr = this->GetFixedImage();

  if (!movingPtr || !fixedPtr)
  {
    itkExceptionMacro("Fixed and/or moving image not set");
  }

  // update variables in the equation object
  auto * f = dynamic_cast<PDEDeformableRegistrationFunctionType *>(this->GetDifferenceFunction().GetPointer());

  if (!f)
  {
    itkExceptionMacro("FiniteDifferenceFunction not of type PDEDeformableRegistrationFilterFunction");
  }

  f->SetFixedImage(fixedPtr);
  f->SetMovingImage(movingPtr);

  this->Superclass::InitializeIteration();
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::CopyInputToOutput()
{
  const typename Superclass::InputImageType::ConstPointer inputPtr = this->GetInput();

  if (inputPtr)
  {
    this->Superclass::CopyInputToOutput();
  }
  else
  {
    typename Superclass::PixelType zeros;
    for (unsigned int j = 0; j < ImageDimension; ++j)
    {
      zeros[j] = 0;
    }

    const typename OutputImageType::Pointer output = this->GetOutput();

    ImageRegionIterator<OutputImageType> out(output, output->GetRequestedRegion());

    while (!out.IsAtEnd())
    {
      out.Value() = zeros;
      ++out;
    }
  }
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::GenerateOutputInformation()
{
  typename DataObject::Pointer output;

  if (this->GetInput(0))
  {
    // Initial deformation field is set.
    // Copy information from initial field.
    this->Superclass::GenerateOutputInformation();
  }
  else if (this->GetFixedImage())
  {
    // Initial deformation field is not set.
    // Copy information from the fixed image.
    for (unsigned int idx = 0; idx < this->GetNumberOfIndexedOutputs(); ++idx)
    {
      output = this->GetOutput(idx);
      if (output)
      {
        output->CopyInformation(this->GetFixedImage());
      }
    }
  }
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::GenerateInputRequestedRegion()
{
  // call the superclass's implementation
  Superclass::GenerateInputRequestedRegion();

  // request the largest possible region for the moving image
  const MovingImagePointer movingPtr = const_cast<MovingImageType *>(this->GetMovingImage());
  if (movingPtr)
  {
    movingPtr->SetRequestedRegionToLargestPossibleRegion();
  }

  // just propagate up the output requested region for
  // the fixed image and initial deformation field.
  const DisplacementFieldPointer inputPtr = const_cast<DisplacementFieldType *>(this->GetInput());
  const DisplacementFieldPointer outputPtr = this->GetOutput();
  const FixedImagePointer        fixedPtr = const_cast<FixedImageType *>(this->GetFixedImage());

  if (inputPtr)
  {
    inputPtr->SetRequestedRegion(outputPtr->GetRequestedRegion());
  }

  if (fixedPtr)
  {
    fixedPtr->SetRequestedRegion(outputPtr->GetRequestedRegion());
  }
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::PostProcessOutput()
{
  this->Superclass::PostProcessOutput();
  m_TempField->Initialize();
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::Initialize()
{
  this->Superclass::Initialize();
  m_StopRegistrationFlag = false;
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::SmoothDisplacementField()
{
  const DisplacementFieldPointer field = this->GetOutput();

  // copy field to TempField
  m_TempField->SetOrigin(field->GetOrigin());
  m_TempField->SetSpacing(field->GetSpacing());
  m_TempField->SetDirection(field->GetDirection());
  m_TempField->SetLargestPossibleRegion(field->GetLargestPossibleRegion());
  m_TempField->SetRequestedRegion(field->GetRequestedRegion());
  m_TempField->SetBufferedRegion(field->GetBufferedRegion());
  m_TempField->Allocate();

  using VectorType = typename DisplacementFieldType::PixelType;
  using ScalarType = typename VectorType::ValueType;
  using OperatorType = GaussianOperator<ScalarType, ImageDimension>;
  using SmootherType = VectorNeighborhoodOperatorImageFilter<DisplacementFieldType, DisplacementFieldType>;

  OperatorType oper;
  auto         smoother = SmootherType::New();

  using PixelContainerPointer = typename DisplacementFieldType::PixelContainerPointer;
  PixelContainerPointer swapPtr;

  // graft the output field onto the mini-pipeline
  smoother->GraftOutput(m_TempField);

  for (unsigned int j = 0; j < ImageDimension; ++j)
  {
    // smooth along this dimension
    oper.SetDirection(j);
    const double variance = itk::Math::sqr(m_StandardDeviations[j]);
    oper.SetVariance(variance);
    oper.SetMaximumError(m_MaximumError);
    oper.SetMaximumKernelWidth(m_MaximumKernelWidth);
    oper.CreateDirectional();

    // todo: make sure we only smooth within the buffered region
    smoother->SetOperator(oper);
    smoother->SetInput(field);
    smoother->Update();

    if (j + 1 < ImageDimension)
    {
      // swap the containers
      swapPtr = smoother->GetOutput()->GetPixelContainer();
      smoother->GraftOutput(field);
      field->SetPixelContainer(swapPtr);
      smoother->Modified();
    }
  }

  // graft the output back to this filter
  m_TempField->SetPixelContainer(field->GetPixelContainer());
  this->GraftOutput(smoother->GetOutput());
}

template <typename TFixedImage, typename TMovingImage, typename TDisplacementField>
void
PDEDeformableRegistrationFilter<TFixedImage, TMovingImage, TDisplacementField>::SmoothUpdateField()
{
  // The update buffer will be overwritten with new data.
  const DisplacementFieldPointer field = this->GetUpdateBuffer();

  using VectorType = typename DisplacementFieldType::PixelType;
  using ScalarType = typename VectorType::ValueType;
  using OperatorType = GaussianOperator<ScalarType, ImageDimension>;
  using SmootherType = VectorNeighborhoodOperatorImageFilter<DisplacementFieldType, DisplacementFieldType>;

  OperatorType                   opers[ImageDimension];
  typename SmootherType::Pointer smoothers[ImageDimension];

  for (unsigned int j = 0; j < ImageDimension; ++j)
  {
    // smooth along this dimension
    opers[j].SetDirection(j);
    const double variance = itk::Math::sqr(this->GetUpdateFieldStandardDeviations()[j]);
    // double variance = itk::Math::sqr( 1.0 );
    opers[j].SetVariance(variance);
    opers[j].SetMaximumError(this->GetMaximumError());
    opers[j].SetMaximumKernelWidth(this->GetMaximumKernelWidth());
    opers[j].CreateDirectional();

    smoothers[j] = SmootherType::New();
    smoothers[j]->SetOperator(opers[j]);
    smoothers[j]->ReleaseDataFlagOn();

    if (j > 0)
    {
      smoothers[j]->SetInput(smoothers[j - 1]->GetOutput());
    }
  }
  smoothers[0]->SetInput(field);
  smoothers[ImageDimension - 1]->GetOutput()->SetRequestedRegion(field->GetBufferedRegion());

  smoothers[ImageDimension - 1]->Update();

  // field to contain the final smoothed data, do the equivalent of a graft
  field->SetPixelContainer(smoothers[ImageDimension - 1]->GetOutput()->GetPixelContainer());
  field->SetRequestedRegion(smoothers[ImageDimension - 1]->GetOutput()->GetRequestedRegion());
  field->SetBufferedRegion(smoothers[ImageDimension - 1]->GetOutput()->GetBufferedRegion());
  field->SetLargestPossibleRegion(smoothers[ImageDimension - 1]->GetOutput()->GetLargestPossibleRegion());
  field->CopyInformation(smoothers[ImageDimension - 1]->GetOutput());
}
} // end namespace itk

#endif
