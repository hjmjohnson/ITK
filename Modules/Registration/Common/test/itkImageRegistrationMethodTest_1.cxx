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

#include "itkImageRegistrationMethod.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkGradientDescentOptimizer.h"

#include "itkImageRegistrationMethodImageSource.h"
#include "itkTestingMacros.h"

/**
 *  This program tests one instantiation of the itk::ImageRegistrationMethod class
 *
 *
 */

int
itkImageRegistrationMethodTest_1(int argc, char * argv[])
{

  bool pass = true;

  constexpr unsigned int Dimension = 2;
  using PixelType = float;

  // Fixed Image Type
  using FixedImageType = itk::Image<PixelType, Dimension>;

  // Moving Image Type
  using MovingImageType = itk::Image<PixelType, Dimension>;

  // Size Type
  using SizeType = MovingImageType::SizeType;


  // ImageSource
  using ImageSourceType = itk::testhelper::
    ImageRegistrationMethodImageSource<FixedImageType::PixelType, MovingImageType::PixelType, Dimension>;
  // Transform Type
  using TransformType = itk::AffineTransform<double, Dimension>;
  using ParametersType = TransformType::ParametersType;

  // Optimizer Type
  using OptimizerType = itk::GradientDescentOptimizer;

  // Metric Type
  using MetricType = itk::MeanSquaresImageToImageMetric<FixedImageType, MovingImageType>;

  // Interpolation technique
  using InterpolatorType = itk::LinearInterpolateImageFunction<MovingImageType, double>;

  // Registration Method
  using RegistrationType = itk::ImageRegistrationMethod<FixedImageType, MovingImageType>;

  using CommandIterationType = itk::CommandIterationUpdate<OptimizerType>;


  auto metric = MetricType::New();
  auto transform = TransformType::New();
  auto optimizer = OptimizerType::New();
  auto interpolator = InterpolatorType::New();
  auto registration = RegistrationType::New();

  auto imageSource = ImageSourceType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(imageSource, ImageRegistrationMethodImageSource, Object);


  SizeType size;
  size[0] = 100;
  size[1] = 100;

  imageSource->GenerateImages(size);

  const FixedImageType::ConstPointer  fixedImage = imageSource->GetFixedImage();
  const MovingImageType::ConstPointer movingImage = imageSource->GetMovingImage();

  //
  // Connect all the components required for Registratio
  //
  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetTransform(transform);
  registration->SetFixedImage(fixedImage);
  registration->SetMovingImage(movingImage);
  registration->SetInterpolator(interpolator);


  // Select the Region of Interest over which the Metric will be computed
  // Registration time will be proportional to the number of pixels in this region.
  metric->SetFixedImageRegion(fixedImage->GetBufferedRegion());

  // Instantiate an Observer to report the progress of the Optimization
  auto iterationCommand = CommandIterationType::New();
  iterationCommand->SetOptimizer(optimizer);

  // Scale the translation components of the Transform in the Optimizer
  OptimizerType::ScalesType scales(transform->GetNumberOfParameters());
  scales.Fill(1.0);


  unsigned long numberOfIterations = 100;
  double        translationScale = 1e-6;
  double        learningRate = 1e-8;

  if (argc > 1)
  {
    numberOfIterations = atol(argv[1]);
    std::cout << "numberOfIterations = " << numberOfIterations << std::endl;
  }
  if (argc > 2)
  {
    translationScale = std::stod(argv[2]);
    std::cout << "translationScale = " << translationScale << std::endl;
  }
  if (argc > 3)
  {
    learningRate = std::stod(argv[3]);
    std::cout << "learningRate = " << learningRate << std::endl;
  }

  for (unsigned int i = 0; i < Dimension; ++i)
  {
    scales[i + Dimension * Dimension] = translationScale;
  }

  optimizer->SetScales(scales);
  optimizer->SetLearningRate(learningRate);
  optimizer->SetNumberOfIterations(numberOfIterations);
  optimizer->MinimizeOn();

  // Start from an Identity transform (in a normal case, the user
  // can probably provide a better guess than the identity...
  transform->SetIdentity();
  registration->SetInitialTransformParameters(transform->GetParameters());

  // Initialize the internal connections of the registration method.
  // This can potentially throw an exception
  try
  {
    registration->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << e << std::endl;
    pass = false;
  }

  ParametersType actualParameters = imageSource->GetActualParameters();
  ParametersType finalParameters = registration->GetLastTransformParameters();

  const unsigned int numbeOfParameters = actualParameters.Size();

  // We know that for the Affine transform the Translation parameters are at
  // the end of the list of parameters.
  const unsigned int offsetOrder = finalParameters.Size() - actualParameters.Size();

  constexpr double tolerance = 1.0; // equivalent to 1 pixel.

  for (unsigned int i = 0; i < numbeOfParameters; ++i)
  {
    // the parameters are negated in order to get the inverse transformation.
    // this only works for comparing translation parameters....
    std::cout << finalParameters[i + offsetOrder] << " == " << -actualParameters[i] << std::endl;
    if (itk::Math::abs(finalParameters[i + offsetOrder] - (-actualParameters[i])) > tolerance)
    {
      std::cout << "Tolerance exceeded at component " << i << std::endl;
      pass = false;
    }
  }

  //
  //  Get the transform as the Output of the Registration filter
  //
  const RegistrationType::TransformOutputConstPointer transformDecorator = registration->GetOutput();

  const TransformType::ConstPointer finalTransform = static_cast<const TransformType *>(transformDecorator->Get());


  if (!pass)
  {
    std::cout << "Test FAILED." << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Test PASSED." << std::endl;
  return EXIT_SUCCESS;
}
