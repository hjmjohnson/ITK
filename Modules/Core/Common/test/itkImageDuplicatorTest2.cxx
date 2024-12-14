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

#include <iostream>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImageDuplicator.h"
#include "itkAbsImageFilter.h"
#include "itkTestingMacros.h"

int
itkImageDuplicatorTest2(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Missing parameters." << '\n';
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv);
    std::cerr << " Input Output" << '\n';
    return EXIT_FAILURE;
  }

  using PixelType = float;
  constexpr unsigned int Dimension = 3;
  using ImageType = itk::Image<PixelType, Dimension>;

  using DuplicatorType = itk::ImageDuplicator<ImageType>;
  auto dup = DuplicatorType::New();
  using AbsType = itk::AbsImageFilter<ImageType, ImageType>;
  auto absF = AbsType::New();

  try
  {
    const auto inImage = itk::ReadImage<ImageType>(argv[1]);

    const ImageType::RegionType lpr = inImage->GetLargestPossibleRegion();
    ImageType::RegionType       region = lpr;
    for (unsigned int d = 0; d < Dimension; ++d)
    {
      const itk::IndexValueType size = region.GetSize(d);
      region.SetIndex(d, size / 4);
      region.SetSize(d, size / 2);
    }

    absF->SetInput(inImage);
    absF->GetOutput()->SetRequestedRegion(region);
    absF->Update();
    const ImageType::Pointer absImage = absF->GetOutput(); // different buffered and largest regions

    dup->SetInputImage(absF->GetOutput());
    dup->Update();
    const ImageType::ConstPointer dupImage = dup->GetOutput();

    itk::WriteImage(dupImage, argv[2]);
    std::cout << "Test SUCCESS" << '\n';
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << e << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
