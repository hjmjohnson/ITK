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

#include <iostream>
#include "itkVectorLinearInterpolateImageFunction.h"
#include "itkImageRegionIteratorWithIndex.h"

enum
{
  VectorDimension = 3
};
enum
{
  ImageDimension = 3
};
using PixelType = itk::Vector<unsigned short, VectorDimension>;
using ImageType = itk::Image<PixelType, ImageDimension>;
using CoordinateType = itk::SpacePrecisionType;
using InterpolatorType = itk::VectorLinearInterpolateImageFunction<ImageType, CoordinateType>;
using IndexType = InterpolatorType::IndexType;
using PointType = InterpolatorType::PointType;
using ContinuousIndexType = InterpolatorType::ContinuousIndexType;
using OutputType = InterpolatorType::OutputType;

/**
 * Test a geometric point. Returns true if test has passed,
 * returns false otherwise
 */
bool
TestGeometricPoint(const InterpolatorType * interp, const PointType & point, bool isInside, OutputType trueValue)
{

  std::cout << " Point: " << point;

  const bool bvalue = interp->IsInsideBuffer(point);
  std::cout << " Inside: " << bvalue;

  if (bvalue != isInside)
  {
    std::cout << "*** Error: inside should be " << isInside << std::endl;
    return false;
  }

  if (isInside)
  {
    OutputType value = interp->Evaluate(point);
    std::cout << " Value: ";
    {
      int k = 0;
      for (; k < VectorDimension - 1; ++k)
      {
        std::cout << value[k] << ", ";
      }
      std::cout << value[k] << std::endl;
    }
    {
      int k = 0;
      for (; k < VectorDimension; ++k)
      {
        if (itk::Math::abs(value[k] - trueValue[k]) > 1e-9)
        {
          break;
        }
      }

      if (k != VectorDimension)
      {
        std::cout << " *** Error: Value should be: ";
        for (k = 0; k < VectorDimension - 1; ++k)
        {
          std::cout << trueValue[k] << ", ";
        }
        std::cout << trueValue[k] << std::endl;
        return false;
      }
    }
  }

  std::cout << std::endl;
  return true;
}


/**
 * Test a continuous index. Returns true if test has passed,
 * returns false otherwise
 */
bool
TestContinuousIndex(const InterpolatorType *    interp,
                    const ContinuousIndexType & index,
                    bool                        isInside,
                    OutputType                  trueValue)
{

  std::cout << " Index: " << index;

  const bool bvalue = interp->IsInsideBuffer(index);
  std::cout << " Inside: " << bvalue;

  if (bvalue != isInside)
  {
    std::cout << "*** Error: inside should be " << isInside << std::endl;
    return false;
  }

  if (isInside)
  {
    OutputType value = interp->EvaluateAtContinuousIndex(index);
    std::cout << " Value: ";
    {
      unsigned int k = 0;
      for (; k < VectorDimension - 1; ++k)
      {
        std::cout << value[k] << ", ";
      }
      std::cout << value[k] << std::endl;
    }

    {
      unsigned int k = 0;
      for (; k < VectorDimension; ++k)
      {
        if (itk::Math::abs(value[k] - trueValue[k]) > 1e-9)
        {
          break;
        }
      }

      if (k != VectorDimension)
      {
        std::cout << " *** Error: Value should be: ";
        for (k = 0; k < VectorDimension - 1; ++k)
        {
          std::cout << trueValue[k] << ", ";
        }
        std::cout << trueValue[k] << std::endl;
        return false;
      }
    }
  }

  std::cout << std::endl;
  return true;
}

int
itkVectorInterpolateImageFunctionTest(int, char *[])
{
  int flag = 0;

  std::cout << "Testing vector image interpolation: " << std::endl;

  constexpr ImageType::SizeType size = { { 20, 40, 80 } };
  constexpr double              origin[3] = { 0.5, 0.5, 0.5 };
  constexpr double              spacing[3] = { 0.1, 0.05, 0.025 };

  // Create a test image
  auto                  image = ImageType::New();
  ImageType::RegionType region;
  region.SetSize(size);

  image->SetLargestPossibleRegion(region);
  image->SetBufferedRegion(region);
  image->Allocate();

  image->SetOrigin(origin);
  image->SetSpacing(spacing);

  // Write in a simple linear pattern
  using Iterator = itk::ImageRegionIteratorWithIndex<ImageType>;

  for (Iterator iter(image, region); !iter.IsAtEnd(); ++iter)
  {
    IndexType      index = iter.GetIndex();
    unsigned short value = 0;

    for (int j = 0; j < ImageDimension; ++j)
    {
      value += index[j];
    }
    PixelType pixel;
    for (int k = 0; k < ImageDimension; ++k)
    {
      pixel[k] = (k + 1) * value;
    }

    iter.Set(pixel);
  }

  // Create the interpolator
  auto interp = InterpolatorType::New();
  interp->SetInputImage(image);
  interp->Print(std::cout);

  using GenericInterpolatorType = InterpolatorType::Superclass;
  std::cout << interp->GenericInterpolatorType::GetNameOfClass() << std::endl;
  std::cout << interp->GetNameOfClass() << std::endl;

  /* Test evaluation at continuous indices and corresponding
     geometric points */
  std::cout << "Evaluate at: " << std::endl;
  OutputType          output;
  ContinuousIndexType cindex;
  PointType           point;
  bool                passed = false;

  // an integer position inside the image
  {
    itk::SpacePrecisionType darray[3] = { 10, 20, 40 };
    double                  temp[3] = { 70, 140, 210 };
    output = OutputType(temp);
    cindex = ContinuousIndexType(darray);
    passed = TestContinuousIndex(interp, cindex, true, output);
  }

  if (!passed)
  {
    flag = 1;
  }

  image->TransformContinuousIndexToPhysicalPoint(cindex, point);
  passed = TestGeometricPoint(interp, point, true, output);

  if (!passed)
  {
    flag = 1;
  }
  IndexType index;
  index[0] = 10;
  index[1] = 20;
  index[2] = 40;
  if (interp->EvaluateAtIndex(index) != output)
  {
    std::cout << "Index: " << index;
    std::cout << "Value: " << interp->EvaluateAtIndex(index) << std::endl;
    std::cout << "Error: true value should be " << output << std::endl;
    flag = 1;
  }


  // position at the image border
  {
    itk::SpacePrecisionType darray[3] = { 0, 20, 40 };
    double                  temp[3] = { 60, 120, 180 };
    output = OutputType(temp);
    cindex = ContinuousIndexType(darray);
    passed = TestContinuousIndex(interp, cindex, true, output);
  }

  if (!passed)
  {
    flag = 1;
  }

  image->TransformContinuousIndexToPhysicalPoint(cindex, point);
  passed = TestGeometricPoint(interp, point, true, output);

  if (!passed)
  {
    flag = 1;
  }

  // position near image border
  {
    constexpr itk::SpacePrecisionType epsilon = 1.0e-10;
    constexpr itk::SpacePrecisionType darray[3] = { 19 - epsilon, 20, 40 };
    constexpr double                  temp[3] = { 79, 158, 237 };
    output = OutputType(temp);
    cindex = ContinuousIndexType(darray);
    passed = TestContinuousIndex(interp, cindex, true, output);
  }

  if (!passed)
  {
    flag = 1;
  }

  image->TransformContinuousIndexToPhysicalPoint(cindex, point);
  passed = TestGeometricPoint(interp, point, true, output);

  if (!passed)
  {
    flag = 1;
  }

  // position outside the image
  {
    constexpr itk::SpacePrecisionType darray[3] = { 20, 20, 40 };
    constexpr double                  temp[3] = { 1, 1, 1 };
    output = OutputType(temp);
    cindex = ContinuousIndexType(darray);
    passed = TestContinuousIndex(interp, cindex, false, output);
  }

  if (!passed)
  {
    flag = 1;
  }

  image->TransformContinuousIndexToPhysicalPoint(cindex, point);
  passed = TestGeometricPoint(interp, point, false, output);

  if (!passed)
  {
    flag = 1;
  }

  // at non-integer position
  {
    constexpr itk::SpacePrecisionType darray[3] = { 5.25, 12.5, 42.0 };
    constexpr double                  temp[3] = { 59.75, 119.5, 179.25 };
    output = OutputType(temp);
    cindex = ContinuousIndexType(darray);
    passed = TestContinuousIndex(interp, cindex, true, output);
  }

  if (!passed)
  {
    flag = 1;
  }

  image->TransformContinuousIndexToPhysicalPoint(cindex, point);
  passed = TestGeometricPoint(interp, point, true, output);

  if (!passed)
  {
    flag = 1;
  }


  // Return results of test
  if (flag != 0)
  {
    std::cout << "*** Some test failed" << std::endl;
    return flag;
  }

  std::cout << "All tests successfully passed" << std::endl;


  return EXIT_SUCCESS;
}
