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

// Program test for the basic QE layer.
#include <iostream>
#include "itkGeometricalQuadEdge.h"
#include "itkGTest.h"

namespace
{
class itkQuadEdgeMeshBasicLayerTestHelper
{
public:
  using PrimalType = itk::GeometricalQuadEdge<int, int, bool, bool>;
  using DualType = PrimalType::DualType;

  static PrimalType *
  MakeQuadEdges()
  {
    auto * e1 = new PrimalType();
    auto * e2 = new DualType();
    auto * e3 = new PrimalType();
    auto * e4 = new DualType();

    e1->SetRot(e2);
    e2->SetRot(e3);
    e3->SetRot(e4);
    e4->SetRot(e1);

    e1->SetOnext(e1);
    e2->SetOnext(e4);
    e3->SetOnext(e3);
    e4->SetOnext(e2); // dual quadrants form the e2<->e4 2-cycle (Guibas-Stolfi MakeEdge)

    return e1;
  }
};
} // namespace

TEST(QuadEdgeMeshBasicLayer, ConvertedLegacyTest)
{
  using PrimalType = itkQuadEdgeMeshBasicLayerTestHelper::PrimalType;

  PrimalType * e[5];

  //////////////////////////////////////////////////////////
  std::cout << "Creating edges" << std::endl;
  {
    PrimalType defaultConstructed; // default-ctor smoke test; real edges built below
    (void)defaultConstructed;
  }
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Testing MakeEdge" << std::endl;
  for (auto & i : e)
  {
    i = itkQuadEdgeMeshBasicLayerTestHelper::MakeQuadEdges();
  }
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Testing ring for Origin() unset values" << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    EXPECT_FALSE(e[i]->IsOriginSet()) << "IsOriginSet() should not be set for edge number " << i << ".";
  }

  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Setting Origin() and Destination() values... " << std::endl;
  const int org[5] = { 0, 1, 2, 3, 0 };
  const int dest[5] = { 1, 2, 3, 0, 2 };

  for (int i = 0; i < 5; ++i)
  {
    e[i]->SetOrigin(org[i]);
    e[i]->SetDestination(dest[i]);
  }
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Testing ring for Origin() set values... " << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    EXPECT_TRUE(e[i]->IsOriginSet()) << "IsOriginSet() nullptr value failed for edge number " << i << ".";
  } // rof
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Splicing... " << std::endl;
  e[0]->Splice(e[4]);
  e[4]->Splice(e[3]->GetSym());
  e[1]->Splice(e[0]->GetSym());
  e[2]->Splice(e[4]->GetSym());
  e[4]->GetSym()->Splice(e[1]->GetSym());
  e[3]->Splice(e[2]->GetSym());
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Testing Origin() and Destination() adjacency... " << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    EXPECT_EQ(e[i]->GetOrigin(), org[i]) << "Erroneous GetOrigin() on edge number " << i << ".";
    EXPECT_EQ(e[i]->GetDestination(), dest[i]) << "Erroneous GetDestination() on edge number " << i << ".";
  } // rof
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Setting faces... " << std::endl;
  e[0]->SetLeft(0);
  e[1]->SetLeft(0);
  e[4]->SetRight(0);
  e[2]->SetLeft(1);
  e[3]->SetLeft(1);
  e[4]->SetLeft(1);
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  using IteratorGeom = PrimalType::IteratorGeom;
  std::cout << "Testing Onext iterators... " << std::endl;
  const int onextDestination[5][3] = { { 1, 2, 3 },
                                       { 2, 0, 0 }, // Last 0 is a dummy
                                       { 3, 0, 1 },
                                       { 0, 2, 0 }, // Last 0 is a dummy
                                       { 2, 3, 1 } };
  for (int edge = 0; edge < 5; ++edge)
  {
    int test = 0;
    for (IteratorGeom itOnext = e[edge]->BeginGeomOnext(); itOnext != e[edge]->EndGeomOnext(); itOnext++, test++)
    {
      EXPECT_EQ(itOnext.Value()->GetDestination(), onextDestination[edge][test])
        << "Erroneous GetDestination() on edge number " << edge << ".";
    }
  }
  std::cout << "Passed" << std::endl;

  //////////////////////////////////////////////////////////
  std::cout << "Testing Lnext iterators... " << std::endl;
  const int lnextDestination[5][3] = { { 0, 1, 2 }, { 1, 2, 0 }, { 2, 3, 0 }, { 3, 0, 2 }, { 0, 2, 3 } };
  for (int edge = 0; edge < 5; ++edge)
  {
    int test = 0;
    for (IteratorGeom itLnext = e[edge]->BeginGeomLnext(); itLnext != e[edge]->EndGeomLnext(); itLnext++, test++)
    {
      EXPECT_EQ(*itLnext, lnextDestination[edge][test]) << "Erroneous GetDestination() on edge number " << edge << ".";
    }
  }

  std::cout << "on Sym()... " << std::endl;
  constexpr int lnextDestinationOnSym[3]{ 2, 0, 1 };
  int           test = 0;
  for (IteratorGeom itLnext = e[4]->GetSym()->BeginGeomLnext(); itLnext != e[4]->GetSym()->EndGeomLnext();
       itLnext++, test++)
  {
    EXPECT_EQ(*itLnext, lnextDestinationOnSym[test]) << "Erroneous GetDestination() on edge number 4.";
  }
  std::cout << "Passed" << std::endl;


  //////////////////////////////////////////////////////////
  std::cout << "Testing Sym iterators... " << std::endl;
  const int symDestination[5][3] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }, { 0, 2 } };
  for (int edge = 0; edge < 5; ++edge)
  {
    test = 0;
    for (IteratorGeom itSym = e[edge]->BeginGeomSym(); itSym != e[edge]->EndGeomSym(); itSym++, test++)
    {
      EXPECT_EQ(*itSym, symDestination[edge][test]) << "Erroneous GetDestination() on edge number " << edge << ".";
    }
  }
  std::cout << "Passed" << std::endl;

  // Free the five quad-edges; each owns a four-element Rot ring.
  for (auto & i : e)
  {
    delete i->GetRot()->GetRot()->GetRot();
    delete i->GetRot()->GetRot();
    delete i->GetRot();
    delete i;
  }
}
