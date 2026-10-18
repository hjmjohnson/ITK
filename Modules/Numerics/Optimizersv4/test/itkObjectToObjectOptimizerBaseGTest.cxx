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
#include "itkObjectToObjectOptimizerBase.h"
#include "itkImage.h"
#include "itkGTest.h"

namespace
{
/* Create a simple metric to use for testing here. */
template <typename TFixedObject, typename TMovingObject>
class ObjectToObjectOptimizerBaseTestMetric : public itk::ObjectToObjectMetricBase
{
public:
  /** Standard class type aliases. */
  using Self = ObjectToObjectOptimizerBaseTestMetric;
  using Superclass = itk::ObjectToObjectMetricBase;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  using typename Superclass::MeasureType;
  using typename Superclass::DerivativeType;
  using typename Superclass::ParametersType;
  using typename Superclass::ParametersValueType;

  itkOverrideGetNameOfClassMacro(ObjectToObjectOptimizerBaseTestMetric);

  itkNewMacro(Self);

  // Pure virtual functions that all Metrics must provide
  unsigned int
  GetNumberOfParameters() const override
  {
    return 5;
  }

  MeasureType
  GetValue() const override
  {
    return 1.0;
  }

  void
  GetDerivative(DerivativeType & derivative) const override
  {
    derivative.Fill(0.0);
  }

  bool
  HasLocalSupport() const override
  {
    return false;
  }

  void
  GetValueAndDerivative(MeasureType & value, DerivativeType & derivative) const override
  {
    value = 1.0;
    derivative.Fill(0.0);
  }

  unsigned int
  GetNumberOfLocalParameters() const override
  {
    return 3;
  }

  void
  UpdateTransformParameters(const DerivativeType &, ParametersValueType) override
  {}

  const ParametersType &
  GetParameters() const override
  {
    return m_Parameters;
  }

  void
  SetParameters(ParametersType &) override
  {}

  void
  Initialize() override
  {}

  void
  PrintSelf(std::ostream & os, itk::Indent indent) const override
  {
    Superclass::PrintSelf(os, indent);
  }

  ParametersType m_Parameters;

private:
  ObjectToObjectOptimizerBaseTestMetric() = default;
  ~ObjectToObjectOptimizerBaseTestMetric() override = default;
};

/* Define a simple derived optimizer class.
 * \class ObjectToObjectOptimizerBaseTestOptimizer */
class ObjectToObjectOptimizerBaseTestOptimizer : public itk::ObjectToObjectOptimizerBase
{
public:
  /** Standard "Self" type alias. */
  using Self = ObjectToObjectOptimizerBaseTestOptimizer;
  using Superclass = itk::ObjectToObjectOptimizerBase;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ObjectToObjectOptimizerBaseTestOptimizer);

  /* Provide initialization for this class */
  void
  StartOptimization(bool doOnlyInitialization = false) override
  {
    Superclass::StartOptimization(doOnlyInitialization);
    std::cout << "StartOptimization called from derived class. doOnlyInitialization: " << doOnlyInitialization
              << std::endl;
  }

  /** Stop condition return string type */
  StopConditionReturnStringType
  GetStopConditionDescription() const override
  {
    return { "Placeholder test return string" };
  }
};
} // namespace

/**
 */
TEST(ObjectToObjectOptimizerBase, ConvertedLegacyTest)
{
  constexpr int ImageDimension{ 2 };
  using ImageType = itk::Image<double, ImageDimension>;

  using MetricType = ObjectToObjectOptimizerBaseTestMetric<ImageType, ImageType>;

  auto metric = MetricType::New();
  auto optimizer = ObjectToObjectOptimizerBaseTestOptimizer::New();

  EXPECT_EQ(optimizer->GetStopConditionDescription(), std::string("Placeholder test return string"))
    << "GetStopConditionDescription did not return properly";
  /* exercise some methods */
  optimizer->SetMetric(metric);
  EXPECT_EQ(optimizer->GetMetric(), metric) << "Set/GetMetric failed.";

  std::cout << "value: " << optimizer->GetCurrentMetricValue() << std::endl;

  /* Test set/get of scales */
  const ObjectToObjectOptimizerBaseTestOptimizer::NumberOfParametersType scalesSize =
    metric->GetNumberOfLocalParameters();
  using ScalesType = ObjectToObjectOptimizerBaseTestOptimizer::ScalesType;
  ScalesType scales(scalesSize, 3.19);
  optimizer->SetScales(scales);
  const ScalesType & scalesReturn = optimizer->GetScales();
  EXPECT_EQ(scalesReturn, scales) << "Set/GetScales failed.";

  optimizer->SetNumberOfWorkUnits(1);

  /* Test StartOptimization */
  EXPECT_NO_THROW(optimizer->StartOptimization());

  /* Test with incorrectly-sized scales. Expect exception */
  scales.SetSize(scalesSize + 1);
  optimizer->SetScales(scales);
  EXPECT_THROW(optimizer->StartOptimization(), itk::ExceptionObject);

  /* Test with scales close to identity, within tolerance.
   * The flag indicating identity scales should be set. */
  scales.SetSize(scalesSize);
  scales.Fill(0.999);
  optimizer->SetScales(scales);
  EXPECT_NO_THROW(optimizer->StartOptimization());
  EXPECT_TRUE(optimizer->GetScalesAreIdentity()) << "Expected GetScalesAreIdentity to return true.";

  /* Test that weights are initialized by default to identity */
  const ObjectToObjectOptimizerBaseTestOptimizer::NumberOfParametersType weightsSize =
    metric->GetNumberOfLocalParameters();
  EXPECT_NO_THROW(optimizer->StartOptimization());
  ScalesType weightsReturn = optimizer->GetWeights();
  EXPECT_EQ(weightsReturn.Size(), 0u);
  EXPECT_TRUE(optimizer->GetWeightsAreIdentity());

  /* Test set/get of weights */
  ScalesType weights(weightsSize, 3.19);
  optimizer->SetWeights(weights);
  weightsReturn = optimizer->GetWeights();
  EXPECT_EQ(weightsReturn, weights) << "Set/GetWeights failed.";

  /* Test with incorrectly-sized weights. Expect exception */
  weights.SetSize(weightsSize + 1);
  optimizer->SetWeights(weights);
  EXPECT_THROW(optimizer->StartOptimization(), itk::ExceptionObject);

  /* Test with weights close to identity, within tolerance.
   * The flag indicating identity weights should be set. */
  weights.SetSize(weightsSize);
  weights.Fill(0.99999);
  optimizer->SetWeights(weights);
  EXPECT_NO_THROW(optimizer->StartOptimization());
  EXPECT_TRUE(optimizer->GetWeightsAreIdentity()) << "Expected GetWeightsAreIdentity to return true.";

  std::cout << "Printing self.." << std::endl;
  std::cout << optimizer << std::endl;

  // Test streaming enumeration for ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer
  // elements
  const std::set<itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer>
    allStopConditionObjectToObjectOptimizer{
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::MAXIMUM_NUMBER_OF_ITERATIONS,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::COSTFUNCTION_ERROR,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::UPDATE_PARAMETERS_ERROR,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::STEP_TOO_SMALL,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::CONVERGENCE_CHECKER_PASSED,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::
        GRADIENT_MAGNITUDE_TOLEARANCE,
      itk::ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer::OTHER_ERROR
    };
  for (const auto & ee : allStopConditionObjectToObjectOptimizer)
  {
    std::cout << "STREAMED ENUM VALUE ObjectToObjectOptimizerBaseTemplateEnums::StopConditionObjectToObjectOptimizer: "
              << ee << std::endl;
  }
}
