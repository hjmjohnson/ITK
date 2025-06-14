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
#ifndef itkGradientDescentLineSearchOptimizerv4_hxx
#define itkGradientDescentLineSearchOptimizerv4_hxx


namespace itk
{

template <typename TInternalComputationValueType>
GradientDescentLineSearchOptimizerv4Template<
  TInternalComputationValueType>::GradientDescentLineSearchOptimizerv4Template()
  : m_LowerLimit(TInternalComputationValueType{})
  , m_UpperLimit(5.0)
  , m_Phi(1.618034)
  , m_Resphi(2 - this->m_Phi)
  , m_Epsilon(0.01)
  , m_MaximumLineSearchIterations(20)

{
  this->m_ReturnBestParametersAndValue = true;
}

template <typename TInternalComputationValueType>
void
GradientDescentLineSearchOptimizerv4Template<TInternalComputationValueType>::PrintSelf(std::ostream & os,
                                                                                       Indent         indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent
     << "LowerLimit: " << static_cast<typename NumericTraits<TInternalComputationValueType>::PrintType>(m_LowerLimit)
     << std::endl;
  os << indent
     << "UpperLimit: " << static_cast<typename NumericTraits<TInternalComputationValueType>::PrintType>(m_UpperLimit)
     << std::endl;
  os << indent << "Phi: " << static_cast<typename NumericTraits<TInternalComputationValueType>::PrintType>(m_Phi)
     << std::endl;
  os << indent << "Resphi: " << static_cast<typename NumericTraits<TInternalComputationValueType>::PrintType>(m_Resphi)
     << std::endl;
  os << indent
     << "Epsilon: " << static_cast<typename NumericTraits<TInternalComputationValueType>::PrintType>(m_Epsilon)
     << std::endl;

  os << indent << "MaximumLineSearchIterations: " << m_MaximumLineSearchIterations << std::endl;
  os << indent << "LineSearchIterations: " << m_LineSearchIterations << std::endl;
}

template <typename TInternalComputationValueType>
void
GradientDescentLineSearchOptimizerv4Template<TInternalComputationValueType>::AdvanceOneStep()
{
  itkDebugMacro("AdvanceOneStep");

  /* Modify the gradient by scales once at the begin */
  this->ModifyGradientByScales();

  /* This will estimate the learning rate (m_LearningRate)
   * if the options are set to do so. We only ever want to
   * estimate at the first step for this class. */
  if (this->m_CurrentIteration == 0)
  {
    this->EstimateLearningRate();
  }

  this->m_LineSearchIterations = 0;
  this->m_LearningRate = this->GoldenSectionSearch(
    this->m_LearningRate * this->m_LowerLimit, this->m_LearningRate, this->m_LearningRate * this->m_UpperLimit);

  /* Begin threaded gradient modification of m_Gradient variable. */
  this->ModifyGradientByLearningRate();

  try
  {
    /* Pass gradient to transform and let it do its own updating */
    this->m_Metric->UpdateTransformParameters(this->m_Gradient);
  }
  catch (const ExceptionObject &)
  {
    this->m_StopCondition = StopConditionObjectToObjectOptimizerEnum::UPDATE_PARAMETERS_ERROR;
    this->m_StopConditionDescription << "UpdateTransformParameters error";
    this->StopOptimization();
    // Pass exception to caller
    throw;
  }
  this->InvokeEvent(IterationEvent());
}


template <typename TInternalComputationValueType>
TInternalComputationValueType
GradientDescentLineSearchOptimizerv4Template<TInternalComputationValueType>::GoldenSectionSearch(
  TInternalComputationValueType a,
  TInternalComputationValueType b,
  TInternalComputationValueType c,
  TInternalComputationValueType metricb)
{
  itkDebugMacro("GoldenSectionSearch: " << a << ' ' << b << ' ' << c << ' ' << metricb);

  if (this->m_LineSearchIterations > this->m_MaximumLineSearchIterations)
  {
    return (c + a) / 2;
  }
  this->m_LineSearchIterations++;

  TInternalComputationValueType x;
  if (c - b > b - a)
  {
    x = b + this->m_Resphi * (c - b);
  }
  else
  {
    x = b - this->m_Resphi * (b - a);
  }
  if (itk::Math::abs(c - a) < this->m_Epsilon * (itk::Math::abs(b) + itk::Math::abs(x)))
  {
    return (c + a) / 2;
  }

  TInternalComputationValueType metricx;

  {
    // Cache the learning rate , parameters , gradient
    // Contain this in a block so these variables go out of
    // scope before we call recursively below. With dense transforms
    // we would otherwise eat up a lot of memory unnecessarily.
    TInternalComputationValueType baseLearningRate = this->m_LearningRate;
    const DerivativeType          baseGradient(this->m_Gradient);
    ParametersType                baseParameters(this->GetCurrentPosition());

    this->m_LearningRate = x;
    this->ModifyGradientByLearningRate();
    this->m_Metric->UpdateTransformParameters(this->m_Gradient);
    metricx = this->GetMetric()->GetValue();

    /** reset position of transform and gradient */
    this->m_Metric->SetParameters(baseParameters);
    this->m_Gradient = baseGradient;

    if (metricb == NumericTraits<TInternalComputationValueType>::max())
    {
      this->m_LearningRate = b;
      this->ModifyGradientByLearningRate();

      this->m_Metric->UpdateTransformParameters(this->m_Gradient);
      metricb = this->GetMetric()->GetValue();

      /** reset position of transform and learning rate */
      this->m_Metric->SetParameters(baseParameters);
      this->m_Gradient = baseGradient;
      this->m_LearningRate = baseLearningRate;
    }
  }

  /** golden section */
  if (metricx < metricb)
  {
    if (c - b > b - a)
    {
      return this->GoldenSectionSearch(b, x, c, metricx);
    }

    return this->GoldenSectionSearch(a, x, b, metricx);
  }
  else
  {
    if (c - b > b - a)
    {
      return this->GoldenSectionSearch(a, b, x, metricb);
    }
    if (metricx == NumericTraits<TInternalComputationValueType>::max())
    {
      // Keep the lower bounds when metricx and metricb are both max,
      // likely due to no valid sample points, from too large of a
      // learning rate.
      return this->GoldenSectionSearch(a, x, b, metricx);
    }
    else if (metricx == NumericTraits<TInternalComputationValueType>::max())
    {
      // Keep the lower bounds when metricx and metricb are both max,
      // likely due to no valid sample points, from too large of a
      // learning rate.
      return this->GoldenSectionSearch(a, x, b);
    }
    else
    {
      return this->GoldenSectionSearch(x, b, c, metricb);
    }
  }
}

} // namespace itk

#endif
