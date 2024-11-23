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

#include "itkImageRegionIteratorWithIndex.h"
#include "itkImageToParametricSpaceFilter.h"
#include "itkMesh.h"
#include "itkMath.h"
#include "itkTestingMacros.h"

int
itkImageToParametricSpaceFilterTest(int, char *[])
{

  using ImagePixelType = float;

  // Declare the type for the images
  using ImageType = itk::Image<ImagePixelType, 2>;
  using ImagePointer = ImageType::Pointer;

  // Make the Mesh PointData type be an Image Index.
  using MeshPixelType = itk::Point<float, 2>;

  // Declare the types of the Mesh
  using MeshType = itk::Mesh<MeshPixelType>;

  // Declare the type for PointsContainerPointer
  using PointsContainerPointer = MeshType::PointsContainerPointer;
  // Declare the type for Points
  using PointType = MeshType::PointType;

  // Create an input Mesh
  auto inputMesh = MeshType::New();

  // Insert data on the Mesh
  PointsContainerPointer const points = inputMesh->GetPoints();


  // Declare the type for the images
  using ImageIteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  // Declare the type for the filter
  using FilterType = itk::ImageToParametricSpaceFilter<ImageType, MeshType>;

  using FilterPointer = FilterType::Pointer;


  ImagePointer const imageX = ImageType::New();
  ImagePointer const imageY = ImageType::New();
  ImagePointer const imageZ = ImageType::New();

  ImageType::SizeType        size;
  ImageType::IndexType const start{};
  size[0] = 10;
  size[1] = 10;

  ImageType::RegionType const region{ start, size };

  imageX->SetRegions(region);
  imageY->SetRegions(region);
  imageZ->SetRegions(region);

  imageX->Allocate();
  imageY->Allocate();
  imageZ->Allocate();

  ImageIteratorType ix(imageX, region);
  ImageIteratorType iy(imageY, region);
  ImageIteratorType iz(imageZ, region);

  ix.GoToBegin();
  iy.GoToBegin();
  iz.GoToBegin();


  while (!ix.IsAtEnd())
  {
    ix.Set(rand());
    ++ix;
  }

  while (!iy.IsAtEnd())
  {
    iy.Set(rand());
    ++iy;
  }

  while (!iz.IsAtEnd())
  {
    iz.Set(rand());
    ++iz;
  }


  FilterPointer const filter = FilterType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(filter, ImageToParametricSpaceFilter, ImageToMeshFilter);


  bool const computeIndices = true;
  ITK_TEST_SET_GET_BOOLEAN(filter, ComputeIndices, computeIndices);

  // Connect the inputs
  filter->SetInput(0, imageX);
  filter->SetInput(1, imageY);
  filter->SetInput(2, imageZ);

  // Execute the filter
  filter->Update();

  // Get the Smart Pointer to the Filter Output
  MeshType::Pointer const outputMesh = filter->GetOutput();

  // Get the point container
  MeshType::PointsContainer::Iterator const beginPoint = outputMesh->GetPoints()->Begin();

  MeshType::PointsContainer::Iterator const endPoint = outputMesh->GetPoints()->End();

  MeshType::PointsContainer::Iterator pointIt = beginPoint;

  bool ok = true;

  ix.GoToBegin();
  iy.GoToBegin();
  iz.GoToBegin();

  while (pointIt != endPoint)
  {
    PointType point = pointIt.Value();
    if (itk::Math::NotExactlyEquals(point[0], ix.Value()))
    {
      ok = false;
      break;
    }
    if (itk::Math::NotExactlyEquals(point[1], iy.Value()))
    {
      ok = false;
      break;
    }
    if (itk::Math::NotExactlyEquals(point[2], iz.Value()))
    {
      ok = false;
      break;
    }

    ++pointIt;
    ++ix;
    ++iy;
    ++iz;
  }

  // All objects should be automatically destroyed at this point

  if (!ok)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
