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

#ifndef itkDeconvolutionIterationCommand_h
#define itkDeconvolutionIterationCommand_h

#include "itkCommand.h"

namespace itk
{

template <typename TFilterType>
class DeconvolutionIterationCommand : public itk::Command
{
public:
  using Self = DeconvolutionIterationCommand;
  using Superclass = itk::Command;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);

  void
  Execute(itk::Object * caller, const itk::EventObject & event) override
  {
    this->Execute((const itk::Object *)caller, event);
  }

  void
  Execute(const itk::Object * object, const itk::EventObject & event) override
  {
    m_NumberOfIterations++;
    if (!itk::IterationEvent().CheckEvent(&event))
    {
      return;
    }
    std::cout << object->GetNameOfClass() << " iteration " << m_NumberOfIterations << std::endl;

    const auto * filter = static_cast<const TFilterType *>(object);
    if (filter->GetCurrentEstimate() == nullptr)
    {
      itkExceptionMacro("CurrentEstimate is nullptr, but should not be.");
    }
  }

  bool
  GetInvoked() const
  {
    return (m_NumberOfIterations > 0);
  }

protected:
  DeconvolutionIterationCommand() {}

private:
  int m_NumberOfIterations{};
};

} // end namespace itk

#endif
