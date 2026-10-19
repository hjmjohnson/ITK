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

#include "itkCastSpatialObjectFilter.h"
#include "itkGroupSpatialObject.h"
#include "itkTubeSpatialObject.h"
#include "itkMath.h"
#include "itkGTest.h"

TEST(CastSpatialObjectFilter, ConvertedLegacyTest)
{
  // Ellipse
  using EllipseType = itk::EllipseSpatialObject<3>;
  auto ellipse = EllipseType::New();
  ellipse->SetRadiusInObjectSpace(3);
  ellipse->GetProperty().SetColor(0, 1, 1);

  // Tube
  using TubeType = itk::TubeSpatialObject<3>;
  using TubePointType = itk::TubeSpatialObjectPoint<3>;
  TubeType::TubePointListType list3;
  for (unsigned int i = 0; i < 7; ++i)
  {
    TubePointType p;
    p.SetPositionInObjectSpace(i * 3, i * 3, i * 3);
    p.SetRadiusInObjectSpace(i);
    p.SetRed(i);
    p.SetGreen(i + 1);
    p.SetBlue(i + 2);
    p.SetAlpha(i + 3);
    list3.push_back(p);
  }
  auto tube = TubeType::New();
  tube->GetProperty().SetName("Tube 3");
  tube->SetId(3);
  tube->SetPoints(list3);

  // Group
  using GroupType = itk::GroupSpatialObject<3>;
  auto group = GroupType::New();
  group->AddChild(ellipse);
  ellipse->AddChild(tube);

  using CastType = itk::CastSpatialObjectFilter<3>;
  using TubeListType = std::list<TubeType::Pointer>;
  auto caster = CastType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(caster, CastSpatialObjectFilter, Object);


  caster->SetInput(group);
  EXPECT_EQ(group, caster->GetInput());

  std::unique_ptr<TubeListType> tList(caster->GetTubes());

  const TubeType::Pointer tListTube = tList->begin()->GetPointer();

  bool found = false;
  if (!strcmp(tListTube->GetTypeName().c_str(), "TubeSpatialObject"))
  {
    found = true;
    unsigned int value = 0;

    EXPECT_FALSE(tListTube->GetPoints().empty()) << " [FAILED] : Size of the point list is zero";

    for (auto pnt = tListTube->GetPoints().begin(); pnt != tListTube->GetPoints().end(); ++pnt)
    {
      for (unsigned int d = 0; d < 3; ++d)
      {
        EXPECT_DOUBLE_EQ(pnt->GetPositionInWorldSpace()[d], value * tListTube->GetId())
          << " [FAILED] (Position is: " << pnt->GetPositionInWorldSpace()[d]
          << " expected : " << value * tListTube->GetId() << " ) ";
      }
      value++;
    }
  }

  if (found)
  {
    std::cout << " [PASSED]" << std::endl;
  }
  else
  {
    ADD_FAILURE() << " [FAILED] : Cannot found TubeSpatialObject";
  }


  std::cout << "Test finished" << std::endl;
}
