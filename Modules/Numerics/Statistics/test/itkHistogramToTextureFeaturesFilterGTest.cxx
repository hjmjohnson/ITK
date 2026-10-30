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

#include "itkHistogramToTextureFeaturesFilter.h"
#include "itkGTest.h"

TEST(HistogramToTextureFeaturesFilter, ConvertedLegacyTest)
{
  // Data definitions
  constexpr unsigned int HISTOGRAM_AXIS_LEN{ 25 };


  //------------------------------------------------------
  // Create a simple test histogram. The histogram must be
  // symmetric and normalized.
  //------------------------------------------------------
  using MeasurementType = float;
  using HistogramType = itk::Statistics::Histogram<MeasurementType>;
  auto histogram = HistogramType::New();

  constexpr unsigned int measurementVectorSize{ 2 };

  histogram->SetMeasurementVectorSize(measurementVectorSize);

  HistogramType::SizeType size(measurementVectorSize, HISTOGRAM_AXIS_LEN);

  HistogramType::MeasurementVectorType lowerBound(measurementVectorSize);
  HistogramType::MeasurementVectorType upperBound(measurementVectorSize);

  lowerBound[0] = 0;
  lowerBound[1] = 0;

  upperBound[0] = HISTOGRAM_AXIS_LEN + 1;
  upperBound[1] = HISTOGRAM_AXIS_LEN + 1;

  histogram->Initialize(size, lowerBound, upperBound);

  HistogramType::IndexType index(measurementVectorSize);

  index[0] = 0;
  index[1] = 0;
  HistogramType::AbsoluteFrequencyType frequency = 10;
  HistogramType::InstanceIdentifier    identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 3;
  index[1] = 3;
  frequency = 50;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 2;
  index[1] = 1;
  frequency = 5;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 1;
  index[1] = 2;
  frequency = 5;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 7;
  index[1] = 6;
  frequency = 10;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 6;
  index[1] = 7;
  frequency = 10;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  index[0] = 10;
  index[1] = 10;
  frequency = 10;
  identifier = histogram->GetInstanceIdentifier(index);
  histogram->SetFrequency(identifier, frequency);

  using HistogramToTextureFeaturesFilterType = itk::Statistics::HistogramToTextureFeaturesFilter<HistogramType>;

  auto filter = HistogramToTextureFeaturesFilterType::New();

  std::cout << filter->GetNameOfClass() << std::endl;
  filter->Print(std::cout);

  // Invoke update before adding an input. An exception should be
  // thrown.
  EXPECT_THROW(filter->Update(), itk::ExceptionObject);

  EXPECT_EQ(filter->GetInput(), nullptr);

  filter->ResetPipeline();

  filter->SetInput(histogram);
  ASSERT_NO_THROW(filter->Update());

  constexpr double trueEnergy{ 0.295 };
  constexpr double trueEntropy{ 2.26096 };
  constexpr double trueCorrelation{ 0.12819 };
  constexpr double trueInverseDifferenceMoment{ 0.85 };
  constexpr double trueInertia{ 0.3 };
  constexpr double trueClusterShade{ 139.1879 };
  constexpr double trueClusterProminence{ 2732.557 };
  constexpr double trueHaralickCorrelation{ 2264.549 };

  const double energy = filter->GetEnergy();
  const double entropy = filter->GetEntropy();
  const double correlation = filter->GetCorrelation();
  const double inverseDifferenceMoment = filter->GetInverseDifferenceMoment();
  const double inertia = filter->GetInertia();
  const double clusterShade = filter->GetClusterShade();
  const double clusterProminence = filter->GetClusterProminence();
  const double haralickCorrelation = filter->GetHaralickCorrelation();


  EXPECT_NEAR(energy, trueEnergy, 0.001) << "Energy calculated wrong";

  EXPECT_NEAR(entropy, trueEntropy, 0.001) << "Entropy calculated wrong";

  EXPECT_NEAR(correlation, trueCorrelation, 0.001) << "Correlation calculated wrong";

  EXPECT_NEAR(inverseDifferenceMoment, trueInverseDifferenceMoment, 0.001)
    << "InverseDifferenceMoment calculated wrong";

  EXPECT_NEAR(inertia, trueInertia, 0.001) << "Inertia calculated wrong";

  EXPECT_NEAR(clusterShade, trueClusterShade, 0.001) << "ClusterShade calculated wrong";

  EXPECT_NEAR(clusterProminence, trueClusterProminence, 0.001) << "ClusterProminence calculated wrong";

  EXPECT_NEAR(haralickCorrelation, trueHaralickCorrelation, 0.001) << "Haralick's Correlation calculated wrong";

  // Get the texture features using GetFeature() method
  const double energy2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Energy);

  const double entropy2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Entropy);

  const double correlation2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Correlation);

  const double inverseDifferenceMoment2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::InverseDifferenceMoment);

  const double inertia2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Inertia);

  const double clusterShade2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterShade);

  const double clusterProminence2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterProminence);

  const double haralickCorrelation2 =
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::HaralickCorrelation);

  EXPECT_NEAR(energy2, trueEnergy, 0.001) << "Energy calculated wrong";

  EXPECT_NEAR(entropy2, trueEntropy, 0.001) << "Entropy calculated wrong";

  EXPECT_NEAR(correlation2, trueCorrelation, 0.001) << "Correlation calculated wrong";

  EXPECT_NEAR(inverseDifferenceMoment2, trueInverseDifferenceMoment, 0.001)
    << "InverseDifferenceMoment calculated wrong";

  EXPECT_NEAR(inertia2, trueInertia, 0.001) << "Inertia calculated wrong";

  EXPECT_NEAR(clusterShade2, trueClusterShade, 0.001) << "ClusterShade calculated wrong";

  EXPECT_NEAR(clusterProminence2, trueClusterProminence, 0.001) << "ClusterProminence calculated wrong";

  EXPECT_NEAR(haralickCorrelation2, trueHaralickCorrelation, 0.001) << "Haralick's Correlation calculated wrong";

  // Test inquiry for invalid feature

  EXPECT_EQ(
    filter->GetFeature(itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::InvalidFeatureName), 0.0)
    << "GetFeature() is returning non-zero feature value: "
    << "for invalid feature request";

  // Test streaming enumeration for HistogramToTextureFeaturesFilterEnums::TextureFeature elements
  const std::set<itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature> allTextureFeature{
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Energy,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Entropy,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Correlation,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::InverseDifferenceMoment,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::Inertia,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterShade,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::ClusterProminence,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::HaralickCorrelation,
    itk::Statistics::HistogramToTextureFeaturesFilterEnums::TextureFeature::InvalidFeatureName
  };
  for (const auto & ee : allTextureFeature)
  {
    std::cout << "STREAMED ENUM VALUE HistogramToTextureFeaturesFilterEnums::TextureFeature: " << ee << std::endl;
  }
}
