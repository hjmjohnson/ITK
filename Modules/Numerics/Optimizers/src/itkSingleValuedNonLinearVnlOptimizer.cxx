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

#include "itkSingleValuedNonLinearVnlOptimizer.h"

namespace itk
{
/** Constructor */
SingleValuedNonLinearVnlOptimizer::SingleValuedNonLinearVnlOptimizer()
{
  m_CostFunctionAdaptor = nullptr;
  m_Maximize = false;
  m_Command = CommandType::New();
  m_Command->SetCallbackFunction(this, &SingleValuedNonLinearVnlOptimizer::IterationReport);
  m_CachedValue = 0;
  m_CachedCurrentPosition.Fill(0);
  m_CachedDerivative.Fill(0);
}

/** Destructor */
SingleValuedNonLinearVnlOptimizer::~SingleValuedNonLinearVnlOptimizer() = default;

void
SingleValuedNonLinearVnlOptimizer::SetCostFunctionAdaptor(CostFunctionAdaptorType * adaptor)
{
  if (m_CostFunctionAdaptor.get() == adaptor)
  {
    return;
  }

  m_CostFunctionAdaptor.reset(adaptor);

  m_CostFunctionAdaptor->AddObserver(IterationEvent(), m_Command);
}

const SingleValuedNonLinearVnlOptimizer::CostFunctionAdaptorType *
SingleValuedNonLinearVnlOptimizer::GetCostFunctionAdaptor() const
{
  return m_CostFunctionAdaptor.get();
}

SingleValuedNonLinearVnlOptimizer::CostFunctionAdaptorType *
SingleValuedNonLinearVnlOptimizer::GetCostFunctionAdaptor()
{
  return m_CostFunctionAdaptor.get();
}

/** The purpose of this method is to get around the lack of
 *  const-correctness in VNL cost-functions and optimizers */
SingleValuedNonLinearVnlOptimizer::CostFunctionAdaptorType *
SingleValuedNonLinearVnlOptimizer::GetNonConstCostFunctionAdaptor() const
{
  return m_CostFunctionAdaptor.get();
}

/** The purpose of this method is to get around the lack of iteration reporting
 * in VNL optimizers. By interfacing directly with the ITK cost function
 * adaptor we are generating here Iteration Events. Note the iteration events
 * here are produce PER EVALUATION of the metric, not per real iteration of the
 * vnl optimizer. Optimizers that evaluate the metric multiple times at each
 * iteration will generate a lot more of Iteration events here. */
void
SingleValuedNonLinearVnlOptimizer::IterationReport(const EventObject & event)
{
  const CostFunctionAdaptorType * adaptor = this->GetCostFunctionAdaptor();

  m_CachedValue = adaptor->GetCachedValue();
  m_CachedDerivative = adaptor->GetCachedDerivative();
  m_CachedCurrentPosition = adaptor->GetCachedCurrentParameters();
  this->InvokeEvent(event);
}

/**
 * PrintSelf
 */
void
SingleValuedNonLinearVnlOptimizer::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  itkPrintSelfBooleanMacro(Maximize);
  os << indent << "Cached Value: " << m_CachedValue << '\n';
  os << indent << "Cached Derivative: " << m_CachedDerivative << '\n';
  os << indent << "Cached current positiion: " << m_CachedCurrentPosition << '\n';
  os << indent << "Command observer " << m_Command.GetPointer() << '\n';
  os << indent << "Cost Function adaptor" << m_CostFunctionAdaptor.get() << '\n';
}
} // end namespace itk
