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
#ifndef itkSTAPLEImageFilter_hxx
#define itkSTAPLEImageFilter_hxx

#include "itkImageScanlineIterator.h"
#include "itkMakeUniqueForOverwrite.h"
#include "itkPrintHelper.h"

namespace itk
{
template <typename TInputImage, typename TOutputImage>
void
STAPLEImageFilter<TInputImage, TOutputImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  using namespace print_helper;

  Superclass::PrintSelf(os, indent);

  os << indent
     << "ForegroundValue: " << static_cast<typename NumericTraits<InputPixelType>::PrintType>(m_ForegroundValue)
     << std::endl;
  os << indent << "ElapsedIterations: " << m_ElapsedIterations << std::endl;
  os << indent << "MaximumIterations: " << m_MaximumIterations << std::endl;
  os << indent << "ConfidenceWeight: " << m_ConfidenceWeight << std::endl;

  os << indent << "Sensitivity: " << m_Sensitivity << std::endl;
  os << indent << "Specificity: " << m_Specificity << std::endl;
}

template <typename TInputImage, typename TOutputImage>
void
STAPLEImageFilter<TInputImage, TOutputImage>::GenerateData()
{
  constexpr double epsilon = 1.0e-10;

  using IteratorType = ImageScanlineConstIterator<TInputImage>;
  using FuzzyIteratorType = ImageScanlineIterator<TOutputImage>;

  constexpr double min_rms_error = 1.0e-14; // 7 digits of precision

  // Allocate the output "fuzzy" image.
  this->GetOutput()->SetBufferedRegion(this->GetOutput()->GetRequestedRegion());
  this->GetOutput()->Allocate();
  const typename TOutputImage::Pointer W = this->GetOutput();

  // Initialize the output to all 0's
  W->FillBuffer(0.0);

  // Record the number of input files.
  const ProcessObject::DataObjectPointerArraySizeType number_of_input_files = this->GetNumberOfIndexedInputs();

  const auto D_it = make_unique_for_overwrite<IteratorType[]>(number_of_input_files);

  const auto p = make_unique_for_overwrite<double[]>(number_of_input_files); // sensitivity
  const auto q = make_unique_for_overwrite<double[]>(number_of_input_files); // specificity

  const auto last_q = make_unique_for_overwrite<double[]>(number_of_input_files);
  const auto last_p = make_unique_for_overwrite<double[]>(number_of_input_files);

  for (unsigned int i = 0; i < number_of_input_files; ++i)
  {
    last_p[i] = -10.0;
    last_q[i] = -10.0;
  }

  // Come up with an initial Wi which is simply the average of
  // all the segmentations.
  for (unsigned int i = 0; i < number_of_input_files; ++i)
  {
    if (this->GetInput(i)->GetRequestedRegion() != W->GetRequestedRegion())
    {
      itkExceptionMacro("One or more input images do not contain matching RequestedRegions");
    }

    IteratorType      in = IteratorType(this->GetInput(i), W->GetRequestedRegion());
    FuzzyIteratorType out = FuzzyIteratorType(W, W->GetRequestedRegion());

    while (!in.IsAtEnd())
    {
      while (!in.IsAtEndOfLine())
      {
        if (in.Get() > m_ForegroundValue - epsilon && in.Get() < m_ForegroundValue + epsilon)
        {
          out.Set(out.Get() + 1.0);
        }
        ++in;
        ++out;
      } // end scanline
      in.NextLine();
      out.NextLine();
    } // end while
  }

  // Divide sum by num of files, calculate the estimate of g_t

  double N = 0.0;
  double g_t = 0.0;
  {
    FuzzyIteratorType out = FuzzyIteratorType(W, W->GetRequestedRegion());
    while (!out.IsAtEnd())
    {
      while (!out.IsAtEndOfLine())
      {
        out.Set(out.Get() / static_cast<double>(number_of_input_files));
        g_t += out.Get();
        N = N + 1.0;
        ++out;
      } // end of scanline
      out.NextLine();
    }
    g_t = (g_t / N) * m_ConfidenceWeight;
  }
  unsigned int iter = 0;
  for (; iter < m_MaximumIterations; ++iter)
  {
    // Now iterate on estimating specificity and sensitivity
    for (unsigned int i = 0; i < number_of_input_files; ++i)
    {
      IteratorType      in = IteratorType(this->GetInput(i), W->GetRequestedRegion());
      FuzzyIteratorType out = FuzzyIteratorType(W, W->GetRequestedRegion());

      double p_num{};
      double p_denom{};
      double q_num{};
      double q_denom{};

      // Sensitivity and specificity of this user
      while (!in.IsAtEnd())
      {
        while (!in.IsAtEndOfLine())
        {
          if (in.Get() > m_ForegroundValue - epsilon && in.Get() < m_ForegroundValue + epsilon) // Dij == 1
          {
            p_num += out.Get(); // out.Get() := Wi
          }
          else //        if (in.Get() != m_ForegroundValue) // Dij == 0
          {
            q_num += (1.0 - out.Get()); // out.Get() := Wi
          }
          p_denom += out.Get();
          q_denom += (1.0 - out.Get());
          ++in;
          ++out;
        } // end of scanline
        in.NextLine();
        out.NextLine();
      }

      p[i] = p_num / p_denom;
      q[i] = q_num / q_denom;
    }

    // Now recreate W using the new p's and q's
    // Need an iterator on each D
    // constexpr double g_t = 0.1;  // prior likelihood that a pixel is incl.in
    // segmentation
    for (unsigned int i = 0; i < number_of_input_files; ++i)
    {
      D_it[i] = IteratorType(this->GetInput(i), W->GetRequestedRegion());
    }

    FuzzyIteratorType out = FuzzyIteratorType(W, W->GetRequestedRegion());
    while (!out.IsAtEnd())
    {
      while (!out.IsAtEndOfLine())
      {
        double alpha1{ 1.0 };
        double beta1{ 1.0 };
        for (unsigned int i = 0; i < number_of_input_files; ++i)
        {
          if (D_it[i].Get() > m_ForegroundValue - epsilon && D_it[i].Get() < m_ForegroundValue + epsilon)
          // Dij == 1
          {
            alpha1 = alpha1 * p[i];
            beta1 = beta1 * (1.0 - q[i]);
          }
          else // Dij == 0
          {
            alpha1 = alpha1 * (1.0 - p[i]);
            beta1 = beta1 * q[i];
          }
          ++D_it[i];
        }
        out.Set(g_t * alpha1 / (g_t * alpha1 + (1.0 - g_t) * beta1));
        ++out;
      } // end scanline
      for (unsigned int i = 0; i < number_of_input_files; ++i)
      {
        D_it[i].NextLine();
      }
      out.NextLine();
    }

    this->InvokeEvent(IterationEvent());

    // Check for convergence
    bool flag = false;
    if (iter != 0) // not on the first iteration
    {
      flag = true;
      for (unsigned int i = 0; i < number_of_input_files; ++i)
      {
        if (((p[i] - last_p[i]) * (p[i] - last_p[i])) > min_rms_error)
        {
          flag = false;
          break;
        }
        if (((q[i] - last_q[i]) * (q[i] - last_q[i])) > min_rms_error)
        {
          flag = false;
          break;
        }
      }
    }
    for (unsigned int i = 0; i < number_of_input_files; ++i)
    {
      last_p[i] = p[i];
      last_q[i] = q[i];
    }

    if (this->GetAbortGenerateData())
    {
      this->ResetPipeline();
      flag = true;
    }

    if (flag)
    {
      break;
    }
  }

  // Copy p's, q's, etc. to member variables

  m_Sensitivity.clear();
  m_Specificity.clear();
  for (unsigned int i = 0; i < number_of_input_files; ++i)
  {
    m_Sensitivity.push_back(p[i]);
    m_Specificity.push_back(q[i]);
  }
  m_ElapsedIterations = iter;
}
} // end namespace itk

#endif
