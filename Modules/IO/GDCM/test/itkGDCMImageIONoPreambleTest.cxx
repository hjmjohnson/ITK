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

#include "itkGDCMImageIO.h"
#include "itkImageFileReader.h"
#include "itkTestingMacros.h"

// Specific ImageIO test

/** This test verifies itkGDCMImageIO can read
 *  DICOM files that contain no preamble
 */
int
itkGDCMImageIONoPreambleTest(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Missing parameters." << '\n';
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv);
    std::cerr << " DicomImage" << '\n';
    return EXIT_FAILURE;
  }

  using InputPixelType = short;
  using InputImageType = itk::Image<InputPixelType, 3>;
  using ReaderType = itk::ImageFileReader<InputImageType>;
  using ImageIOType = itk::GDCMImageIO;

  auto       dcmImageIO = ImageIOType::New();
  const bool canRead = dcmImageIO->CanReadFile(argv[1]);
  if (!canRead)
  {
    std::cerr << "Cannot read file " << '\n';
    return EXIT_FAILURE;
  }

  auto reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->SetImageIO(dcmImageIO);

  try
  {
    reader->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "exception in file reader " << '\n';
    std::cerr << e << '\n';
    return EXIT_FAILURE;
  }

  InputImageType::SizeType extentSize;
  extentSize = reader->GetOutput()->GetLargestPossibleRegion().GetSize();
  std::cout << "Read image dimensions: (" << extentSize[0] << ", " << extentSize[1] << ", " << extentSize[2] << ')'
            << '\n';
  if (extentSize[0] == 0 || extentSize[1] == 0 || extentSize[2] == 0)
  {
    std::cerr << "File read but empty " << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
