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

#include "itkHeldIsotropicWavelet.h"
#include "itkGTest.h"

#include <string>

TEST(HeldIsotropicWavelet, ConvertedLegacyTest)
{
  using Double = double;
  using Float = float;

  constexpr unsigned int D3 = 3;
  constexpr unsigned int D2 = 2;
  constexpr unsigned int D1 = 1;

  using Default = itk::HeldIsotropicWavelet<>;
  Default::New();

  using Point3D = itk::Point<itk::SpacePrecisionType, D3>;
  using Point2D = itk::Point<itk::SpacePrecisionType, D2>;
  using Point1D = itk::Point<itk::SpacePrecisionType, D1>;

  using Wavelet3D = itk::HeldIsotropicWavelet<Double, D3, Point3D>;
  using Wavelet2D = itk::HeldIsotropicWavelet<Double, D2, Point2D>;
  using Wavelet1D = itk::HeldIsotropicWavelet<Double, D1, Point1D>;
  Wavelet3D::New();
  Wavelet2D::New();
  Wavelet1D::New();

  using Wavelet3DFloat = itk::HeldIsotropicWavelet<Float, D3, Point3D>;
  using Wavelet2DFloat = itk::HeldIsotropicWavelet<Float, D2, Point2D>;
  using Wavelet1DFloat = itk::HeldIsotropicWavelet<Float, D1, Point1D>;
  Wavelet3DFloat::New();
  Wavelet2DFloat::New();
  Wavelet1DFloat::New();

  auto wavelet2Dfloat = Wavelet2DFloat::New();

  ITK_GTEST_EXERCISE_BASIC_OBJECT_METHODS(wavelet2Dfloat, HeldIsotropicWavelet, IsotropicWaveletFrequencyFunction);

  Point2D point2D;
  point2D[0] = 0.2;
  point2D[1] = 0.2;
  double freq2D = wavelet2Dfloat->Magnitude(point2D);
  std::cout << "freq2D: " << freq2D << std::endl;
  // Check that inherits from IsotropicFrequencyFunction
  unsigned int defaultBands = wavelet2Dfloat->GetHighPassSubBands();
  EXPECT_EQ(defaultBands, 1u);

  // Specific methods for this type:
  unsigned int maxPolynomialOrder = 5;
  for (unsigned int p = 0; p < maxPolynomialOrder + 1; ++p)
  {
    wavelet2Dfloat->SetPolynomialOrder(p);
    EXPECT_EQ(p, wavelet2Dfloat->GetPolynomialOrder());
    Wavelet2DFloat::FunctionValueType value = wavelet2Dfloat->EvaluateMagnitude(freq2D);
    std::cout << "Order: " << p << "; Evaluate: " << value << std::endl;
  }


  // Test exception cases
  unsigned int polynomialOrder = 6;
  wavelet2Dfloat->SetPolynomialOrder(polynomialOrder);
  EXPECT_EQ(polynomialOrder, wavelet2Dfloat->GetPolynomialOrder());

  EXPECT_THROW(wavelet2Dfloat->EvaluateMagnitude(freq2D), itk::ExceptionObject);
}
