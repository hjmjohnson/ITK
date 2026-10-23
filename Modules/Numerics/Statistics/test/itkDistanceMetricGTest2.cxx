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

#include "itkDistanceMetric.h"
#include "itkGTest.h"

namespace
{

template <typename TMeasurementVector>
class MyDistanceMetric : public itk::Statistics::DistanceMetric<TMeasurementVector>
{
public:
  /** Standard class type alias. */
  using Self = MyDistanceMetric;
  using Superclass = itk::Statistics::DistanceMetric<TMeasurementVector>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  /** \see LightObject::GetNameOfClass() */
  itkOverrideGetNameOfClassMacro(MyDistanceMetric);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Evaluate membership score */
  double
  Evaluate(const TMeasurementVector &) const override
  {
    constexpr double score{ 1 };
    return score;
  }

  double
  Evaluate(const TMeasurementVector &, const TMeasurementVector &) const override
  {
    constexpr double score{ 1 };
    return score;
  }
};

} // namespace


// test DistanceMetric using resizable measurement vector type
TEST(DistanceMetric, ConvertedLegacyTest2)
{

  using MeasurementVectorType = itk::Array<float>;


  using DistanceMetricType = MyDistanceMetric<MeasurementVectorType>;

  using MeasurementVectorSizeType = DistanceMetricType::MeasurementVectorSizeType;

  auto distance = DistanceMetricType::New();

  std::cout << distance->GetNameOfClass() << std::endl;
  std::cout << distance->DistanceMetricType::Superclass::GetNameOfClass() << std::endl;

  distance->Print(std::cout);

  constexpr MeasurementVectorSizeType measurementVectorSize{ 3 };
  distance->SetMeasurementVectorSize(measurementVectorSize);

  EXPECT_EQ(distance->GetMeasurementVectorSize(), measurementVectorSize) << "Error in Set/GetMeasurementVectorSize()";

  // try re-setting the measurement vector size to the same value, no exceptions should be
  // thrown
  {
    constexpr MeasurementVectorSizeType sameSize{ 3 };
    EXPECT_NO_THROW(distance->SetMeasurementVectorSize(sameSize));
  }


  // try setting an origin vector with a different size it should throw an exception
  {
    DistanceMetricType::OriginType      origin;
    constexpr MeasurementVectorSizeType newSize{ 4 };
    origin.SetSize(newSize);
    EXPECT_THROW(distance->SetOrigin(origin), itk::ExceptionObject)
      << "Attempting to set an origin vector with a different size,"
      << "should result in an exception";
  }
}
