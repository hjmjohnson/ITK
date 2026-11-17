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

#include "itkDecisionRule.h"
#include "itkGTest.h"

namespace
{
class MyDecisionRule : public itk::Statistics::DecisionRule
{
public:
  /** Standard class type alias. */
  using Self = MyDecisionRule;
  using Superclass = itk::Statistics::DecisionRule;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(MyDecisionRule);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Types for discriminant values and vectors. */
  using MembershipValueType = Superclass::MembershipValueType;
  using MembershipVectorType = Superclass::MembershipVectorType;

  /** Types for class identifiers. */
  using ClassIdentifierType = Superclass::ClassIdentifierType;

  /** Evaluate membership score */
  ClassIdentifierType
  Evaluate(const MembershipVectorType & scoreVector) const override
  {
    double max = scoreVector[0];

    unsigned int maxIndex = 0;
    for (unsigned int i = 1; i < scoreVector.size(); ++i)
    {
      if (scoreVector[i] > max)
      {
        max = scoreVector[i];
        maxIndex = i;
      }
    }
    return maxIndex;
  }
};
} // namespace

TEST(DecisionRule, ConvertedLegacyTest)
{
  using DecisionRuleType = MyDecisionRule;

  using MembershipVectorType = DecisionRuleType::MembershipVectorType;

  auto decisionRule = DecisionRuleType::New();

  std::cout << decisionRule->GetNameOfClass() << std::endl;
  std::cout << decisionRule->DecisionRuleType::Superclass::GetNameOfClass() << std::endl;

  decisionRule->Print(std::cout);

  MembershipVectorType membershipScoreVector;

  constexpr double membershipScore1{ 0.1 };
  membershipScoreVector.push_back(membershipScore1);

  constexpr double membershipScore2{ 0.5 };
  membershipScoreVector.push_back(membershipScore2);

  constexpr double membershipScore3{ 1.9 };
  membershipScoreVector.push_back(membershipScore3);

  // the maximum score is the third component. The decision rule should
  // return index ( 2)
  EXPECT_EQ(decisionRule->Evaluate(membershipScoreVector), 2u);
}
