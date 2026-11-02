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
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkGTest.h"

TEST(LabelMap, ConvertedLegacyTest2)
{
  constexpr unsigned int dim{ 3 };

  using LabelObjectType = itk::LabelObject<unsigned long, dim>;
  using IndexType = LabelObjectType::IndexType;
  using LabelMapType = itk::LabelMap<LabelObjectType>;
  using RegionType = LabelMapType::RegionType;
  using SizeType = LabelMapType::SizeType;

  auto map = LabelMapType::New();

  SizeType sizeIn{ 10, 20, 30 };
  map->SetRegions(sizeIn);
  map->Allocate();

  RegionType regionIn;
  regionIn.SetSize(sizeIn);

  RegionType regionOut = map->GetRequestedRegion();
  map->Initialize();

  IndexType index{ 1, 3, 5 };

  sizeIn[0] = 100;
  sizeIn[1] = 200;
  sizeIn[2] = 300;

  regionIn = { index, sizeIn };
  map->SetRegions(regionIn);
  map->Allocate();

  regionOut = map->GetRequestedRegion();

  map->SetBackgroundValue(255);

  auto lo = LabelObjectType::New();
  lo->SetLabel(1);

  IndexType idx;
  idx[0] = 1;
  idx[1] = 20;
  idx[2] = 30;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 0;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 0;
  idx[2] = 1;
  lo->AddLine(idx, 10);

  idx[0] = 5;
  idx[1] = 1;
  idx[2] = 0;
  lo->AddLine(idx, 10);

  idx[0] = 0;
  idx[1] = 1;
  idx[2] = 1;
  lo->AddLine(idx, 10);

  idx[0] = 10;
  idx[1] = 1;
  idx[2] = 1;
  lo->AddLine(idx, 1);

  map->AddLabelObject(lo);

  auto lo2 = LabelObjectType::New();

  idx[0] = 1;
  idx[1] = 21;
  idx[2] = 30;
  lo2->AddLine(idx, 10);

  map->PushLabelObject(lo2);

  map->SetPixel(idx, 255);
  EXPECT_EQ(map->GetPixel(idx), 255u) << "SetPixel( idx, 255 ) - Failed 1";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 255 ) - Failed 1";

  idx[0] = 11;
  idx[1] = 21;
  idx[2] = 30;
  map->SetPixel(idx, 255);
  EXPECT_EQ(map->GetPixel(idx), 255u) << "SetPixel( idx, 255 ) - Failed 2";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 255 ) - Failed 2";

  idx[0] = 10;
  idx[1] = 21;
  idx[2] = 30;
  map->SetPixel(idx, 255);
  EXPECT_EQ(map->GetPixel(idx), 255u) << "SetPixel( idx, 255 ) - Failed 3";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 255 ) - Failed 3";

  idx[0] = 5;
  idx[1] = 21;
  idx[2] = 30;
  map->SetPixel(idx, 1);
  EXPECT_EQ(map->GetPixel(idx), 1u) << "SetPixel( idx, 1 ) failed";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 1 ) failed";

  map->SetPixel(idx, 255);
  EXPECT_EQ(map->GetPixel(idx), 255u) << "SetPixel( idx, 255 ) - Failed 4";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 1 ) - Failed 4";

  map->SetPixel(idx, 255);
  EXPECT_EQ(map->GetPixel(idx), 255u) << "SetPixel( idx, 255 ) - Failed 5";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 1 ) - Failed 5";

  map->SetPixel(idx, 3);
  EXPECT_EQ(map->GetPixel(idx), 3u) << "SetPixel( idx, 3 ) failed";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 3u) << "SetPixel( idx, 1 ) failed";

  map->SetPixel(idx, 2);
  EXPECT_EQ(map->GetPixel(idx), 2u) << "SetPixel( idx, 2 ) failed";
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 2u) << "SetPixel( idx, 2 ) failed";

  idx[0] = 0;
  idx[1] = 21;
  idx[2] = 30;

  for (int k = 0; k < 15; k++, idx[0]++)
  {
    map->SetPixel(idx, 255);
  }

  EXPECT_EQ(map->GetNumberOfLabelObjects(), 1u) << "Remove Label Object 2";

  map->Optimize();

  map->ClearLabels();
}
