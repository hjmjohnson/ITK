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

#include "itkAutoPointer.h"
#include "itkQuadEdge.h"
#include "itkGTest.h"
#include <iostream>

TEST(QuadEdge, ConvertedLegacyTest)
{
  using QuadEdgeType = itk::QuadEdge;

  // Throughout the tests, create AutoPointers to manage the lifetimes of
  // QuadEdgeType instances. The AutoPointers are created in addition to the raw
  // pointers. This avoids the need to call GetPointer() in every comparison.
  using QuadEdgeTypePointer = itk::AutoPointer<QuadEdgeType>;

  // Tests for the GetRot() SetRot() methods
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

    quadEdge1->GetRot(); // testing null case

    // Verify that it can be set.
    quadEdge1->SetRot(quadEdge2);
    EXPECT_EQ(quadEdge1->GetRot(), quadEdge2) << "Error in SetRot() / GetRot() ";
    // Test the const version
    EXPECT_EQ(quadEdge1c->GetRot(), quadEdge2) << "Error in const GetRot() ";

    // Verify that it can be changed.
    quadEdge1->SetRot(quadEdge3);
    EXPECT_EQ(quadEdge1->GetRot(), quadEdge3) << "Error in changing SetRot() / GetRot() ";
    // Test the const version
    EXPECT_EQ(quadEdge1c->GetRot(), quadEdge3) << "Error in changed const GetRot() ";

    std::cout << "GetRot()/SetRot() Test passed ! " << std::endl;
  } // end of local scope for tests

  // Tests for the GetOnext() SetOnext() methods
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

    quadEdge1->GetOnext(); // testing null case

    // Verify that it can be set.
    quadEdge1->SetOnext(quadEdge2);
    EXPECT_EQ(quadEdge1->GetOnext(), quadEdge2) << "Error in SetOnext() / GetOnext() ";

    // Test the const version
    EXPECT_EQ(quadEdge1c->GetOnext(), quadEdge2) << "Error in const GetOnext() ";

    // Verify that it can be changed.
    auto *                    quadEdge3 = new QuadEdgeType;
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);

    quadEdge1->SetOnext(quadEdge3);

    EXPECT_EQ(quadEdge1->GetOnext(), quadEdge3) << "Error in changing SetOnext() / GetOnext() ";

    // Test the const version
    EXPECT_EQ(quadEdge1c->GetOnext(), quadEdge3) << "Error changed const GetOnext() ";

    std::cout << "GetOnext()/SetOnext() Test passed ! " << std::endl;
  } // end of local scope for tests

  // Tests for the GetSym() methods
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;
    const QuadEdgeType * quadEdge2c = quadEdge2;
    const QuadEdgeType * quadEdge3c = quadEdge3;
    const QuadEdgeType * quadEdge4c = quadEdge4;

    // testing first GetSym()'s fail case
    EXPECT_EQ(quadEdge1->GetSym(), nullptr) << "Error GetSym( ) should fail here ";
    EXPECT_EQ(quadEdge1c->GetSym(), nullptr) << "Error GetSym( ) should fail here ";

    // testing the second GetSym()'s fail case
    quadEdge1->SetRot(quadEdge2);
    EXPECT_EQ(quadEdge1->GetSym(), nullptr) << "Error GetSym( ) should fail here ";
    EXPECT_EQ(quadEdge1c->GetSym(), nullptr) << "Error GetSym( ) should fail here ";

    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    EXPECT_EQ(quadEdge1->GetSym(), quadEdge3) << "Error in GetSym() ";

    EXPECT_EQ(quadEdge1c->GetSym(), quadEdge3) << "Error in const GetSym() ";

    EXPECT_EQ(quadEdge2->GetSym(), quadEdge4) << "Error in GetSym() B ";

    EXPECT_EQ(quadEdge2c->GetSym(), quadEdge4) << "Error in const GetSym() B";

    EXPECT_EQ(quadEdge3->GetSym(), quadEdge1) << "Error in GetSym() C ";

    EXPECT_EQ(quadEdge3c->GetSym(), quadEdge1) << "Error in const GetSym() C";

    EXPECT_EQ(quadEdge4->GetSym(), quadEdge2) << "Error in GetSym() D ";

    EXPECT_EQ(quadEdge4c->GetSym(), quadEdge2) << "Error in const GetSym() D";

    std::cout << "GetSym()   Test passed ! " << std::endl;
  }


  // Tests for the GetLnext() methods
  // returns the next edge with same left face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;
    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);
    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    // testing first fail case
    EXPECT_EQ(quadEdge1->GetLnext(), nullptr) << "Error in GetLNext()";
    EXPECT_EQ(quadEdge1c->GetLnext(), nullptr) << "Error in GetLNext()";
#endif

    //                        /
    //                       / quadEdgeA
    //          Face        /
    //                     /
    //                    /
    //   --------------->O
    //   quadEdge1
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

#ifndef NDEBUG
    // testing second fail case
    quadEdge4->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetLnext(), nullptr) << "Error in GetLnext()";
    EXPECT_EQ(quadEdge1c->GetLnext(), nullptr) << "Error in GetLnext()";
#endif

    // testing third fail case
    quadEdge4->SetOnext(quadEdgeB);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetLnext(), nullptr) << "Error in GetLnext()";
    EXPECT_EQ(quadEdge1c->GetLnext(), nullptr) << "Error in GetLnext()";
#endif

    quadEdgeB->SetRot(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetLnext(), quadEdgeA) << "Error in GetLnext()";

    EXPECT_EQ(quadEdge1c->GetLnext(), quadEdgeA) << "Error in const GetLnext()";

    std::cout << "GetLnext() Test passed ! " << std::endl;
  }

  // Tests for the GetRnext() methods
  // returns the next edge with same right face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;
    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);
    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);

    const QuadEdgeType * quadEdgeAc = quadEdgeA;

#ifndef NDEBUG
    const QuadEdgeType * quadEdge1c = quadEdge1;

    // testing first fail case
    EXPECT_EQ(quadEdge1->GetRnext(), nullptr) << "Error in GetRnext()";
    EXPECT_EQ(quadEdge1c->GetRnext(), nullptr) << "Error in GetRnext()";
#endif

    //
    //        quadEdge1
    //   --------------------->O
    //                        /
    //                       /
    //          Face        /
    //                     /quadEdgeA
    //                    /
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);


#ifndef NDEBUG
    quadEdge2->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetRnext(), nullptr) << "Error in GetRnext()";
    EXPECT_EQ(quadEdge1c->GetRnext(), nullptr) << "Error in GetRnext()";
#endif

    quadEdge2->SetOnext(quadEdgeB);
    quadEdgeB->SetOnext(quadEdge2);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetRnext(), nullptr) << "Error in GetRnext()";
    EXPECT_EQ(quadEdge1c->GetRnext(), nullptr) << "Error in GetRnext()";
#endif

    quadEdgeA->SetRot(quadEdgeB);

    EXPECT_EQ(quadEdgeA->GetRnext(), quadEdge1) << "Error in GetRnext()";

    EXPECT_EQ(quadEdgeAc->GetRnext(), quadEdge1) << "Error in const GetRnext()";

    std::cout << "GetRnext() Test passed ! " << std::endl;
  }

  // Tests for the GetDnext() methods
  // returns the next edge with same right face
  // and same destination
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetDnext(), nullptr) << "Error 1 in GetDnext()";
    EXPECT_EQ(quadEdge1c->GetDnext(), nullptr) << "Error 1 in GetDnext()";
#endif

    //
    //        quadEdge1
    //   -------------------->-O
    //                         ^
    //                         |
    //          Face           |
    //                         |  quadEdgeC
    //                         |
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

#ifndef NDEBUG
    quadEdge3->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetDnext(), nullptr) << "Error 2 in GetDnext()";
    EXPECT_EQ(quadEdge1c->GetDnext(), nullptr) << "Error 2 in GetDnext()";
#endif

    quadEdge3->SetOnext(quadEdgeA);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetDnext(), nullptr) << "Error 3 in GetDnext()";
    EXPECT_EQ(quadEdge1c->GetDnext(), nullptr) << "Error 3 in GetDnext()";
#endif

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetDnext(), quadEdgeC) << "Error 4 in GetDnext()";

    EXPECT_EQ(quadEdge1c->GetDnext(), quadEdgeC) << "Error 5 in const GetDnext()";

    std::cout << "GetDnext() Test passed ! " << std::endl;
  }


  // Tests for the GetOprev() methods
  // returns the previous edge with same origin
  // and same destination
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetOprev(), nullptr) << "Error in GetOprev()";
    EXPECT_EQ(quadEdge1c->GetOprev(), nullptr) << "Error in GetOprev()";
#endif

    //
    //                        ^/^
    //                        /
    //                       / quadEdgeA
    //          Face        /
    //                     /
    //                    /
    //   <---------------O
    //       quadEdge1
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

#ifndef NDEBUG
    quadEdge2->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetOprev(), nullptr) << "Error in GetOprev()";
    EXPECT_EQ(quadEdge1c->GetOprev(), nullptr) << "Error in GetOprev()";
#endif

    quadEdge2->SetOnext(quadEdgeD);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetOprev(), nullptr) << "Error in GetOprev()";
    EXPECT_EQ(quadEdge1c->GetOprev(), nullptr) << "Error in GetOprev()";
#endif

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetOprev(), quadEdgeA) << "Error in GetOprev()";

    EXPECT_EQ(quadEdge1c->GetOprev(), quadEdgeA) << "Error in const GetOprev()";

    std::cout << "GetOprev() Test passed ! " << std::endl;
  }


  // Tests for the GetLprev() methods
  // returns the previous edge with same left face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    quadEdge1->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetLprev(), nullptr) << "Error in GetLprev()";
    EXPECT_EQ(quadEdge1c->GetLprev(), nullptr) << "Error in GetLprev()";
#endif

    //
    //                        ^/^
    //                        /
    //                       / quadEdge1
    //          Face        /
    //                     /
    //                    /
    //   --------------->O
    //       quadEdgeA
    //

    quadEdge1->SetOnext(quadEdgeC);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetLprev(), nullptr) << "Error in GetLprev()";
    EXPECT_EQ(quadEdge1c->GetLprev(), nullptr) << "Error in GetLprev()";
#endif

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    EXPECT_EQ(quadEdge1->GetLprev(), quadEdgeA) << "Error in GetLprev()";

    EXPECT_EQ(quadEdge1c->GetLprev(), quadEdgeA) << "Error in const GetLprev()";

    std::cout << "GetLprev() Test passed ! " << std::endl;
  }


  // Tests for the GetRprev() methods
  // returns the previous edge with same right face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetRprev(), nullptr) << "Error in GetRprev()";
    EXPECT_EQ(quadEdge1c->GetRprev(), nullptr) << "Error in GetRprev()";
#endif

    //
    //
    //
    //
    //     ???
    //
    //
    //
    //
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

#ifndef NDEBUG
    quadEdge3->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetRprev(), nullptr) << "Error in GetRprev()";
    EXPECT_EQ(quadEdge1c->GetRprev(), nullptr) << "Error in GetRprev()";
#endif

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge3->SetOnext(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetRprev(), quadEdgeA) << "Error in GetRprev()";

    EXPECT_EQ(quadEdge1c->GetRprev(), quadEdgeA) << "Error in const GetRprev()";

    std::cout << "GetRprev() Test passed ! " << std::endl;
  }


  // Tests for the GetDprev() methods
  // returns the previous edge with same right face
  // and same destination
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetDprev(), nullptr) << "Error in GetDprev()";
    EXPECT_EQ(quadEdge1c->GetDprev(), nullptr) << "Error in GetDprev()";
#endif

    //                       |
    //                       |
    //                       |
    //                       | quadEdgeA
    //                       |
    //                       |
    //                       V
    //  -------------------> 0
    //      quadEdge1
    //

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

#ifndef NDEBUG
    quadEdge4->SetOnext(nullptr);
    EXPECT_EQ(quadEdge1->GetDprev(), nullptr) << "Error in GetDprev()";
    EXPECT_EQ(quadEdge1c->GetDprev(), nullptr) << "Error in GetDprev()";
#endif

    quadEdge4->SetOnext(quadEdgeB);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetDprev(), nullptr) << "Error in GetDprev()";
    EXPECT_EQ(quadEdge1c->GetDprev(), nullptr) << "Error in GetDprev()";
#endif

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetDprev(), quadEdgeA) << "Error in GetDprev()";

    EXPECT_EQ(quadEdge1c->GetDprev(), quadEdgeA) << "Error in const GetDprev()";

    std::cout << "GetDprev() Test passed ! " << std::endl;
  }

  // Tests for the GetInvRot() methods
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    // Testing incomplete connections.
    EXPECT_EQ(quadEdge1->GetInvRot(), nullptr) << "Error in GetInvRot()";
    EXPECT_EQ(quadEdge1c->GetInvRot(), nullptr) << "Error in GetInvRot()";
#endif

    quadEdge1->SetRot(quadEdge2);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetInvRot(), nullptr) << "Error in GetInvRot()";
    EXPECT_EQ(quadEdge1c->GetInvRot(), nullptr) << "Error in GetInvRot()";
#endif

    quadEdge2->SetRot(quadEdge3);
#ifndef NDEBUG
    EXPECT_EQ(quadEdge1->GetInvRot(), nullptr) << "Error in GetInvRot()";
    EXPECT_EQ(quadEdge1c->GetInvRot(), nullptr) << "Error in GetInvRot()";
#endif

    quadEdge3->SetRot(quadEdge4);

    // Finally, the well constructed case
    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    EXPECT_EQ(quadEdge1->GetInvRot(), quadEdge4) << "Error in GetInvRot()";

    EXPECT_EQ(quadEdge1c->GetInvRot(), quadEdge4) << "Error in const GetInvRot()";

    std::cout << "GetInvRot() Test passed ! " << std::endl;
  }

  // Tests for the GetInvOnext() methods
  // returns the previous edge with same origin
  // and same destination
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    quadEdge1->GetInvOnext(); // testing null case
#endif

    //
    //                        ^/^
    //                        /
    //                       / quadEdgeA
    //          Face        /
    //                     /
    //                    /
    //   <---------------O
    //       quadEdge1
    //

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    quadEdge2->SetOnext(quadEdgeD); // rely on this one
    quadEdgeA->SetOnext(quadEdge1);

    EXPECT_EQ(quadEdge1->GetInvOnext(), quadEdgeA) << "Error in GetInvOnext()";

    EXPECT_EQ(quadEdge1c->GetInvOnext(), quadEdgeA) << "Error in const GetInvOnext()";

    std::cout << "GetInvOnext() Test passed ! " << std::endl;
  }

  // Tests for the GetInvLnext() methods
  // returns the previous edge with same left face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    quadEdge1->GetInvLnext(); // testing null case
#endif

    //
    //                        ^/^
    //                        /
    //                       / quadEdge1
    //          Face        /
    //                     /
    //                    /
    //   --------------->O
    //       quadEdgeA
    //

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    quadEdge1->SetOnext(quadEdgeC);

    EXPECT_EQ(quadEdge1->GetInvLnext(), quadEdgeA) << "Error in GetInvLnext()";

    EXPECT_EQ(quadEdge1c->GetInvLnext(), quadEdgeA) << "Error in const GetInvLnext()";

    std::cout << "GetInvLnext() Test passed ! " << std::endl;
  }

  // Tests for the GetInvRnext() methods
  // returns the previous edge with same right face
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    quadEdge1->GetInvRnext(); // testing null case
#endif

    //
    //
    //
    //
    //     ???
    //
    //
    //
    //
    //

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    quadEdge3->SetOnext(quadEdgeA);

    EXPECT_EQ(quadEdge1->GetInvRnext(), quadEdgeA) << "Error in GetInvRnext()";

    EXPECT_EQ(quadEdge1c->GetInvRnext(), quadEdgeA) << "Error in const GetInvRnext()";

    std::cout << "GetInvRnext() Test passed ! " << std::endl;
  }

  // Tests for the GetInvDnext() methods
  // returns the previous edge with same right face
  // and same destination
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;

    auto * quadEdgeA = new QuadEdgeType;
    auto * quadEdgeB = new QuadEdgeType;
    auto * quadEdgeC = new QuadEdgeType;
    auto * quadEdgeD = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);

    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);
    const QuadEdgeTypePointer quadEdgeBp(quadEdgeB, true);
    const QuadEdgeTypePointer quadEdgeCp(quadEdgeC, true);
    const QuadEdgeTypePointer quadEdgeDp(quadEdgeD, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

#ifndef NDEBUG
    quadEdge1->GetInvDnext(); // testing null case
#endif

    //                       |
    //                       |
    //                       |
    //                       | quadEdgeA
    //                       |
    //                       |
    //                       V
    //  -------------------> 0
    //      quadEdge1
    //

    quadEdgeA->SetRot(quadEdgeB);
    quadEdgeB->SetRot(quadEdgeC);
    quadEdgeC->SetRot(quadEdgeD);
    quadEdgeD->SetRot(quadEdgeA);

    quadEdge1->SetRot(quadEdge2);
    quadEdge2->SetRot(quadEdge3);
    quadEdge3->SetRot(quadEdge4);
    quadEdge4->SetRot(quadEdge1);

    quadEdge4->SetOnext(quadEdgeB);

    EXPECT_EQ(quadEdge1->GetInvDnext(), quadEdgeA) << "Error in GetInvDnext()";

    EXPECT_EQ(quadEdge1c->GetInvDnext(), quadEdgeA) << "Error in const GetInvDnext()";

    std::cout << "GetInvDnext() Test passed ! " << std::endl;
  }


  // Tests for the IsHalfEdge() method
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdgeA = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdgeAp(quadEdgeA, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

    EXPECT_TRUE(quadEdge1c->IsHalfEdge()) << "Error in IsHalfEdge() A";

    quadEdge1->SetRot(quadEdge2);

    EXPECT_TRUE(quadEdge1c->IsHalfEdge()) << "Error in IsHalfEdge() B";

    quadEdge1->SetOnext(quadEdgeA);

    EXPECT_FALSE(quadEdge1c->IsHalfEdge()) << "Error in IsHalfEdge() C";

    quadEdge1->SetRot(nullptr);

    EXPECT_TRUE(quadEdge1c->IsHalfEdge()) << "Error in IsHalfEdge() D";

    std::cout << "IsHalfEdge() Test passed ! " << std::endl;
  }

  // Tests for the IsIsolated() method
  { // create a local scope for these tests
    auto *                    quadEdge1 = new QuadEdgeType;
    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeType *      quadEdge1c = quadEdge1;

    EXPECT_TRUE(quadEdge1c->IsIsolated()) << "Error in IsIsolated() A";

    auto *                    quadEdge2 = new QuadEdgeType;
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);

    quadEdge1->SetOnext(quadEdge2);

    EXPECT_FALSE(quadEdge1c->IsIsolated()) << "Error in IsIsolated() B";

    quadEdge1->SetOnext(quadEdge1);

    EXPECT_TRUE(quadEdge1c->IsIsolated()) << "Error in IsIsolated() C";

    std::cout << "IsIsolated() Test passed ! " << std::endl;
  }

  // Tests for the IsEdgeInOnextRing() method
  { // create a local scope for these tests
    auto * quadEdge1 = new QuadEdgeType;
    auto * quadEdge2 = new QuadEdgeType;
    auto * quadEdge3 = new QuadEdgeType;
    auto * quadEdge4 = new QuadEdgeType;
    auto * quadEdge5 = new QuadEdgeType;
    auto * quadEdge6 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdge1p(quadEdge1, true);
    const QuadEdgeTypePointer quadEdge2p(quadEdge2, true);
    const QuadEdgeTypePointer quadEdge3p(quadEdge3, true);
    const QuadEdgeTypePointer quadEdge4p(quadEdge4, true);
    const QuadEdgeTypePointer quadEdge5p(quadEdge5, true);
    const QuadEdgeTypePointer quadEdge6p(quadEdge6, true);

    const QuadEdgeType * quadEdge1c = quadEdge1;

    quadEdge1->SetOnext(nullptr);
    quadEdge1c->IsEdgeInOnextRing(nullptr);

    EXPECT_FALSE(quadEdge1c->IsEdgeInOnextRing(quadEdge6)) << "Error in IsEdgeInOnextRing() A";

    // Create a ring
    quadEdge1->SetOnext(quadEdge2);
    quadEdge2->SetOnext(quadEdge3);
    quadEdge3->SetOnext(quadEdge4);
    quadEdge4->SetOnext(quadEdge5);
    quadEdge5->SetOnext(quadEdge1);

    EXPECT_FALSE(quadEdge1c->IsEdgeInOnextRing(quadEdge6)) << "Error in IsEdgeInOnextRing() B";

    // Close the ring by adding
    quadEdge5->SetOnext(quadEdge6);
    quadEdge6->SetOnext(quadEdge1);

    EXPECT_TRUE(quadEdge1c->IsEdgeInOnextRing(quadEdge6)) << "Error in IsEdgeInOnextRing() C";

    std::cout << "IsEdgeInOnextRing() Test passed ! " << std::endl;
  } // end of local scope for tests

  // Tests for the IsLnextGivenSizeCyclic() method
  { // create a local scope for these tests
    //                                           //
    //                                           //
    // Create quad-edges on the three physical   //
    // edges (A,B,C) of a triangular face        //
    //                                           //
    //                                           //
    //                   /\                      //
    //                  /  \                     //
    //                 /    \                    //
    //                /      \                   //
    //           B   /        \  A               //
    //              /          \                 //
    //             /            \                //
    //            /              \               //
    //           /                \              //
    //           ------------------              //
    //                   C   quadEdgeC1-->       //
    //                                           //
    //                                           //
    auto * quadEdgeA1 = new QuadEdgeType;
    auto * quadEdgeA2 = new QuadEdgeType;
    auto * quadEdgeA3 = new QuadEdgeType;
    auto * quadEdgeA4 = new QuadEdgeType;

    auto * quadEdgeB1 = new QuadEdgeType;
    auto * quadEdgeB2 = new QuadEdgeType;
    auto * quadEdgeB3 = new QuadEdgeType;
    auto * quadEdgeB4 = new QuadEdgeType;

    auto * quadEdgeC1 = new QuadEdgeType;
    auto * quadEdgeC2 = new QuadEdgeType;
    auto * quadEdgeC3 = new QuadEdgeType;
    auto * quadEdgeC4 = new QuadEdgeType;

    const QuadEdgeTypePointer quadEdgeA1p(quadEdgeA1, true);
    const QuadEdgeTypePointer quadEdgeA2p(quadEdgeA2, true);
    const QuadEdgeTypePointer quadEdgeA3p(quadEdgeA3, true);
    const QuadEdgeTypePointer quadEdgeA4p(quadEdgeA4, true);

    const QuadEdgeTypePointer quadEdgeB1p(quadEdgeB1, true);
    const QuadEdgeTypePointer quadEdgeB2p(quadEdgeB2, true);
    const QuadEdgeTypePointer quadEdgeB3p(quadEdgeB3, true);
    const QuadEdgeTypePointer quadEdgeB4p(quadEdgeB4, true);

    const QuadEdgeTypePointer quadEdgeC1p(quadEdgeC1, true);
    const QuadEdgeTypePointer quadEdgeC2p(quadEdgeC2, true);
    const QuadEdgeTypePointer quadEdgeC3p(quadEdgeC3, true);
    const QuadEdgeTypePointer quadEdgeC4p(quadEdgeC4, true);

    const QuadEdgeType * quadEdgeA1c = quadEdgeA1;
    const QuadEdgeType * quadEdgeB1c = quadEdgeB1;
    const QuadEdgeType * quadEdgeC1c = quadEdgeC1;
    const QuadEdgeType * quadEdgeA4c = quadEdgeA4;

#ifndef NDEBUG
    [[maybe_unused]] auto val = quadEdgeA1c->IsLnextGivenSizeCyclic(3); // testing null case

    EXPECT_FALSE(quadEdgeA1c->IsLnextGivenSizeCyclic(3)) << "Error in IsLnextGivenSizeCyclic() A";
#endif


    // Connect quad-edges inside physical edge A
    quadEdgeA1->SetRot(quadEdgeA2);
    quadEdgeA2->SetRot(quadEdgeA3);
    quadEdgeA3->SetRot(quadEdgeA4);
    quadEdgeA4->SetRot(quadEdgeA1);

    // Connect quad-edges inside physical edge B
    quadEdgeB1->SetRot(quadEdgeB2);
    quadEdgeB2->SetRot(quadEdgeB3);
    quadEdgeB3->SetRot(quadEdgeB4);
    quadEdgeB4->SetRot(quadEdgeB1);

    // Connect quad-edges inside physical edge C
    quadEdgeC1->SetRot(quadEdgeC2);
    quadEdgeC2->SetRot(quadEdgeC3);
    quadEdgeC3->SetRot(quadEdgeC4);
    quadEdgeC4->SetRot(quadEdgeC1);

    // PRIMAL ORING
    // connect Orings of Top point
    quadEdgeA3->SetOnext(quadEdgeB1);
    quadEdgeB1->SetOnext(quadEdgeA3);

    // connect Oring of bottom left point
    quadEdgeB3->SetOnext(quadEdgeC1);
    quadEdgeC1->SetOnext(quadEdgeB3);

    // connect Oring of bottom right point
    quadEdgeC3->SetOnext(quadEdgeA1);
    quadEdgeA1->SetOnext(quadEdgeC3);

    // DUAL ORING (FACE)
    // triangle
    quadEdgeA4->SetOnext(quadEdgeB4);
    quadEdgeB4->SetOnext(quadEdgeC4);
    quadEdgeC4->SetOnext(quadEdgeA4);

    // outside
    quadEdgeA2->SetOnext(quadEdgeC2);
    quadEdgeC2->SetOnext(quadEdgeB2);
    quadEdgeB2->SetOnext(quadEdgeA2);

    const unsigned int     quadEdgeA1Order = quadEdgeA1c->GetOrder();
    constexpr unsigned int quadEdgeA1ExpectedOrder{ 2 };
    EXPECT_EQ(quadEdgeA1Order, quadEdgeA1ExpectedOrder) << "Error in GetOrder() A";

    const unsigned int     quadEdgeB1Order = quadEdgeB1c->GetOrder();
    constexpr unsigned int quadEdgeB1ExpectedOrder{ 2 };
    EXPECT_EQ(quadEdgeB1Order, quadEdgeB1ExpectedOrder) << "Error in GetOrder() B";

    const unsigned int     quadEdgeC1Order = quadEdgeC1c->GetOrder();
    constexpr unsigned int quadEdgeC1ExpectedOrder{ 2 };
    EXPECT_EQ(quadEdgeC1Order, quadEdgeC1ExpectedOrder) << "Error in GetOrder() C";

    const unsigned int     quadEdgeA4Order = quadEdgeA4c->GetOrder();
    constexpr unsigned int quadEdgeA4ExpectedOrder{ 3 };
    EXPECT_EQ(quadEdgeA4Order, quadEdgeA4ExpectedOrder) << "Error in GetOrder() D";

    // Check with the right period
    EXPECT_TRUE(quadEdgeA1c->IsLnextGivenSizeCyclic(3)) << "Error in IsLnextGivenSizeCyclic() B";

    // Check a wrong period on purpose
    EXPECT_FALSE(quadEdgeA1c->IsLnextGivenSizeCyclic(4)) << "Error in IsLnextGivenSizeCyclic() C";

    std::cout << "IsLnextGivenSizeCyclic() Test passed ! " << std::endl;
  } // end of local scope for tests

  std::cout << "QuadEdge Test Passed !" << std::endl;
}
