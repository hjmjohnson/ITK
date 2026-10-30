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

#include "itkMeshRegion.h"
#include "itkGTest.h"


TEST(MeshRegion, ConvertedLegacyTest)
{

  itk::MeshRegion meshRegion{};

  auto * const meshRegionPointer = &meshRegion;
  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(meshRegionPointer, MeshRegion, Region);


  EXPECT_EQ(itk::MeshRegion::Superclass::RegionEnum::ITK_UNSTRUCTURED_REGION, meshRegion.GetRegionType());

  constexpr itk::SizeValueType numRegions{ 10 };
  meshRegion.SetNumberOfRegions(numRegions);
  EXPECT_EQ(numRegions, meshRegion.GetNumberOfRegions());

  constexpr itk::SizeValueType idx{ 1 };
  meshRegion.SetRegion(idx);
  EXPECT_EQ(idx, meshRegion.GetRegion());


  std::cout << "Test finished." << std::endl;
}
