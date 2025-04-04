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
#include "itkHessianRecursiveGaussianImageFilter.h"
#include "itkSimpleFilterWatcher.h"
#include "itkTestingMacros.h"

int
itkHessianRecursiveGaussianFilterTest(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " sigma normalizeAcrossScale" << std::endl;
    return EXIT_FAILURE;
  }

  // Define the dimension of the images
  constexpr unsigned int myDimension = 3;

  // Declare the types of the images
  using myImageType = itk::Image<float, myDimension>;

  // Declare the type of the index to access images
  using myIndexType = itk::Index<myDimension>;

  // Declare the type of the size
  using mySizeType = itk::Size<myDimension>;

  // Declare the type of the Region
  using myRegionType = itk::ImageRegion<myDimension>;

  // Create the image
  auto inputImage = myImageType::New();


  // Define their size, and start index
  mySizeType size;
  size[0] = 8;
  size[1] = 8;
  size[2] = 8;

  myIndexType start{};

  myRegionType region{ start, size };

  // Initialize Image A
  inputImage->SetRegions(region);
  inputImage->Allocate();

  // Declare Iterator type for the input image
  using myIteratorType = itk::ImageRegionIteratorWithIndex<myImageType>;

  // Create one iterator for the Input Image A (this is a light object)
  myIteratorType it(inputImage, inputImage->GetRequestedRegion());

  // Initialize the content of Image A
  while (!it.IsAtEnd())
  {
    it.Set(0.0);
    ++it;
  }

  size[0] = 4;
  size[1] = 4;
  size[2] = 4;

  start[0] = 2;
  start[1] = 2;
  start[2] = 2;

  // Create one iterator for an internal region
  region.SetSize(size);
  region.SetIndex(start);
  myIteratorType itb(inputImage, region);

  // Initialize the content the internal region
  while (!itb.IsAtEnd())
  {
    itb.Set(100.0);
    ++itb;
  }

  // Declare the type for the
  using myFilterType = itk::HessianRecursiveGaussianImageFilter<myImageType>;

  using myHessianImageType = myFilterType::OutputImageType;


  // Create a  Filter
  auto filter = myFilterType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(filter, HessianRecursiveGaussianImageFilter, ImageToImageFilter);


  auto sigma = static_cast<typename myFilterType::RealType>(std::stod(argv[1]));
  filter->SetSigma(sigma);
  ITK_TEST_SET_GET_VALUE(sigma, filter->GetSigma());

  auto normalizeAcrossScale = static_cast<bool>(std::stoi(argv[2]));
  ITK_TEST_SET_GET_BOOLEAN(filter, NormalizeAcrossScale, normalizeAcrossScale);

  // Connect the input images
  filter->SetInput(inputImage);

  // Execute the filter
  filter->Update();

  // Get the Smart Pointer to the Filter Output
  // It is important to do it AFTER the filter is Updated
  // Because the object connected to the output may be changed
  // by another during GenerateData() call
  const myHessianImageType::Pointer outputImage = filter->GetOutput();

  // Declare Iterator type for the output image
  using myOutputIteratorType = itk::ImageRegionIteratorWithIndex<myHessianImageType>;

  // Create an iterator for going through the output image
  myOutputIteratorType itg(outputImage, outputImage->GetRequestedRegion());

  // Print the content of the result image
  std::cout << " Result " << std::endl;
  itg.GoToBegin();
  while (!itg.IsAtEnd())
  {
    std::cout << itg.Get();
    ++itg;
  }

  // Test for warnings in 2D
  using my2DImageType = itk::Image<float, 2>;
  using my2DFilterType = itk::HessianRecursiveGaussianImageFilter<my2DImageType>;
  auto test = my2DFilterType::New();
  if (test.IsNull())
  {
    return EXIT_FAILURE;
  }

  // All objects should be automatically destroyed at this point
  return EXIT_SUCCESS;
}
