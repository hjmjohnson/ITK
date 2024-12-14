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

#include "itkPCAShapeSignedDistanceFunction.h"

#include "vnl/vnl_sample.h"
#include "itkImageRegionIterator.h"
#include "itkEuler2DTransform.h"


/**
 * This module tests the functionality of the PCAShapeSignedDistanceFunction
 * class.
 *
 * The mean image, principal component images, standard deviations, and
 * and weighting parameters are randomly generated. The signed distance is
 * evaluated at all image points and compared to expected values.
 * The test fails if the evaluated results is not within a certain tolerance
 * of the expected results.
 */
int
itkPCAShapeSignedDistanceFunctionTest(int, char *[])
{
  unsigned int i;
  using CoordRep = double;
  constexpr unsigned int Dimension = 2;
  constexpr unsigned int ImageWidth = 3;
  constexpr unsigned int ImageHeight = 2;
  constexpr unsigned int NumberOfPCs = 3;


  // define a pca shape function
  using ShapeFunction = itk::PCAShapeSignedDistanceFunction<CoordRep, Dimension>;
  auto shape = ShapeFunction::New();
  //  shape->DebugOn();
  shape->SetNumberOfPrincipalComponents(NumberOfPCs);


  // set up the transform
  using transformType = itk::Euler2DTransform<double>;
  auto transform = transformType::New();
  shape->SetTransform(transform);


  // prepare for image creation
  using ImageType = ShapeFunction::ImageType;

  const ImageType::SizeType imageSize = { { ImageWidth, ImageHeight } };

  const ImageType::IndexType startIndex{};

  const ImageType::RegionType region{ startIndex, imageSize };


  // set up the random number generator
  vnl_sample_reseed();
  ImageType::PixelType randomPixel;


  // set up the mean image
  auto meanImage = ImageType::New();
  meanImage->SetRegions(region);
  meanImage->Allocate();

  using ImageIterator = itk::ImageRegionIterator<ImageType>;
  ImageIterator meanImageIt(meanImage, meanImage->GetBufferedRegion());

  for (meanImageIt.GoToBegin(); !meanImageIt.IsAtEnd(); ++meanImageIt)
  {
    randomPixel = vnl_sample_normal(0, 1);
    meanImageIt.Set(randomPixel);
  }

  shape->SetMeanImage(meanImage);


  // set up the NumberOfPCs principal component images
  ShapeFunction::ImagePointerVector pcImages(NumberOfPCs);
  using ImageIteratorVector = std::vector<ImageIterator>;
  ImageIteratorVector pcImageIts(NumberOfPCs);

  for (i = 0; i < NumberOfPCs; ++i)
  {
    pcImages[i] = ImageType::New();
    pcImages[i]->SetRegions(region);
    pcImages[i]->Allocate();

    pcImageIts[i] = ImageIterator(pcImages[i], pcImages[i]->GetBufferedRegion());

    for (pcImageIts[i].GoToBegin(); !pcImageIts[i].IsAtEnd(); ++pcImageIts[i])
    {
      randomPixel = vnl_sample_normal(0, 1);
      pcImageIts[i].Set(randomPixel);
    }
  }

  shape->SetPrincipalComponentImages(pcImages);


  // set up the standard deviation for each principal component images
  ShapeFunction::ParametersType pcStandardDeviations(NumberOfPCs);

  for (i = 0; i < NumberOfPCs; ++i)
  {
    pcStandardDeviations[i] = vnl_sample_normal(0, 1);
  }

  shape->SetPrincipalComponentStandardDeviations(pcStandardDeviations);


  // set up the parameters
  const unsigned int            numberOfShapeParameters = shape->GetNumberOfShapeParameters();
  const unsigned int            numberOfPoseParameters = shape->GetNumberOfPoseParameters();
  const unsigned int            numberOfParameters = numberOfShapeParameters + numberOfPoseParameters;
  ShapeFunction::ParametersType parameters(numberOfParameters);

  for (i = 0; i < numberOfParameters; ++i)
  {
    parameters[i] = vnl_sample_normal(0, 1);
  }

  shape->SetParameters(parameters);


  // we must initialize the function before use
  shape->Initialize();

  // check pca shape calculation
  ShapeFunction::PointType  point;
  ImageType::IndexType      index;
  ShapeFunction::OutputType output;
  ShapeFunction::OutputType expected;

  std::cout << "check results:" << '\n';
  const unsigned int numberOfRotationParameters = Dimension * (Dimension - 1) / 2;
  const unsigned int startIndexOfTranslationParameters = numberOfShapeParameters + numberOfRotationParameters;

  ShapeFunction::TransformType::InputPointType p;
  ShapeFunction::TransformType::InputPointType q;

  for (meanImageIt.GoToBegin(); !meanImageIt.IsAtEnd(); ++meanImageIt)
  {
    // from index to physical point
    index = meanImageIt.GetIndex();
    meanImage->TransformIndexToPhysicalPoint(index, point);

    // inverse Euler2DTransform: first translation then rotation
    p[0] = point[0] - parameters[startIndexOfTranslationParameters];
    p[1] = point[1] - parameters[startIndexOfTranslationParameters + 1];

    const double angle = parameters[numberOfShapeParameters];
    q[0] = p[0] * std::cos(-angle) - p[1] * std::sin(-angle);
    q[1] = p[0] * std::sin(-angle) + p[1] * std::cos(-angle);

    // evaluate shape function
    output = shape->Evaluate(q);

    // calculate expected function value
    expected = meanImage->GetPixel(index);
    for (i = 0; i < NumberOfPCs; ++i)
    {
      expected += pcImages[i]->GetPixel(index) * pcStandardDeviations[i] * parameters[i];
    }

    // check result
    std::cout << "f(" << point << ") = " << output << '\n';

    if (itk::Math::abs(output - expected) > 1e-9)
    {
      std::cout << "But expected value is: " << expected << '\n';
      return EXIT_FAILURE;
    }
  }

  // Evaluate at a point outside the image domain
  std::cout << "Evaluate at point outside image domain" << '\n';
  q.Fill(5.0);
  output = shape->Evaluate(q);
  std::cout << "f(" << q << ") = " << output << '\n';

  // Exercise other methods for test coverage
  shape->Print(std::cout);

  std::cout << "NumberOfPrincipalComponents: " << shape->GetNumberOfPrincipalComponents() << '\n';
  std::cout << "MeanImage: " << shape->GetMeanImage() << '\n';
  std::cout << "PrincipalComponentStandardDeviations: " << shape->GetPrincipalComponentStandardDeviations() << '\n';
  std::cout << "Transform: " << shape->GetTransform() << '\n';
  std::cout << "Parameters: " << shape->GetParameters() << '\n';

  // Exercise error testing
  bool pass;

#define TEST_INITIALIZATION_ERROR(ComponentName, badComponent, goodComponent) \
  shape->Set##ComponentName(badComponent);                                    \
  try                                                                         \
  {                                                                           \
    pass = false;                                                             \
    shape->Initialize();                                                      \
  }                                                                           \
  catch (const itk::ExceptionObject & err)                                    \
  {                                                                           \
    std::cout << "Caught expected ExceptionObject" << '\n';                   \
    std::cout << err << '\n';                                                 \
    pass = true;                                                              \
  }                                                                           \
  shape->Set##ComponentName(goodComponent);                                   \
                                                                              \
  if (!pass)                                                                  \
  {                                                                           \
    std::cout << "Test failed." << '\n';                                      \
    return EXIT_FAILURE;                                                      \
  }                                                                           \
  ITK_MACROEND_NOOP_STATEMENT

  // nullptr MeanImage
  TEST_INITIALIZATION_ERROR(MeanImage, nullptr, meanImage);

  // Wrong number of PC images
  ShapeFunction::ImagePointerVector badPCImages;
  badPCImages.resize(1);
  badPCImages[0] = nullptr;

  TEST_INITIALIZATION_ERROR(PrincipalComponentImages, badPCImages, pcImages);

  // A nullptr PC image
  badPCImages = pcImages;
  badPCImages[1] = nullptr;

  TEST_INITIALIZATION_ERROR(PrincipalComponentImages, badPCImages, pcImages);

  // A PC image of the wrong size
  auto                        badSize = ImageType::SizeType::Filled(1);
  const ImageType::RegionType badRegion(badSize);
  badPCImages[1] = ImageType::New();
  badPCImages[1]->SetRegions(badRegion);
  badPCImages[1]->Allocate();
  badPCImages[1]->FillBuffer(0.0);

  TEST_INITIALIZATION_ERROR(PrincipalComponentImages, badPCImages, pcImages);

  std::cout << "Test passed. " << '\n';
  return EXIT_SUCCESS;
}
