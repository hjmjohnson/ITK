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
#ifndef itkGaussianRandomSpatialNeighborSubsampler_hxx
#define itkGaussianRandomSpatialNeighborSubsampler_hxx

namespace itk::Statistics
{

template <typename TSample, typename TRegion>
GaussianRandomSpatialNeighborSubsampler<TSample, TRegion>::GaussianRandomSpatialNeighborSubsampler()
  : m_Variance(DefaultVariance)
{}

template <typename TSample, typename TRegion>
typename LightObject::Pointer
GaussianRandomSpatialNeighborSubsampler<TSample, TRegion>::InternalClone() const
{
  typename LightObject::Pointer loPtr = Superclass::InternalClone();

  const typename Self::Pointer rval = dynamic_cast<Self *>(loPtr.GetPointer());
  if (rval.IsNull())
  {
    itkExceptionMacro("downcast to type " << this->GetNameOfClass() << " failed.");
  }

  rval->m_Variance = this->m_Variance;
  return loPtr;
}

template <typename TSample, typename TRegion>
auto
GaussianRandomSpatialNeighborSubsampler<TSample, TRegion>::GetIntegerVariate(RandomIntType lowerBound,
                                                                             RandomIntType upperBound,
                                                                             RandomIntType mean) -> RandomIntType
{
  if (upperBound < lowerBound)
  {
    itkExceptionMacro("upperBound (" << upperBound << ") not >= to lowerBound(" << lowerBound << ')');
  }

  RandomIntType randInt = 0;

  do
  {
    const RealType randVar = this->m_RandomNumberGenerator->GetNormalVariate(mean, m_Variance);
    randInt = static_cast<RandomIntType>(std::floor(randVar));
  } while ((randInt < lowerBound) || (randInt > upperBound));
  return randInt;
}

template <typename TSample, typename TRegion>
void
GaussianRandomSpatialNeighborSubsampler<TSample, TRegion>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Gaussian variance: " << m_Variance << std::endl;
  os << std::endl;
}

} // namespace itk::Statistics

#endif
