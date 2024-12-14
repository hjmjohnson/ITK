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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkTestingMacros.h"

// Specific ImageIO test

int
itkImageIODirection3DTest(int argc, char * argv[])
{

  if (argc < 11)
  {
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " InputImage  (9 direction cosines terms) "
              << "[outputImage]" << '\n';
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 3;
  using PixelType = unsigned char;

  using ImageType = itk::Image<PixelType, Dimension>;
  using ReaderType = itk::ImageFileReader<ImageType>;

  auto reader = ReaderType::New();

  reader->SetFileName(argv[1]);

  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << e << '\n';
    return EXIT_FAILURE;
  }

  const ImageType::ConstPointer image = reader->GetOutput();

  ImageType::DirectionType directionCosines = image->GetDirection();

  std::cout << directionCosines << '\n';

  unsigned int element = 2;
  const double tolerance = 1e-5;

  for (unsigned int row = 0; row < Dimension; ++row)
  {
    for (unsigned int col = 0; col < Dimension; ++col)
    {
      const double expectedValue = std::stod(argv[element++]);
      const double currentValue = directionCosines[row][col];
      const double difference = currentValue - expectedValue;
      if (itk::Math::abs(difference) > tolerance)
      {
        std::cerr << "Error: " << '\n';
        std::cerr << "Expected " << expectedValue << '\n';
        std::cerr << "Read     " << currentValue << '\n';
        return EXIT_FAILURE;
      }
    }
  }


  if (argc > 11)
  {
    using WriterType = itk::ImageFileWriter<ImageType>;
    auto writer = WriterType::New();
    writer->SetFileName(argv[11]);
    writer->SetInput(reader->GetOutput());

    try
    {
      writer->Update();
    }
    catch (const itk::ExceptionObject & e)
    {
      std::cerr << e << '\n';
      return EXIT_FAILURE;
    }
  }


  return EXIT_SUCCESS;
}
