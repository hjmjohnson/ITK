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

TEST(LabelMap, ConvertedLegacyTest)
{
  constexpr unsigned int dim{ 3 };

  using LabelObjectType = itk::LabelObject<unsigned long, dim>;
  using IndexType = LabelObjectType::IndexType;
  using LabelMapType = itk::LabelMap<LabelObjectType>;
  using RegionType = LabelMapType::RegionType;
  using SizeType = LabelMapType::SizeType;
  using LabelObjectVectorType = LabelMapType::LabelObjectVectorType;
  using LabelVectorType = LabelMapType::LabelVectorType;

  auto map = LabelMapType::New();

  SizeType sizeIn{ 10, 20, 30 };
  map->SetRegions(sizeIn);
  map->Allocate();

  RegionType regionIn;
  regionIn.SetSize(sizeIn);

  RegionType regionOut = map->GetRequestedRegion();
  EXPECT_EQ(regionOut, regionIn) << "SetRegions (size) failed";
  map->Initialize();

  constexpr IndexType index{ 1, 2, 3 };

  sizeIn[0] = 100;
  sizeIn[1] = 200;
  sizeIn[2] = 300;

  regionIn = { index, sizeIn };
  map->SetRegions(regionIn);
  map->Allocate();

  regionOut = map->GetRequestedRegion();
  EXPECT_EQ(regionOut, regionIn) << "SetRegions (region) failed";

  auto mapGraft = LabelMapType::New();
  mapGraft->Graft(map);
  regionOut = mapGraft->GetRequestedRegion();
  EXPECT_EQ(regionOut, regionIn) << "Graft failed";

  mapGraft->SetBackgroundValue(255);
  EXPECT_EQ(mapGraft->GetBackgroundValue(), 255u) << "Set/GetBackground failed.";

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

  LabelObjectType::Pointer loCheck;

  map->AddLabelObject(lo);
  loCheck = map->GetLabelObject(idx);
  EXPECT_EQ(loCheck, lo) << "Add/GetLabelObject failed";

  const LabelObjectVectorType loVector = map->GetLabelObjects();
  EXPECT_EQ(loVector[0], lo) << "GetLabelObjects failed";

  const LabelVectorType loLabels = map->GetLabels();
  EXPECT_EQ(loLabels[0], 1u) << "GetLabels failed";

  auto lo2 = LabelObjectType::New();

  idx[0] = 1;
  idx[1] = 21;
  idx[2] = 30;
  lo2->AddLine(idx, 10);


  map->PushLabelObject(lo2);
  loCheck = map->GetLabelObject(idx);
  EXPECT_EQ(loCheck, lo2) << "Push/GetLabelObject failed";

  idx[0] = 1;
  idx[1] = 21;
  idx[2] = 31;
  map->SetPixel(idx, 3);

  idx[0] = 1;
  idx[1] = 21;
  idx[2] = 32;
  map->SetLine(idx, 11, 3);

  idx[0] = 2;
  idx[1] = 21;
  idx[2] = 32;
  EXPECT_EQ(map->GetPixel(idx), 3u) << "SetPixel/SetLine/GetPixel failed";

  EXPECT_EQ(map->GetNumberOfLabelObjects(), 3u) << "GetNumberOfLabelObjects failed";
  EXPECT_TRUE(map->HasLabel(1)) << "HasLabel failed";

  loCheck = map->GetNthLabelObject(1);
  EXPECT_EQ(loCheck, lo2) << "GetNthLabelObject failed";

  EXPECT_EQ(map->GetPixel(idx), 3u) << "SetPixel/SetLine/GetPixel failed";

  map->Print(std::cout);

  map->PrintLabelObjects();

  map->Optimize();

  map->RemoveLabelObject(lo);
  map->RemoveLabel(2);
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 1u) << "Remove LabelObject/Label failed";
  map->ClearLabels();
  EXPECT_EQ(map->GetNumberOfLabelObjects(), 0u) << "ClearLabels failed";
}
