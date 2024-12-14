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

#include <fstream>
#include "itkGrayscaleDilateImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkTextOutput.h"
#include "itkSimpleFilterWatcher.h"
#include "itkFlatStructuringElement.h"
#include "itkTestingMacros.h"

int
itkGrayscaleDilateImageFilterTest(int argc, char * argv[])
{
  // Comment the following if you want to use the itk text output window
  itk::OutputWindow::SetInstance(itk::TextOutput::New());

  if (argc < 6)
  {
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " InputImage BASIC HISTO ANCHOR VHGW" << '\n';
    return EXIT_FAILURE;
  }

  const unsigned int dim = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<unsigned char, dim>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  auto reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  // Create a filter
  using SRType = itk::FlatStructuringElement<dim>;
  using FilterType = itk::GrayscaleDilateImageFilter<ImageType, ImageType, SRType>;
  auto filter = FilterType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(filter, GrayscaleDilateImageFilter, KernelImageFilter);


  auto boundary = itk::NumericTraits<PixelType>::NonpositiveMin();
  filter->SetBoundary(boundary);
  ITK_TEST_SET_GET_VALUE(boundary, filter->GetBoundary());

  filter->SetInput(reader->GetOutput());

  const itk::SimpleFilterWatcher watcher(filter, "filter");

  using RadiusType = FilterType::RadiusType;

  // test default values
  auto r1 = itk::MakeFilled<RadiusType>(1);
  if (filter->GetRadius() != r1)
  {
    std::cerr << "Wrong default Radius: " << filter->GetRadius() << '\n';
    return EXIT_FAILURE;
  }

  if (filter->GetAlgorithm() != FilterType::AlgorithmEnum::HISTO)
  {
    std::cerr << "Wrong default algorithm." << '\n';
    return EXIT_FAILURE;
  }

  try
  {
    filter->SetRadius(4);

    using WriterType = itk::ImageFileWriter<ImageType>;
    auto writer = WriterType::New();
    writer->SetInput(filter->GetOutput());

    filter->SetAlgorithm(FilterType::AlgorithmEnum::BASIC);
    writer->SetFileName(argv[2]);
    writer->Update();

    filter->SetAlgorithm(FilterType::AlgorithmEnum::HISTO);
    writer->SetFileName(argv[3]);
    writer->Update();

    filter->SetAlgorithm(FilterType::AlgorithmEnum::ANCHOR);
    writer->SetFileName(argv[4]);
    writer->Update();

    filter->SetAlgorithm(FilterType::AlgorithmEnum::VHGW);
    writer->SetFileName(argv[5]);
    writer->Update();
  }
  catch (const itk::ExceptionObject & e)
  {
    std::cerr << "Exception detected: " << e.GetDescription();
    return EXIT_FAILURE;
  }

  // Generate test image
  using WriterType = itk::ImageFileWriter<ImageType>;
  auto writer = WriterType::New();
  writer->SetInput(filter->GetOutput());
  writer->SetFileName(argv[2]);
  writer->Update();

  return EXIT_SUCCESS;
}
