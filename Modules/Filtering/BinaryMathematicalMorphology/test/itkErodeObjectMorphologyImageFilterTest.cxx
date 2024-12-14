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

#include "itkErodeObjectMorphologyImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkSimpleFilterWatcher.h"
#include "itkTestingMacros.h"

int
itkErodeObjectMorphologyImageFilterTest(int, char *[])
{

  // Define the dimension of the images
  constexpr unsigned int myDimension = 2;

  // Define the values of the input images
  constexpr unsigned short fgValue = 25;
  constexpr unsigned short bgValue = 0;
  constexpr unsigned short randomValue = 10;

  // Declare the types of the images
  using myImageType = itk::Image<unsigned short, myDimension>;

  // Declare the type of the index to access images
  using myIndexType = itk::Index<myDimension>;

  // Declare the type of the size
  using mySizeType = itk::Size<myDimension>;

  // Declare the type of the Region
  using myRegionType = itk::ImageRegion<myDimension>;

  // Create an image
  auto inputImage = myImageType::New();

  // Define their size, and start index
  mySizeType size;
  size[0] = 20;
  size[1] = 20;

  myIndexType start;
  start[0] = 0;
  start[1] = 0;

  const myRegionType region{ start, size };

  // Initialize Image
  inputImage->SetRegions(region);
  inputImage->Allocate();

  // Declare Iterator types apropriated for each image
  using myIteratorType = itk::ImageRegionIterator<myImageType>;

  // Create one iterator for image (this is a light object)
  myIteratorType it(inputImage, inputImage->GetBufferedRegion());

  // Initialize the content of Image
  std::cout << "Input image " << std::endl;
  inputImage->FillBuffer(bgValue);

  myImageType::IndexType ind;
  ind[0] = 10;
  ind[1] = 10;
  inputImage->SetPixel(ind, fgValue);

  ind[0] = 19;
  ind[1] = 19;
  inputImage->SetPixel(ind, fgValue);

  ind[0] = 0;
  ind[1] = 19;
  inputImage->SetPixel(ind, fgValue);

  ind[0] = 13;
  ind[1] = 13;
  inputImage->SetPixel(ind, randomValue);

  ind[0] = 12;
  ind[1] = 12;
  inputImage->SetPixel(ind, randomValue);

  ind[0] = 19;
  ind[1] = 18;
  inputImage->SetPixel(ind, randomValue);

  ind[0] = 0;
  ind[1] = 5;
  inputImage->SetPixel(ind, randomValue);

  unsigned int i = 0;
  it.GoToBegin();
  while (!it.IsAtEnd())
  {
    std::cout << it.Get() << "  ";
    ++it;

    if (++i % 20 == 0)
    {
      std::cout << std::endl;
    }
  }

  // Declare the type for the structuring element
  using myKernelType = itk::BinaryBallStructuringElement<unsigned short, myDimension>;

  // Declare the type for the morphology Filter
  using myFilterType = itk::ErodeObjectMorphologyImageFilter<myImageType, myImageType, myKernelType>;

  // Create the filter
  auto                           filter = myFilterType::New();
  const itk::SimpleFilterWatcher watcher(filter, "filter");

  // Create the structuring element
  myKernelType           ball;
  myKernelType::SizeType ballSize;
  ballSize[0] = 2;
  ballSize[1] = 4;
  ball.SetRadius(ballSize);
  ball.CreateStructuringElement();

  // Connect the input image
  filter->SetInput(inputImage);
  ITK_TEST_SET_GET_VALUE(inputImage, filter->GetInput());

  filter->SetKernel(ball);
  ITK_TEST_SET_GET_VALUE(ball, filter->GetKernel());

  filter->SetErodeValue(fgValue);
  ITK_TEST_SET_GET_VALUE(fgValue, filter->GetErodeValue());

  const unsigned short backgroundValue = 5;
  filter->SetBackgroundValue(backgroundValue);
  ITK_TEST_SET_GET_VALUE(backgroundValue, filter->GetBackgroundValue());

  std::cout << "BoundaryCondition: " << filter->GetBoundaryCondition() << std::endl;

  // Get the Smart Pointer to the Filter Output
  const myImageType::Pointer outputImage = filter->GetOutput();

  // Execute the filter
  ITK_TRY_EXPECT_NO_EXCEPTION(filter->Update());

  // Create an iterator for going through the image output
  myIteratorType it2(outputImage, outputImage->GetBufferedRegion());

  // Print the content of the result image
  std::cout << "Result " << std::endl;
  i = 0;
  while (!it2.IsAtEnd())
  {
    std::cout << it2.Get() << "  ";
    ++it2;

    if (++i % 20 == 0)
    {
      std::cout << std::endl;
    }
  }

  // All objects should be automatically destroyed at this point

  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
