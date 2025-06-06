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

// First include the header file to be tested:
#include "itkMersenneTwisterRandomVariateGenerator.h"
#include <gtest/gtest.h>
#include <random> // For mt19937.

// The class to be tested.
using itk::Statistics::MersenneTwisterRandomVariateGenerator;


// Check that the default seed is not just zero!
static_assert(MersenneTwisterRandomVariateGenerator::DefaultSeed != 0);


// Tests that DefaultSeed is the seed of a default-constructed generator.
TEST(MersenneTwisterRandomVariateGenerator, DefaultSeed)
{
  // Derived generator class whose `New()` simply calls the default-constructor.
  class DerivedGenerator : public MersenneTwisterRandomVariateGenerator
  {
  public:
    ITK_DISALLOW_COPY_AND_MOVE(DerivedGenerator);
    itkSimpleNewMacro(DerivedGenerator);

  protected:
    DerivedGenerator() = default;
    ~DerivedGenerator() override = default;
  };

  EXPECT_EQ(DerivedGenerator::New()->GetSeed(), MersenneTwisterRandomVariateGenerator::DefaultSeed);
}


// Tests that GetIntegerVariate() conforms with the C++11 requirement for std::mt19937,
// when the ITK generator uses the default seed of std::mt19937:
// "The 10000th consecutive invocation of a default-constructed object of type mt19937
// shall produce the value 4123659995."
// (C++11 section "Engines and engine adaptors with predefined parameters", [rand.predef])
TEST(MersenneTwisterRandomVariateGenerator, GetIntegerVariateConformsWithStdMt19937Requirement)
{
  const auto generator = MersenneTwisterRandomVariateGenerator::New();
  generator->SetSeed(std::mt19937::default_seed);

  for (int i = 1; i < 10000; ++i)
  {
    generator->GetIntegerVariate();
  }

  // Call GetIntegerVariate() for the 10000th time:
  const auto actualValue = generator->GetIntegerVariate();

  // The value required for std::mt19937 (C++11):
  constexpr auto requiredValue = 4123659995UL;
  ASSERT_EQ(actualValue, requiredValue);
}


// Tests that repeated calls to GetIntegerVariate() yield the same values
// as std::mt19937, when std::mt19937 uses the same seed as the ITK generator.
TEST(MersenneTwisterRandomVariateGenerator, GetIntegerVariateReturnsSameAsStdMt19937)
{
  const auto   generator = MersenneTwisterRandomVariateGenerator::New();
  std::mt19937 stdMt19937{ generator->GetSeed() };

  // Just repeat a few times, assuming that that should be enough.
  for (int i = 0; i < 10; ++i)
  {
    EXPECT_EQ(generator->GetIntegerVariate(), stdMt19937());
  }
}


// Tests that two GetNextSeed() calls return the very same seed value, when ResetNextSeed() is called before each of
// those calls.
TEST(MersenneTwisterRandomVariateGenerator, ResetNextSeed)
{
  // Call GetInstance() beforehand, to make sure the global instance is there already when calling GetNextSeed().
  [[maybe_unused]] const auto globalGenerator = MersenneTwisterRandomVariateGenerator::GetInstance();

  MersenneTwisterRandomVariateGenerator::ResetNextSeed();
  const auto seed = MersenneTwisterRandomVariateGenerator::GetNextSeed();

  MersenneTwisterRandomVariateGenerator::ResetNextSeed();
  EXPECT_EQ(MersenneTwisterRandomVariateGenerator::GetNextSeed(), seed);
}
