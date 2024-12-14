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

#include "itkBMPImageIO.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionConstIterator.h"
#include "itkMetaDataDictionary.h"
#include "itkTestingMacros.h"
#include <fstream>

// Specific ImageIO test

int
itkBMPImageIOTestPalette(int argc, char * argv[])
{
  if (argc != 5)
  {
    std::cerr << "Missing parameters." << '\n';
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv);
    std::cerr << " input"
              << " output"
              << " expandRGBPalette"
              << " isPaletteImage" << '\n';
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;
  using ScalarPixelType = unsigned char;

  using ScalarImageType = itk::Image<ScalarPixelType, Dimension>;
  using ReaderType = itk::ImageFileReader<ScalarImageType>;
  using WriterType = itk::ImageFileWriter<ScalarImageType>;
  using IOType = itk::BMPImageIO;

  auto io = IOType::New();

  auto reader = ReaderType::New();
  auto writer = WriterType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(io, BMPImageIO, ImageIOBase);

  const auto expandRGBPalette = static_cast<bool>(std::stoi(argv[3]));
  const auto isPaletteImage = static_cast<bool>(std::stoi(argv[4]));
  ITK_TEST_SET_GET_BOOLEAN(io, ExpandRGBPalette, expandRGBPalette);

  // Exercise exception cases
  const size_t sizeOfActualIORegion =
    io->GetIORegion().GetNumberOfPixels() * (io->GetComponentSize() * io->GetNumberOfComponents());
  auto * loadBuffer = new char[sizeOfActualIORegion];

  ITK_TRY_EXPECT_EXCEPTION(io->Read(loadBuffer));


  io->SetFileName(argv[1]);
  reader->SetImageIO(io);
  reader->SetFileName(io->GetFileName());

  if (io->CanReadFile(""))
  {
    std::cerr << "Test failed!" << '\n';
    std::cout << "No filename specified." << '\n';
    std::cout << "CanReadFile: "
              << "Expected false but got true" << '\n';
    return EXIT_FAILURE;
  }

  if (!io->SupportsDimension(Dimension))
  {
    std::cerr << "Test failed!" << '\n';
    std::cerr << "itk::BMPImageIO does not support dimension: " << Dimension << '\n';
    return EXIT_FAILURE;
  }

  if (io->CanStreamRead())
  {
    std::cout << "itk::BMPImageIO can stream read" << '\n';
  }
  else
  {
    std::cout << "itk::BMPImageIO cannot stream read" << '\n';
  }

  if (!io->CanReadFile(argv[1]))
  {
    std::cerr << "Test failed!" << '\n';
    std::cout << "itk::BMPImageIO cannot read file " << argv[1] << '\n';
    return EXIT_FAILURE;
  }


  // Try reading
  ITK_TRY_EXPECT_NO_EXCEPTION(reader->Update());


  // Try Palette reading and scalar image reading
  if (io->GetExpandRGBPalette())
  {
    if (isPaletteImage)
    {
      std::cout << "Input is a defined as palette image, expanding to RGB. " << '\n';
    }
    else
    {
      std::cout << "Input is a defined as a non palette image. " << '\n';
    }
  }
  else
  {
    if (isPaletteImage)
    {
      std::cout << "Input is a defined as palette image, trying to read it as scalar. " << '\n';
    }
  }

  if (!io->GetExpandRGBPalette() && isPaletteImage)
  {
    if (io->GetIsReadAsScalarPlusPalette())
    {
      std::cout << "Image read as Scalar." << '\n';

      // print palette
      IOType::PaletteType palette = io->GetColorPalette();
      std::cout << "Palette: " << '\n';
      for (unsigned int i = 0; i < palette.size(); ++i)
      {
        std::cout << '[' << i << "]:" << palette[i] << '\n';
      }
    }
    else
    {
      std::cerr << "Test failed!" << '\n';
      std::cerr << "Cannot read data of this palette image as scalar " << io->GetFileName() << '\n';
      return EXIT_FAILURE;
    }
  }
  else
  {
    std::cout << "Image read as Greyscale (conversion)." << '\n';
  }


  // Try writing
  writer->SetInput(reader->GetOutput());
  writer->SetImageIO(io);
  writer->SetFileName(argv[2]);

  ITK_TRY_EXPECT_NO_EXCEPTION(writer->Update());

  // Exercise other methods
  const itk::ImageIOBase::SizeType pixelStride = io->GetPixelStride();
  std::cout << "PixelStride: " << itk::NumericTraits<itk::ImageIOBase::SizeType>::PrintType(pixelStride) << '\n';

  // ToDo
  // When the palette has made into the Metadata Dictionary (as opposed to the ImageIO):
  // Use the MetaDataDictionary
  // io->SetMetaDataDictionary();


  // Release memory
  delete[] loadBuffer;

  std::cout << "Test finished" << '\n';
  return EXIT_SUCCESS;
}
