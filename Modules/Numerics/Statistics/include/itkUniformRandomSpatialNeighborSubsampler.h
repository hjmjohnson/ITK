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
#ifndef itkUniformRandomSpatialNeighborSubsampler_h
#define itkUniformRandomSpatialNeighborSubsampler_h

#include "itkSpatialNeighborSubsampler.h"
#include "itkMersenneTwisterRandomVariateGenerator.h"

namespace itk::Statistics
{
/**
 * \class UniformRandomSpatialNeighborSubsampler
 * \brief A subsampler that uniformly randomly selects points
 * within the specified radius of the query point.
 *
 * This class derives from SpatialNeighborSubsampler and
 * randomly selects points according to a uniform distribution
 * within the Radius given by SetRadius(radius)
 * as long as that point is also within the RegionConstraint.
 *
 * This class assumes that the instance identifiers in the input
 * sample correspond to the result of ComputeOffset() of the index
 * of the corresponding point in the image region.
 *
 * \sa SubsamplerBase, RegionConstrainedSubsampler
 * \sa SpatialNeighborSubsampler
 * \sa GaussianRandomSpatialNeighborSubsampler
 * \ingroup ITKStatistics
 */

template <typename TSample, typename TRegion>
class ITK_TEMPLATE_EXPORT UniformRandomSpatialNeighborSubsampler : public SpatialNeighborSubsampler<TSample, TRegion>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(UniformRandomSpatialNeighborSubsampler);

  /** Standard class type aliases */
  using Self = UniformRandomSpatialNeighborSubsampler<TSample, TRegion>;
  using Superclass = SpatialNeighborSubsampler<TSample, TRegion>;
  using Baseclass = typename Superclass::Baseclass;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(UniformRandomSpatialNeighborSubsampler);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** type alias alias for the source data container */
  using typename Superclass::SampleType;
  using typename Superclass::SampleConstPointer;
  using typename Superclass::MeasurementVectorType;
  using typename Superclass::InstanceIdentifier;

  using typename Superclass::SubsampleType;
  using typename Superclass::SubsamplePointer;
  using typename Superclass::SubsampleConstIterator;
  using typename Superclass::InstanceIdentifierHolder;
  using SeedType = typename Baseclass::SeedType;

  using SearchSizeType = unsigned long;
  using RandomIntType = unsigned int;

  /** type alias related to image region */
  using typename Superclass::RadiusType;
  using typename Superclass::RegionType;
  using typename Superclass::IndexType;
  using typename Superclass::IndexValueType;
  using typename Superclass::SizeType;
  using typename Superclass::ImageHelperType;


  /** type alias related to random variate generator */
  using RandomGeneratorType = Statistics::MersenneTwisterRandomVariateGenerator;

  void
  SetSeed(const SeedType seed) override
  {
    Superclass::SetSeed(seed);
    this->m_RandomNumberGenerator->SetSeed(this->m_Seed);
  }

  virtual void
  SetUseClockForSeed(const bool & useClock)
  {
    if (useClock != this->m_UseClockForSeed)
    {
      this->m_UseClockForSeed = useClock;
      if (this->m_UseClockForSeed)
      {
        this->m_RandomNumberGenerator->SetSeed();
      }
      this->Modified();
    }
  }

  itkBooleanMacro(UseClockForSeed);
  itkGetConstMacro(UseClockForSeed, bool);

  virtual void
  SetNumberOfResultsRequested(const SearchSizeType & numberRequested)
  {
    itkDebugMacro("setting NumberOfResultsRequested to " << numberRequested);
    if (this->m_RequestMaximumNumberOfResults || this->m_NumberOfResultsRequested != numberRequested)
    {
      this->m_NumberOfResultsRequested = numberRequested;
      this->m_RequestMaximumNumberOfResults = false;
      this->Modified();
    }
  }
  itkGetConstMacro(NumberOfResultsRequested, SearchSizeType);

  /** Main Search method that MUST be implemented by each subclass
   * The Search method will find all points similar to query and return
   * them as a Subsample.  The definition of similar will be subclass-
   * specific.  And could mean spatial similarity or feature similarity
   * etc.  */
  void
  Search(const InstanceIdentifier & query, SubsamplePointer & results) override;

protected:
  /**
   * Clone the current subsampler.
   * This does a complete copy of the subsampler state
   * to the new subsampler
   */
  [[nodiscard]] typename LightObject::Pointer
  InternalClone() const override;

  UniformRandomSpatialNeighborSubsampler();
  ~UniformRandomSpatialNeighborSubsampler() override = default;

  void
  PrintSelf(std::ostream & os, Indent indent) const override;

  /** method to randomly generate an integer in the closed range
   * [lowerBound, upperBound]
   * using a uniform sampling selection method.
   * override this method to do gaussian selection */
  virtual RandomIntType
  GetIntegerVariate(RandomIntType lowerBound, RandomIntType upperBound, RandomIntType itkNotUsed(mean));

  SearchSizeType               m_NumberOfResultsRequested{};
  RandomGeneratorType::Pointer m_RandomNumberGenerator{};
  bool                         m_UseClockForSeed{};
}; // end of class UniformRandomSpatialNeighborSubsampler

} // namespace itk::Statistics

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkUniformRandomSpatialNeighborSubsampler.hxx"
#endif

#endif
