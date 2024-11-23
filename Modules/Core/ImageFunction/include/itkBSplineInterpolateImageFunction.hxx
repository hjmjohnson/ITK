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
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef itkBSplineInterpolateImageFunction_hxx
#define itkBSplineInterpolateImageFunction_hxx

#include "itkImageLinearIteratorWithIndex.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIterator.h"

#include "itkVector.h"

#include "itkMatrix.h"
#include "itkPrintHelper.h"

namespace itk
{

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::BSplineInterpolateImageFunction()
{
  m_NumberOfWorkUnits = 1;

  m_CoefficientFilter = CoefficientFilter::New();
  m_Coefficients = CoefficientImageType::New();

  m_SplineOrder = 0;
  unsigned int const SplineOrder = 3;
  this->SetSplineOrder(SplineOrder);
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::PrintSelf(std::ostream & os,
                                                                                    Indent         indent) const
{
  using namespace print_helper;

  Superclass::PrintSelf(os, indent);

  os << indent << "Scratch: " << m_Scratch << std::endl;
  os << indent
     << "DataLength: " << static_cast<typename NumericTraits<typename TImageType::SizeType>::PrintType>(m_DataLength)
     << std::endl;
  os << indent << "SplineOrder: " << m_SplineOrder << std::endl;

  itkPrintSelfObjectMacro(Coefficients);

  os << indent << "MaxNumberInterpolationPoints: " << m_MaxNumberInterpolationPoints << std::endl;
  os << indent << "PointsToIndex: " << m_PointsToIndex << std::endl;

  itkPrintSelfObjectMacro(CoefficientFilter);

  itkPrintSelfBooleanMacro(UseImageDirection);

  os << indent
     << "NumberOfWorkUnits: " << static_cast<typename NumericTraits<ThreadIdType>::PrintType>(m_NumberOfWorkUnits)
     << std::endl;

  os << indent << "ThreadedEvaluateIndex: ";
  if (m_ThreadedEvaluateIndex != nullptr)
  {
    os << m_ThreadedEvaluateIndex.get() << std::endl;
  }
  else
  {
    os << "(null)" << std::endl;
  }

  os << indent << "ThreadedWeights: ";
  if (m_ThreadedWeights != nullptr)
  {
    os << m_ThreadedWeights.get() << std::endl;
  }
  else
  {
    os << "(null)" << std::endl;
  }

  os << indent << "ThreadedWeightsDerivative: ";
  if (m_ThreadedWeightsDerivative != nullptr)
  {
    os << m_ThreadedWeightsDerivative.get() << std::endl;
  }
  else
  {
    os << "(null)" << std::endl;
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::SetInputImage(const TImageType * inputData)
{
  if (inputData)
  {
    m_CoefficientFilter->SetInput(inputData);

    m_CoefficientFilter->Update();
    m_Coefficients = m_CoefficientFilter->GetOutput();

    // Call the Superclass implementation after, in case the filter
    // pulls in  more of the input image
    Superclass::SetInputImage(inputData);

    m_DataLength = inputData->GetBufferedRegion().GetSize();
  }
  else
  {
    m_Coefficients = nullptr;
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::SetSplineOrder(unsigned int SplineOrder)
{
  if (SplineOrder == m_SplineOrder)
  {
    return;
  }
  m_SplineOrder = SplineOrder;
  m_CoefficientFilter->SetSplineOrder(SplineOrder);

  // this->SetPoles();
  m_MaxNumberInterpolationPoints = 1;
  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    m_MaxNumberInterpolationPoints *= (m_SplineOrder + 1);
  }
  this->GeneratePointsToIndex();
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::SetNumberOfWorkUnits(
  ThreadIdType numWorkUnits)
{
  m_NumberOfWorkUnits = numWorkUnits;
  this->GeneratePointsToIndex();
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::SetInterpolationWeights(
  const ContinuousIndexType & x,
  const vnl_matrix<long> &    EvaluateIndex,
  vnl_matrix<double> &        weights,
  unsigned int                splineOrder) const
{
  // For speed improvements we could make each case a separate function and use
  // function pointers to reference the correct weight order.
  // Left as is for now for readability.
  double w;
  double w2;
  double w4;
  double t;
  double t0;
  double t1;

  switch (splineOrder)
  {
    case 3:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] - static_cast<double>(EvaluateIndex[n][1]);
        weights[n][3] = (1.0 / 6.0) * w * w * w;
        weights[n][0] = (1.0 / 6.0) + 0.5 * w * (w - 1.0) - weights[n][3];
        weights[n][2] = w + weights[n][0] - 2.0 * weights[n][3];
        weights[n][1] = 1.0 - weights[n][0] - weights[n][2] - weights[n][3];
      }
      break;
    }
    case 0:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        weights[n][0] = 1; // implements nearest neighbor
      }
      break;
    }
    case 1:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] - static_cast<double>(EvaluateIndex[n][0]);
        weights[n][1] = w;
        weights[n][0] = 1.0 - w;
      }
      break;
    }
    case 2:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        /* x */
        w = x[n] - static_cast<double>(EvaluateIndex[n][1]);
        weights[n][1] = 0.75 - w * w;
        weights[n][2] = 0.5 * (w - weights[n][1] + 1.0);
        weights[n][0] = 1.0 - weights[n][1] - weights[n][2];
      }
      break;
    }
    case 4:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        /* x */
        w = x[n] - static_cast<double>(EvaluateIndex[n][2]);
        w2 = w * w;
        t = (1.0 / 6.0) * w2;
        weights[n][0] = 0.5 - w;
        weights[n][0] *= weights[n][0];
        weights[n][0] *= (1.0 / 24.0) * weights[n][0];
        t0 = w * (t - 11.0 / 24.0);
        t1 = 19.0 / 96.0 + w2 * (0.25 - t);
        weights[n][1] = t1 + t0;
        weights[n][3] = t1 - t0;
        weights[n][4] = weights[n][0] + t0 + 0.5 * w;
        weights[n][2] = 1.0 - weights[n][0] - weights[n][1] - weights[n][3] - weights[n][4];
      }
      break;
    }
    case 5:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        /* x */
        w = x[n] - static_cast<double>(EvaluateIndex[n][2]);
        w2 = w * w;
        weights[n][5] = (1.0 / 120.0) * w * w2 * w2;
        w2 -= w;
        w4 = w2 * w2;
        w -= 0.5;
        t = w2 * (w2 - 3.0);
        weights[n][0] = (1.0 / 24.0) * (1.0 / 5.0 + w2 + w4) - weights[n][5];
        t0 = (1.0 / 24.0) * (w2 * (w2 - 5.0) + 46.0 / 5.0);
        t1 = (-1.0 / 12.0) * w * (t + 4.0);
        weights[n][2] = t0 + t1;
        weights[n][3] = t0 - t1;
        t0 = (1.0 / 16.0) * (9.0 / 5.0 - t);
        t1 = (1.0 / 24.0) * w * (w4 - w2 - 5.0);
        weights[n][1] = t0 + t1;
        weights[n][4] = t0 - t1;
      }
      break;
    }
    default:
    {
      // SplineOrder not implemented yet.
      ExceptionObject err(__FILE__, __LINE__);
      err.SetLocation(ITK_LOCATION);
      err.SetDescription("SplineOrder must be between 0 and 5. Requested spline order has not been implemented yet.");
      throw err;
      break;
    }
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::SetDerivativeWeights(
  const ContinuousIndexType & x,
  const vnl_matrix<long> &    EvaluateIndex,
  vnl_matrix<double> &        weights,
  unsigned int                splineOrder) const
{
  // For speed improvements we could make each case a separate function and use
  // function pointers to reference the correct weight order.
  // Another possibility would be to loop inside the case statement (reducing
  // the number
  // of switch statement executions to one per routine call.
  // Left as is for now for readability.
  double    w;
  double    w1;
  double    w2;
  double    w3;
  double    w4;
  double    w5;
  double    t;
  double    t0;
  double    t1;
  double    t2;
  int const derivativeSplineOrder = static_cast<int>(splineOrder) - 1;

  switch (derivativeSplineOrder)
  {
    // Calculates B(splineOrder) ( (x + 1/2) - xi) -
    //            B(splineOrder -1)( (x - 1/2) - xi)
    case -1:
    {
      // Why would we want to do this?
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        weights[n][0] = 0.0;
      }
      break;
    }
    case 0:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        weights[n][0] = -1.0;
        weights[n][1] = 1.0;
      }
      break;
    }
    case 1:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] + 0.5 - static_cast<double>(EvaluateIndex[n][1]);
        // w2 = w;
        w1 = 1.0 - w;

        weights[n][0] = 0.0 - w1;
        weights[n][1] = w1 - w;
        weights[n][2] = w;
      }
      break;
    }
    case 2:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] + .5 - static_cast<double>(EvaluateIndex[n][2]);
        w2 = 0.75 - w * w;
        w3 = 0.5 * (w - w2 + 1.0);
        w1 = 1.0 - w2 - w3;

        weights[n][0] = 0.0 - w1;
        weights[n][1] = w1 - w2;
        weights[n][2] = w2 - w3;
        weights[n][3] = w3;
      }
      break;
    }
    case 3:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] + 0.5 - static_cast<double>(EvaluateIndex[n][2]);
        w4 = (1.0 / 6.0) * w * w * w;
        w1 = (1.0 / 6.0) + 0.5 * w * (w - 1.0) - w4;
        w3 = w + w1 - 2.0 * w4;
        w2 = 1.0 - w1 - w3 - w4;

        weights[n][0] = 0.0 - w1;
        weights[n][1] = w1 - w2;
        weights[n][2] = w2 - w3;
        weights[n][3] = w3 - w4;
        weights[n][4] = w4;
      }
      break;
    }
    case 4:
    {
      for (unsigned int n = 0; n < ImageDimension; ++n)
      {
        w = x[n] + .5 - static_cast<double>(EvaluateIndex[n][3]);
        t2 = w * w;
        t = (1.0 / 6.0) * t2;
        w1 = 0.5 - w;
        w1 *= w1;
        w1 *= (1.0 / 24.0) * w1;
        t0 = w * (t - 11.0 / 24.0);
        t1 = 19.0 / 96.0 + t2 * (0.25 - t);
        w2 = t1 + t0;
        w4 = t1 - t0;
        w5 = w1 + t0 + 0.5 * w;
        w3 = 1.0 - w1 - w2 - w4 - w5;

        weights[n][0] = 0.0 - w1;
        weights[n][1] = w1 - w2;
        weights[n][2] = w2 - w3;
        weights[n][3] = w3 - w4;
        weights[n][4] = w4 - w5;
        weights[n][5] = w5;
      }
      break;
    }
    default:
    {
      // SplineOrder not implemented yet.
      ExceptionObject err(__FILE__, __LINE__);
      err.SetLocation(ITK_LOCATION);
      err.SetDescription(
        "SplineOrder (for derivatives) must be between 1 and 5. Requested spline order has not been implemented yet.");
      throw err;
      break;
    }
  }
}

// Generates m_PointsToIndex;
template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::GeneratePointsToIndex()
{
  // m_PointsToIndex is used to convert a sequential location to an N-dimension
  // index vector.  This is precomputed to save time during the interpolation
  // routine.
  m_ThreadedEvaluateIndex = std::make_unique<vnl_matrix<long>[]>(m_NumberOfWorkUnits);
  m_ThreadedWeights = std::make_unique<vnl_matrix<double>[]>(m_NumberOfWorkUnits);
  m_ThreadedWeightsDerivative = std::make_unique<vnl_matrix<double>[]>(m_NumberOfWorkUnits);
  for (unsigned int i = 0; i < m_NumberOfWorkUnits; ++i)
  {
    m_ThreadedEvaluateIndex[i].set_size(ImageDimension, m_SplineOrder + 1);
    m_ThreadedWeights[i].set_size(ImageDimension, m_SplineOrder + 1);
    m_ThreadedWeightsDerivative[i].set_size(ImageDimension, m_SplineOrder + 1);
  }

  m_PointsToIndex.resize(m_MaxNumberInterpolationPoints);
  for (unsigned int p = 0; p < m_MaxNumberInterpolationPoints; ++p)
  {
    int           pp = p;
    unsigned long indexFactor[ImageDimension];
    indexFactor[0] = 1;
    for (int j = 1; j < static_cast<int>(ImageDimension); ++j)
    {
      indexFactor[j] = indexFactor[j - 1] * (m_SplineOrder + 1);
    }
    for (int j = (static_cast<int>(ImageDimension) - 1); j >= 0; j--)
    {
      m_PointsToIndex[p][j] = pp / indexFactor[j];
      pp = pp % indexFactor[j];
    }
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::DetermineRegionOfSupport(
  vnl_matrix<long> &          evaluateIndex,
  const ContinuousIndexType & x,
  unsigned int                splineOrder) const
{
  const float halfOffset = splineOrder & 1 ? 0.0 : 0.5;
  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    long indx = static_cast<long>(std::floor(static_cast<float>(x[n]) + halfOffset)) - splineOrder / 2;
    for (unsigned int k = 0; k <= splineOrder; ++k)
    {
      evaluateIndex[n][k] = indx++;
    }
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::ApplyMirrorBoundaryConditions(
  vnl_matrix<long> & evaluateIndex,
  unsigned int       splineOrder) const
{
  const IndexType startIndex = this->GetStartIndex();
  const IndexType endIndex = this->GetEndIndex();

  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    // apply the mirror boundary conditions
    // TODO:  We could implement other boundary options beside mirror
    if (m_DataLength[n] == 1)
    {
      for (unsigned int k = 0; k <= splineOrder; ++k)
      {
        evaluateIndex[n][k] = 0;
      }
    }
    else
    {
      for (unsigned int k = 0; k <= splineOrder; ++k)
      {
        if (evaluateIndex[n][k] < startIndex[n])
        {
          evaluateIndex[n][k] = startIndex[n] + (startIndex[n] - evaluateIndex[n][k]);
        }
        if (evaluateIndex[n][k] >= endIndex[n])
        {
          evaluateIndex[n][k] = endIndex[n] - (evaluateIndex[n][k] - endIndex[n]);
        }
      }
    }
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
auto
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::EvaluateAtContinuousIndexInternal(
  const ContinuousIndexType & x,
  vnl_matrix<long> &          evaluateIndex,
  vnl_matrix<double> &        weights) const -> OutputType
{
  // compute the interpolation indexes
  this->DetermineRegionOfSupport((evaluateIndex), x, m_SplineOrder);

  // Determine weights
  SetInterpolationWeights(x, (evaluateIndex), (weights), m_SplineOrder);

  // Modify evaluateIndex at the boundaries using mirror boundary conditions
  this->ApplyMirrorBoundaryConditions((evaluateIndex), m_SplineOrder);

  // perform interpolation
  double    interpolated = 0.0;
  IndexType coefficientIndex;
  // Step through each point in the n-dimensional interpolation cube.
  for (unsigned int p = 0; p < m_MaxNumberInterpolationPoints; ++p)
  {
    double w = 1.0;
    for (unsigned int n = 0; n < ImageDimension; ++n)
    {
      unsigned int const indx = m_PointsToIndex[p][n];
      w *= (weights)[n][indx];
      coefficientIndex[n] = (evaluateIndex)[n][indx];
    }
    interpolated += w * m_Coefficients->GetPixel(coefficientIndex);
  }

  return (interpolated);
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
void
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::
  EvaluateValueAndDerivativeAtContinuousIndexInternal(const ContinuousIndexType & x,
                                                      OutputType &                value,
                                                      CovariantVectorType &       derivativeValue,
                                                      vnl_matrix<long> &          evaluateIndex,
                                                      vnl_matrix<double> &        weights,
                                                      vnl_matrix<double> &        weightsDerivative) const
{
  this->DetermineRegionOfSupport((evaluateIndex), x, m_SplineOrder);

  SetInterpolationWeights(x, (evaluateIndex), (weights), m_SplineOrder);

  SetDerivativeWeights(x, (evaluateIndex), (weightsDerivative), m_SplineOrder);

  // Modify EvaluateIndex at the boundaries using mirror boundary conditions
  this->ApplyMirrorBoundaryConditions((evaluateIndex), m_SplineOrder);

  unsigned int indx;
  double       tmpV;
  double       w;
  double       w1;
  double       tmpW;
  IndexType    coefficientIndex;
  value = 0.0;
  unsigned int p;
  unsigned int n;
  unsigned int n1;
  derivativeValue[0] = 0.0;
  for (p = 0; p < m_MaxNumberInterpolationPoints; ++p)
  {
    indx = m_PointsToIndex[p][0];
    coefficientIndex[0] = (evaluateIndex)[0][indx];
    w = (weights)[0][indx];
    w1 = (weightsDerivative)[0][indx];
    for (n = 1; n < ImageDimension; ++n)
    {
      indx = m_PointsToIndex[p][n];
      coefficientIndex[n] = (evaluateIndex)[n][indx];
      tmpW = (weights)[n][indx];
      w *= tmpW;
      w1 *= tmpW;
    }
    tmpV = m_Coefficients->GetPixel(coefficientIndex);
    value += w * tmpV;
    derivativeValue[0] += w1 * tmpV;
  }
  derivativeValue[0] /= this->GetInputImage()->GetSpacing()[0];
  for (n = 1; n < ImageDimension; ++n)
  {
    derivativeValue[n] = 0.0;
    for (p = 0; p < m_MaxNumberInterpolationPoints; ++p)
    {
      w1 = 1.0;
      for (n1 = 0; n1 < ImageDimension; ++n1)
      {
        indx = m_PointsToIndex[p][n1];
        coefficientIndex[n1] = (evaluateIndex)[n1][indx];

        if (n1 == n)
        {
          w1 *= (weightsDerivative)[n1][indx];
        }
        else
        {
          w1 *= (weights)[n1][indx];
        }
      }
      derivativeValue[n] += m_Coefficients->GetPixel(coefficientIndex) * w1;
    }
    // take spacing into account
    derivativeValue[n] /= this->GetInputImage()->GetSpacing()[n];
  }

  if (this->m_UseImageDirection)
  {
    derivativeValue = this->GetInputImage()->TransformLocalVectorToPhysicalVector(derivativeValue);
  }
}

template <typename TImageType, typename TCoordRep, typename TCoefficientType>
auto
BSplineInterpolateImageFunction<TImageType, TCoordRep, TCoefficientType>::EvaluateDerivativeAtContinuousIndexInternal(
  const ContinuousIndexType & x,
  vnl_matrix<long> &          evaluateIndex,
  vnl_matrix<double> &        weights,
  vnl_matrix<double> &        weightsDerivative) const -> CovariantVectorType
{
  this->DetermineRegionOfSupport((evaluateIndex), x, m_SplineOrder);

  SetInterpolationWeights(x, (evaluateIndex), (weights), m_SplineOrder);

  SetDerivativeWeights(x, (evaluateIndex), (weightsDerivative), m_SplineOrder);

  // Modify EvaluateIndex at the boundaries using mirror boundary conditions
  this->ApplyMirrorBoundaryConditions((evaluateIndex), m_SplineOrder);

  const InputImageType *                       inputImage = this->GetInputImage();
  const typename InputImageType::SpacingType & spacing = inputImage->GetSpacing();

  // Calculate derivative
  CovariantVectorType derivativeValue;
  double              tempValue;
  IndexType           coefficientIndex;
  for (unsigned int n = 0; n < ImageDimension; ++n)
  {
    derivativeValue[n] = 0.0;
    for (unsigned int p = 0; p < m_MaxNumberInterpolationPoints; ++p)
    {
      tempValue = 1.0;
      for (unsigned int n1 = 0; n1 < ImageDimension; ++n1)
      {
        unsigned int const indx = m_PointsToIndex[p][n1];
        coefficientIndex[n1] = (evaluateIndex)[n1][indx];

        if (n1 == n)
        {
          tempValue *= (weightsDerivative)[n1][indx];
        }
        else
        {
          tempValue *= (weights)[n1][indx];
        }
      }
      derivativeValue[n] += m_Coefficients->GetPixel(coefficientIndex) * tempValue;
    }
    derivativeValue[n] /= spacing[n];
  }

  if (this->m_UseImageDirection)
  {
    return inputImage->TransformLocalVectorToPhysicalVector(derivativeValue);
  }

  return (derivativeValue);
}
} // namespace itk

#endif
