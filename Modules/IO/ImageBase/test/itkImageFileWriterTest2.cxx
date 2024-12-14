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

#include "itkImageFileWriter.h"
#include "itkImageFileReader.h"

int
itkImageFileWriterTest2(int argc, char * argv[])
{

  if (argc < 2)
  {
    std::cout << "usage: itkIOTests itkImageFileWriterTest2 outputFileName" << '\n';
    return EXIT_FAILURE;
  }

  using ImageNDType = itk::Image<unsigned char, 2>;
  using WriterType = itk::ImageFileWriter<ImageNDType>;
  using ReaderType = itk::ImageFileReader<ImageNDType>;

  auto image = ImageNDType::New();

  auto                          size = itk::MakeFilled<ImageNDType::SizeType>(5);
  auto                          index = itk::MakeFilled<ImageNDType::IndexType>(1);
  const ImageNDType::RegionType region{ index, size };

  image->SetRegions(region);
  image->AllocateInitialized();

  ImageNDType::PointType originalPoint;
  image->TransformIndexToPhysicalPoint(index, originalPoint);
  std::cout << "Original Starting Index: " << index << '\n';
  std::cout << "Original Starting Point (physical cooridents) : " << originalPoint << '\n';
  std::cout << "Original Origin: " << image->GetOrigin() << '\n';

  ImageNDType::PointType readPoint;
  auto                   writer = WriterType::New();
  auto                   reader = ReaderType::New();
  try
  {
    writer->SetInput(image);
    writer->SetFileName(argv[1]);
    writer->Update();


    reader->SetFileName(argv[1]);
    reader->Update();
    index = reader->GetOutput()->GetLargestPossibleRegion().GetIndex();
    reader->GetOutput()->TransformIndexToPhysicalPoint(index, readPoint);
    std::cout << "Read Starting Index: " << index << '\n';
    std::cout << "Original Starting Point (physical cooridents) : " << readPoint << '\n';
    std::cout << "Read Origin: " << image->GetOrigin() << '\n';
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::cout << "caught exception!" << '\n';
    std::cout << ex;
    return EXIT_FAILURE;
  }

  if (readPoint != originalPoint)
  {
    std::cout << "Image locations changed!" << '\n';
    return EXIT_FAILURE;
  }

  // execute the PrintSelf methods
  std::cout << writer;

  return EXIT_SUCCESS;
}
