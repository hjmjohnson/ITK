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
/*
 * itkDTITubeSpatialObject test file.
 * This test file test also the basic functions of the CompositeSpatialObject class,
 * like Add/RemoveChild(...), Get/SetChildren(...), etc...
 */

#include "itkGTest.h"
#include "itkDTITubeSpatialObject.h"
#include "itkGroupSpatialObject.h"


TEST(DTITubeSpatialObject, ConvertedLegacyTest)
{
  using ScalarType = double;
  using Vector = itk::Vector<ScalarType, 3>;
  using Point = itk::Point<ScalarType, 3>;
  using TubeType = itk::DTITubeSpatialObject<3>;
  using TubePointer = itk::SmartPointer<TubeType>;
  using GroupType = itk::GroupSpatialObject<3>;
  using GroupPointer = itk::SmartPointer<GroupType>;
  using TubePointType = TubeType::TubePointType;
  using TubePointListType = TubeType::TubePointListType;
  using ChildrenListType = std::list<itk::SpatialObject<3>::Pointer>;
  using ChildrenListPointer = ChildrenListType *;

  //======================================
  // testing of a single SpatialObject...
  //======================================

  std::cout << "==================================" << std::endl;
  std::cout << "Testing SpatialObject:" << std::endl << std::endl;

  const TubePointer tube1 = TubeType::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(tube1, DTITubeSpatialObject, TubeSpatialObject);


  tube1->GetProperty().SetName("Tube 1");
  tube1->SetId(1);

  TubePointListType list;

  auto offset = itk::MakeFilled<TubeType::TransformType::OffsetType>(10);
  tube1->GetModifiableObjectToParentTransform()->SetOffset(offset);

  for (unsigned int i = 0; i < 10; ++i)
  {
    TubePointType p;
    p.SetPositionInObjectSpace(i, i, i);
    p.SetRadiusInObjectSpace(1);
    list.push_back(p);
  }

  // For coverage
  TubePointType p;
  p.SetPositionInObjectSpace(1, 2, 3);
  p.SetRadiusInObjectSpace(1);
  p.Print(std::cout);

  tube1->SetPoints(list);
  tube1->Update();
  auto in = itk::MakeFilled<Point>(15);
  auto out = itk::MakeFilled<Point>(5);

  std::cout << "IsInside()...";
  EXPECT_TRUE(tube1->IsInsideInWorldSpace(in)) << "[FAILED]";
  EXPECT_FALSE(tube1->IsInsideInWorldSpace(out)) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  TubeType::CovariantVectorType derivative;

  std::cout << "DerivativeAt()...";
  ASSERT_NO_THROW(tube1->DerivativeAtInWorldSpace(in, 1, derivative)) << "[FAILED]";

  constexpr TubeType::CovariantVectorType expectedDerivative{};

  EXPECT_EQ(expectedDerivative, derivative) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;

  std::cout << "itkTubeSpatialObjectTest ";

  //==============================================
  // testing of a single CompositeSpatialObject...
  //==============================================

  std::cout << "==================================" << std::endl;
  std::cout << "Testing GroupSpatialObject:" << std::endl << std::endl;

  const TubePointer tube2 = TubeType::New();
  tube2->GetProperty().SetName("Tube 2");
  tube2->SetId(2);
  tube2->SetPoints(list);
  tube2->Update();

  const TubePointer tube3 = TubeType::New();
  tube3->GetProperty().SetName("Tube 3");
  tube3->SetId(3);
  tube3->SetPoints(list);
  tube3->Update();

  const GroupPointer tubeNet1 = GroupType::New();
  tubeNet1->GetProperty().SetName("tube network 1");


  tubeNet1->AddChild(tube1);
  tubeNet1->AddChild(tube2);
  tubeNet1->AddChild(tube3);
  tubeNet1->Update();

  // testing the AddChild() function...
  unsigned int nbChildren = tubeNet1->GetNumberOfChildren();

  std::cout << "AddChild()...";
  EXPECT_EQ(nbChildren, 3u) << "[FAILED] [" << nbChildren << "!= 3]";

  std::cout << "[PASSED]" << std::endl;


  // testing the RemoveChild() function...
  std::cout << "Removing 1" << std::endl;
  tubeNet1->RemoveChild(tube1);
  std::cout << "Removing 2" << std::endl;
  tubeNet1->RemoveChild(tube2);
  std::cout << "Removing 3" << std::endl;
  tubeNet1->RemoveChild(tube3);

  nbChildren = tubeNet1->GetNumberOfChildren();

  std::cout << "RemoveChild()...";
  EXPECT_EQ(nbChildren, 0u) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  tubeNet1->AddChild(tube1);
  tubeNet1->AddChild(tube2);
  tubeNet1->AddChild(tube3);

  ChildrenListType childrenList;
  // testing the GetChildren() function...
  childrenList.emplace_back(tube1);
  childrenList.emplace_back(tube2);
  childrenList.emplace_back(tube3);

  ChildrenListPointer returnedList = tubeNet1->GetChildren();
  bool                passed = true;
  if (childrenList.size() == returnedList->size())
  {
    auto itTest = returnedList->begin();
    auto it = childrenList.begin();
    auto end = childrenList.end();

    for (unsigned int i = 0; it != end; ++itTest, ++it, i++)
    {
      if (*itTest != *it)
      {
        passed = false;
        break;
      }
    }
  }
  else
  {
    passed = false;
  }

  std::cout << "GetChildren()...";
  EXPECT_TRUE(passed) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  tubeNet1->RemoveChild(tube1);
  tubeNet1->RemoveChild(tube2);
  tubeNet1->RemoveChild(tube3);

  delete returnedList;

  // testing the SetChildren() function...
  std::cout << "Set children ..." << std::endl;
  tubeNet1->SetChildren(childrenList);
  returnedList = tubeNet1->GetChildren();

  if (childrenList.size() == returnedList->size())
  {
    auto itTest = returnedList->begin();
    auto it = childrenList.begin();
    auto end = childrenList.end();

    passed = true;

    for (unsigned int i = 0; it != end; ++itTest, ++it, i++)
    {
      if (*itTest != *it)
      {
        passed = false;
        break;
      }
    }
  }
  else
  {
    passed = false;
  }

  delete returnedList;
  std::cout << "SetChildren()...";
  EXPECT_TRUE(passed) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  tubeNet1->Update();

  std::cout << "HasParent()...";
  EXPECT_TRUE(tube2->HasParent()) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  auto translation = itk::MakeFilled<Vector>(10);
  tubeNet1->GetModifiableObjectToParentTransform()->Translate(translation, false);
  tubeNet1->Update();

  Vector axis{};
  axis[1] = 1;
  double angle = itk::Math::pi_over_2;
  tube2->GetModifiableObjectToParentTransform()->Rotate3D(axis, angle);
  tube2->Update();

  angle = -itk::Math::pi_over_2;
  tube3->GetModifiableObjectToParentTransform()->Rotate3D(axis, angle);
  tube3->Update();

  in.Fill(25);
  out.Fill(15);

  auto p1 = itk::MakeFilled<Point>(15);
  p1[2] = 5;
  auto p2 = itk::MakeFilled<Point>(15);
  p2[0] = 5;

  std::cout << "IsInside()...";
  EXPECT_TRUE(tubeNet1->IsInsideInWorldSpace(in, 3)) << "[FAILED]";
  EXPECT_FALSE(tubeNet1->IsInsideInWorldSpace(out, 3)) << "[FAILED]";

  std::cout << "[PASSED]" << std::endl;


  std::cout << "DerivativeAt()...";
  try
  {
    tubeNet1->DerivativeAtInWorldSpace(in, static_cast<unsigned short>(1), derivative, true);
  }
  catch (...)
  {
    std::cout << "[FAILED]" << std::endl;
  }

  EXPECT_EQ(derivative, expectedDerivative) << "[FAILED]";
  if (derivative == expectedDerivative)
  {
    std::cout << "[PASSED]" << std::endl;
  }


  //====================================================
  // testing of references behavior for SpatialObject...
  //====================================================

  std::cout << "==============================================" << std::endl;
  std::cout << "Testing references behavior for SpatialObject:" << std::endl << std::endl;

  const TubePointer  tube = TubeType::New();
  const GroupPointer net = GroupType::New();


  unsigned int tubeCount = tube->GetReferenceCount();
  unsigned int netCount = net->GetReferenceCount();

  std::cout << "References test...";
  EXPECT_EQ(tubeCount, 1u) << "[FAILED]: Problem in Tube initialization of references count" << tubeCount;
  {
    const TubePointer localTube = tube;
    tubeCount = tube->GetReferenceCount();
    EXPECT_EQ(tubeCount, 2u) << "[FAILED]: Problem in Tube with incrementation of references count";
  }

  EXPECT_EQ(netCount, 1u) << "[FAILED]: Problem in TubeNetwork initialization of references count";
  {
    const GroupPointer localNet = net;
    netCount = net->GetReferenceCount();
    EXPECT_EQ(netCount, 2u) << "[FAILED]: Problem in TubeNetwork with incrementation of references count";
  }

  tubeCount = tube->GetReferenceCount();
  netCount = net->GetReferenceCount();

  EXPECT_EQ(tubeCount, 1u) << "[FAILED]: Problem in Tube with decrementation of references count";

  EXPECT_EQ(netCount, 1u) << "[FAILED]: Problem in TubeNetwork with decrementation of references count";

  std::cout << "[PASSED]" << std::endl;

  // Testing Set/GetParentPoint
  std::cout << "Set/GetParentPoint: ";

  tube->SetParentPoint(1);
  EXPECT_EQ(tube->GetParentPoint(), 1) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;


  // Testing ComputeTangentAndNormals();
  std::cout << "ComputeTangentAndNormals: ";
  tube1->ComputeTangentsAndNormals();

  TubePointType::VectorType t = static_cast<const TubePointType *>(tube1->GetPoint(1))->GetTangentInWorldSpace();
  TubePointType::CovariantVectorType n1 =
    static_cast<const TubePointType *>(tube1->GetPoint(1))->GetNormal1InWorldSpace();
  TubePointType::CovariantVectorType n2 =
    static_cast<const TubePointType *>(tube1->GetPoint(1))->GetNormal2InWorldSpace();


  const Point      t_known(itk::MakePoint(0.57735, 0.57735, 0.57735));
  const Point      n1_known(itk::MakePoint(0.707107, 0.707107, 0.0));
  const Point      n2_known(itk::MakePoint(0.408248, 0.408248, 0.816497));
  constexpr double tol{ 0.0001 };

  EXPECT_NEAR(t[0], t_known[0], tol) << "[FAILED]" << " t = " << t << " != " << t_known << " within " << tol;
  EXPECT_NEAR(t[1], t_known[1], tol) << "[FAILED]" << " t = " << t << " != " << t_known << " within " << tol;
  EXPECT_NEAR(t[2], t_known[2], tol) << "[FAILED]" << " t = " << t << " != " << t_known << " within " << tol;
  EXPECT_NEAR(n1[0], n1_known[0], tol) << "[FAILED]" << " n1 = " << n1 << " != " << n1_known << " within " << tol;
  EXPECT_NEAR(n1[1], -n1_known[1], tol) << "[FAILED]" << " n1 = " << n1 << " != " << n1_known << " within " << tol;
  EXPECT_NEAR(n1[2], n1_known[2], tol) << "[FAILED]" << " n1 = " << n1 << " != " << n1_known << " within " << tol;
  EXPECT_NEAR(n2[0], n2_known[0], tol) << "[FAILED]" << " n2 = " << n2 << " != " << n2_known << " within " << tol;
  EXPECT_NEAR(n2[1], n2_known[1], tol) << "[FAILED]" << " n2 = " << n2 << " != " << n2_known << " within " << tol;
  EXPECT_NEAR(n2[2], -n2_known[2], tol) << "[FAILED]" << " n2 = " << n2 << " != " << n2_known << " within " << tol;

  std::cout << "[PASSED]" << std::endl;

  // Testing IsInside() with m_EndType set to rounded end-type;
  std::cout << "IsInside() with m_RoundedEnd=True: ";
  p1.Fill(19.5);
  tube1->SetEndRounded(false);

  EXPECT_FALSE(tube1->IsInsideInWorldSpace(p1)) << "[FAILED]";

  tube1->SetEndRounded(true);

  EXPECT_TRUE(tube1->IsInsideInWorldSpace(p1)) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;


  // For coverage only
  std::cout << "Testing PointBasedSO: ";
  using PointBasedType = itk::PointBasedSpatialObject<3>;
  auto                                       pBSO = PointBasedType::New();
  PointBasedType::SpatialObjectPointType     pnt;
  PointBasedType::SpatialObjectPointListType ll{ pnt };
  pBSO->SetPoints(ll);
  pBSO->GetPoint(0);
  pBSO->Update();
  std::cout << "[PASSED]" << std::endl;

  std::cout << "Testing PointBasedSO AddPoint: ";
  pnt.SetPositionInObjectSpace(1, 1, 1);
  pBSO->AddPoint(pnt);
  EXPECT_EQ(pBSO->GetPoint(1)->GetPositionInObjectSpace()[0], 1) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;

  std::cout << "Testing PointBasedSO RemovePoint: ";
  pBSO->RemovePoint(0);
  EXPECT_EQ(pBSO->GetPoints().size(), 1u) << "[FAILED]";
  EXPECT_EQ(pBSO->GetPoint(0)->GetPositionInObjectSpace()[0], 1) << "[FAILED]";
  std::cout << "[PASSED]" << std::endl;

  // Test Copy and Assignment for TubePointType
  {
    TubePointType pOriginal;

    // itk::SpatialObjectPoint
    pOriginal.SetId(250);
    pOriginal.SetColor(0.5, 0.4, 0.3, 0.2);
    pOriginal.SetPositionInObjectSpace(42, 41, 43);

    // itk::TubeSpatialObjectPoint
    auto tangent = itk::MakeFilled<TubePointType::VectorType>(1);
    pOriginal.SetTangentInObjectSpace(tangent);
    auto normal1 = itk::MakeFilled<TubePointType::CovariantVectorType>(2);
    pOriginal.SetNormal1InObjectSpace(normal1);
    auto normal2 = itk::MakeFilled<TubePointType::CovariantVectorType>(3);
    pOriginal.SetNormal2InObjectSpace(normal2);
    pOriginal.SetRadiusInObjectSpace(1.0);
    pOriginal.SetMedialness(2.0);
    pOriginal.SetRidgeness(3.0);
    pOriginal.SetBranchness(4.0);
    pOriginal.SetCurvature(5.0);
    pOriginal.SetLevelness(6.0);
    pOriginal.SetRoundness(7.0);
    pOriginal.SetIntensity(8.0);
    pOriginal.SetAlpha1(9.0);
    pOriginal.SetAlpha2(10.0);
    pOriginal.SetAlpha3(11.0);

    // itk::DTITubeSpatialObjectTest.cxx
    const itk::DiffusionTensor3D<float> tensor{};
    pOriginal.SetTensorMatrix(tensor);

    // Copy
    const TubePointType pCopy(pOriginal);
    // Assign
    const TubePointType pAssign = pOriginal;

    std::vector<TubePointType> pointVector{ pCopy, pAssign };

    for (const auto & pv : pointVector)
    {
      // itk::SpatialObjectPoint
      EXPECT_EQ(pOriginal.GetId(), pv.GetId());
      EXPECT_DOUBLE_EQ(pOriginal.GetRed(), pv.GetRed());
      EXPECT_DOUBLE_EQ(pOriginal.GetGreen(), pv.GetGreen());
      EXPECT_DOUBLE_EQ(pOriginal.GetBlue(), pv.GetBlue());
      EXPECT_DOUBLE_EQ(pOriginal.GetAlpha(), pv.GetAlpha());
      for (size_t j = 0; j < 3; ++j)
      {
        EXPECT_DOUBLE_EQ(pOriginal.GetPositionInObjectSpace()[j], pv.GetPositionInObjectSpace()[j]);
      }
      // itk::TubeSpatialObjectPoint
      for (size_t j = 0; j < 3; ++j)
      {
        EXPECT_DOUBLE_EQ(pOriginal.GetTangentInObjectSpace()[j], pv.GetTangentInObjectSpace()[j]);
        EXPECT_DOUBLE_EQ(pOriginal.GetNormal1InObjectSpace()[j], pv.GetNormal1InObjectSpace()[j]);
        EXPECT_DOUBLE_EQ(pOriginal.GetNormal2InObjectSpace()[j], pv.GetNormal2InObjectSpace()[j]);
      }
      EXPECT_DOUBLE_EQ(pOriginal.GetRadiusInObjectSpace(), pv.GetRadiusInObjectSpace());
      EXPECT_DOUBLE_EQ(pOriginal.GetMedialness(), pv.GetMedialness());
      EXPECT_DOUBLE_EQ(pOriginal.GetRidgeness(), pv.GetRidgeness());
      EXPECT_DOUBLE_EQ(pOriginal.GetBranchness(), pv.GetBranchness());
      EXPECT_DOUBLE_EQ(pOriginal.GetCurvature(), pv.GetCurvature());
      EXPECT_DOUBLE_EQ(pOriginal.GetLevelness(), pv.GetLevelness());
      EXPECT_DOUBLE_EQ(pOriginal.GetRoundness(), pv.GetRoundness());
      EXPECT_DOUBLE_EQ(pOriginal.GetIntensity(), pv.GetIntensity());
      EXPECT_DOUBLE_EQ(pOriginal.GetAlpha1(), pv.GetAlpha1());
      EXPECT_DOUBLE_EQ(pOriginal.GetAlpha2(), pv.GetAlpha2());
      EXPECT_DOUBLE_EQ(pOriginal.GetAlpha3(), pv.GetAlpha3());

      // itk::DTITubeSpatialObjectPoint
      const auto pOriginal_tensor = pOriginal.GetTensorMatrix();
      const auto pv_tensor = pv.GetTensorMatrix();
      for (size_t j = 0; j < 6; ++j)
      {
        EXPECT_FLOAT_EQ(pOriginal_tensor[j], pv_tensor[j]);
      }
    }

    std::cout << "[DONE]" << std::endl;
  }


  std::cout << "Test finished" << std::endl;
}
