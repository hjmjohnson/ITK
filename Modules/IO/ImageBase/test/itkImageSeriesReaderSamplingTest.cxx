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

#include "itkImageSeriesReader.h"
#include "itkTestingMacros.h"

int
itkImageSeriesReaderSamplingTest(int argc, char * argv[])
{

  if (argc < 3)
  {
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv) << " inputFileName(s) " << '\n';
    return EXIT_FAILURE;
  }


  using Image3DType = itk::Image<short, 3>;
  using Reader3DType = itk::ImageSeriesReader<Image3DType>;

  Reader3DType::FileNamesContainer fnames;
  for (int i = 1; i < argc; ++i)
  {
    std::cout << argv[i] << '\n';
    fnames.push_back(argv[i]);
  }

  std::cout << "testing reading a series of 2D images to 3D with extra slices" << '\n';
  try
  {
    auto reader = Reader3DType::New();
    reader->SetFileNames(fnames);
    reader->Update();
    double maxSamplingDeviation = 0.0;
    if (itk::ExposeMetaData<double>(
          reader->GetOutput()->GetMetaDataDictionary(), "ITK_non_uniform_sampling_deviation", maxSamplingDeviation))
    {
      std::cout << "global ITK_non_uniform_sampling_deviation detected : " << maxSamplingDeviation << '\n';
    }
    else
    {
      std::cout << "global ITK_non_uniform_sampling_deviation not found" << '\n';
      return EXIT_FAILURE;
    }

    // iterate over all slices to detect offending slice
    for (auto d : *reader->GetMetaDataDictionaryArray())
    {
      const itk::MetaDataDictionary theMetadata = *d;
      double                        samplingDeviation = 0.0;
      if (itk::ExposeMetaData<double>(theMetadata, "ITK_non_uniform_sampling_deviation", samplingDeviation))
      {
        std::cout << "slice ITK_non_uniform_sampling_deviation detected: " << samplingDeviation << '\n';
      }
      else
      {
        std::cout << "slice ITK_non_uniform_sampling_deviation not detected" << '\n';
      }
    }
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::cout << ex;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
