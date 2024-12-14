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

#include "itkShiSparseLevelSetImage.h"
#include "itkTestingMacros.h"

int
itkShiSparseLevelSetImageTest(int, char *[])
{
  constexpr unsigned int Dimension = 2;
  using SparseLevelSetType = itk::ShiSparseLevelSetImage<Dimension>;

  using LabelMapType = SparseLevelSetType::LabelMapType;
  using IndexType = LabelMapType::IndexType;

  auto index = IndexType::Filled(3);

  auto labelMap = LabelMapType::New();
  labelMap->SetBackgroundValue(3);

  for (int i = 0; i < 4; ++i)
  {
    ++index[1];
    labelMap->SetPixel(index, -3);
  }

  index[1] = 2;
  labelMap->SetPixel(index, -1);

  index[1] = 1;
  labelMap->SetPixel(index, 1);

  index[1] = 7;
  labelMap->SetPixel(index, -1);

  index[1] = 8;
  labelMap->SetPixel(index, 1);

  auto phi = SparseLevelSetType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(phi, ShiSparseLevelSetImage, LevelSetSparseImage);


  phi->SetLabelMap(labelMap);

  index[0] = 3;
  index[1] = 3;
  if (phi->Evaluate(index) != 3)
  {
    std::cout << index << ' ' << phi->Evaluate(index) << " != 3" << '\n';
    return EXIT_FAILURE;
  }

  index[0] = 3;
  index[1] = 4;
  if (phi->Evaluate(index) != -3)
  {
    std::cout << index << ' ' << phi->Evaluate(index) << " != -3" << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
