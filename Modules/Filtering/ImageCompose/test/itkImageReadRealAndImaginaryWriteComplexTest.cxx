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

/** Example illustrating use of functions to convert between complex valued
 * voxels, magnitude and phase, and real and imaginary representations.
 *
 * \author Simon K. Warfield simon.warfield\@childrens.harvard.edu
 *
 * \note Attribution Notice. This research work was made possible by Grant
 * Number R01 RR021885 (PI Simon K. Warfield, Ph.D.) from
 * the National Center for Research Resources (NCRR), a component of the
 * National Institutes of Health (NIH).  Its contents are solely the
 * responsibility of the authors and do not necessarily represent the
 * official view of NCRR or NIH.
 *
 */

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkComposeImageFilter.h"
#include "itkTestingMacros.h"

int
itkImageReadRealAndImaginaryWriteComplexTest(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " inputReal inputImaginary outputComplex"
              << std::endl;
    return EXIT_FAILURE;
  }

  constexpr unsigned int Dimension = 2;

  using InputPixelType = float;
  using OutputPixelType = float;
  using InputImageType = itk::Image<InputPixelType, Dimension>;
  using OutputImageType = itk::Image<std::complex<OutputPixelType>, Dimension>;
  using ReaderType = itk::ImageFileReader<InputImageType>;
  using WriterType = itk::ImageFileWriter<OutputImageType>;

  using RealAndImaginary2ComplexFilterType = itk::ComposeImageFilter<InputImageType, OutputImageType>;

  auto readerReal = ReaderType::New();
  auto readerImag = ReaderType::New();
  auto writer = WriterType::New();

  auto realAndImaginary2Complex = RealAndImaginary2ComplexFilterType::New();

  readerReal->SetFileName(argv[1]);
  readerImag->SetFileName(argv[2]);
  writer->SetFileName(argv[3]);

  // Read the image and get its size
  readerReal->Update();
  readerImag->Update();

  realAndImaginary2Complex->SetInput1(readerReal->GetOutput());
  realAndImaginary2Complex->SetInput2(readerImag->GetOutput());

  ITK_TRY_EXPECT_NO_EXCEPTION(realAndImaginary2Complex->Update());

  writer->SetInput(realAndImaginary2Complex->GetOutput());
  writer->Update();

  // check that the default template parameters work
  using DefaultParametersFilterType = itk::ComposeImageFilter<InputImageType>;
  auto temp = DefaultParametersFilterType::New();
  if (temp.IsNull())
  {
    return EXIT_FAILURE;
  }

  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
