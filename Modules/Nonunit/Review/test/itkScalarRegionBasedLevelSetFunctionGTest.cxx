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

#include "itkScalarRegionBasedLevelSetFunction.h"
#include "itkGTest.h"

namespace
{

template <typename TInput,   // LevelSetImageType
          typename TFeature, // FeatureImageType
          typename TSharedData>
class ScalarRegionBasedLevelSetFunctionTestHelper
  : public itk::ScalarRegionBasedLevelSetFunction<TInput, TFeature, TSharedData>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ScalarRegionBasedLevelSetFunctionTestHelper);

  /** Standard class type aliases. */
  using Self = ScalarRegionBasedLevelSetFunctionTestHelper;
  using Superclass = itk::ScalarRegionBasedLevelSetFunction<TInput, TFeature, TSharedData>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  static constexpr unsigned int ImageDimension = Superclass::ImageDimension;

  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ScalarRegionBasedLevelSetFunctionTestHelper);

  using typename Superclass::ScalarValueType;
  using typename Superclass::FeaturePixelType;
  using typename Superclass::FeatureIndexType;

  ScalarValueType
  ComputeInternalTerm(const FeaturePixelType &, const FeatureIndexType &) override
  {
    return ScalarValueType(0);
  }

  ScalarValueType
  ComputeExternalTerm(const FeaturePixelType &, const FeatureIndexType &) override
  {
    return ScalarValueType(0);
  }

  ScalarValueType
  ComputeOverlapParameters(const FeatureIndexType &, ScalarValueType &) override
  {
    return ScalarValueType(0);
  }

  void
  ComputeParameters() override
  {}

  void
  UpdateSharedDataParameters() override
  {}

  void
  UpdateSharedDataInsideParameters(const unsigned int &, const FeaturePixelType &, const ScalarValueType &) override
  {}

  void
  UpdateSharedDataOutsideParameters(const unsigned int &, const FeaturePixelType &, const ScalarValueType &) override
  {}

protected:
  ScalarRegionBasedLevelSetFunctionTestHelper() = default;
  ~ScalarRegionBasedLevelSetFunctionTestHelper() override = default;
};

template <unsigned int VDimension>
class ScalarRegionBasedLevelSetFunctionSharedDataHelper : public itk::DataObject
{
public:
  /** Standard class type aliases. */
  using Self = ScalarRegionBasedLevelSetFunctionSharedDataHelper;
  using Superclass = itk::DataObject;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  itkNewMacro(Self);

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(ScalarRegionBasedLevelSetFunctionSharedDataHelper);

  unsigned long m_FunctionCount;

  using IndexType = itk::Index<VDimension>;
  using ListPixelType = std::list<unsigned int>;

  using ImageType = itk::Image<ListPixelType, VDimension>;
  typename ImageType::Pointer m_NearestNeighborListImage;

  using PixelType = double;
  using InputImageType = itk::Image<PixelType, VDimension>;

  struct SingleData
  {
    typename InputImageType::Pointer m_HeavisideFunctionOfLevelSetImage;
    int                              m_WeightedNumberOfPixelsInsideLevelSet;
    int                              m_WeightedSumOfPixelValuesInsideLevelSet;
    int                              m_ForegroundConstantValues;

    int m_WeightedNumberOfPixelsOutsideLevelSet;
    int m_WeightedSumOfPixelValuesOutsideLevelSet;
    int m_BackgroundConstantValues;

    IndexType
    GetFeatureIndex(const IndexType & indx)
    {
      return indx;
    }

    IndexType
    GetIndex(const IndexType & globalIndex)
    {
      return globalIndex;
    }
  };

  SingleData * m_LevelSetDataPointerVector[19];
};

} // namespace

TEST(ScalarRegionBasedLevelSetFunction, ConvertedLegacyTest)
{
  constexpr unsigned int Dimension{ 3 };

  using PixelType = double;
  using ImageType = itk::Image<PixelType, Dimension>;
  using FeatureImageType = itk::Image<float, Dimension>;

  using DataHelperType = ScalarRegionBasedLevelSetFunctionSharedDataHelper<Dimension>;

  using RegionBasedLevelSetFunctionType =
    ScalarRegionBasedLevelSetFunctionTestHelper<ImageType, FeatureImageType, DataHelperType>;

  auto function = RegionBasedLevelSetFunctionType::New();
  EXPECT_FALSE(function.IsNull());
}
