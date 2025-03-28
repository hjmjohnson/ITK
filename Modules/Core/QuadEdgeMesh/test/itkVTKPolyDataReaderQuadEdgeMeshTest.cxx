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

#include "itkQuadEdgeMesh.h"
#include "itkVTKPolyDataReader.h"
#include "itkTestingMacros.h"

#include <iostream>

int
itkVTKPolyDataReaderQuadEdgeMeshTest(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " inputFilename" << std::endl;
    return EXIT_FAILURE;
  }

  using MeshType = itk::QuadEdgeMesh<float, 3>;
  using ReaderType = itk::VTKPolyDataReader<MeshType>;

  auto polyDataReader = ReaderType::New();

  using PointType = ReaderType::PointType;

  polyDataReader->SetFileName(argv[1]);

  try
  {
    polyDataReader->Update();
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Error during Update() " << std::endl;
    std::cerr << excp << std::endl;
  }

  std::cout << "polyDataReader:" << std::endl;
  std::cout << polyDataReader << std::endl;

  const MeshType::Pointer mesh = polyDataReader->GetOutput();

  std::cout << "Using following MeshType :";
  std::cout << mesh->GetNameOfClass() << std::endl;

  const PointType point{};


  std::cout << "Testing itk::VTKPolyDataReader" << std::endl;

  const unsigned int numberOfPoints = mesh->GetNumberOfPoints();
  const unsigned int numberOfCells = mesh->GetNumberOfCells();

  std::cout << "numberOfPoints= " << numberOfPoints << std::endl;
  std::cout << "numberOfCells= " << numberOfCells << std::endl;

  if (!numberOfPoints)
  {
    std::cerr << "ERROR: numberOfPoints= " << numberOfPoints << std::endl;
    return EXIT_FAILURE;
  }

  if (!numberOfCells)
  {
    std::cerr << "ERROR: numberOfCells= " << numberOfCells << std::endl;
    return EXIT_FAILURE;
  }

  for (unsigned int i = 0; i < numberOfPoints; ++i)
  {
    // mesh->GetPoint(i, &point);
    // std::cout << "Point[" << i << "]: " << point << std::endl;
  }

  std::cout << "Test passed" << std::endl;
  return EXIT_SUCCESS;
}
