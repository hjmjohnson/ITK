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

#include "itkImageToListSampleFilter.h"
#include "itkSubsample.h"
#include "itkRandomImageSource.h"
#include "itkComposeImageFilter.h"
#include "itkMath.h"

int
itkSubsampleTest(int, char *[])
{
  std::cout << "Subsample Test \n \n";
  bool        pass = true;
  std::string whereFail = "";

  using FloatImage = itk::Image<float, 3>;

  // Now generate a random image
  using SourceType = itk::RandomImageSource<FloatImage>;
  auto source = SourceType::New();

  itk::SizeValueType       size[3] = { 17, 8, 20 };
  const itk::SizeValueType totalSize = size[0] * size[1] * size[2];

  source->SetSize(size);
  constexpr float minValue = -100.0;
  constexpr float maxValue = 1000.0;

  source->SetMin(static_cast<FloatImage::PixelType>(minValue));
  source->SetMax(static_cast<FloatImage::PixelType>(maxValue));
  source->Update();


  // creat a new image with array pixel type from the source
  using ArrayPixelType = itk::FixedArray<FloatImage::PixelType, 1>;

  using ArrayPixelImageType = itk::Image<ArrayPixelType, 3>;
  using MaskPixelImageType = itk::Image<unsigned char, 3>;

  using ImageCastFilterType = itk::ComposeImageFilter<FloatImage, ArrayPixelImageType>;
  auto castFilter = ImageCastFilterType::New();
  castFilter->SetInput(source->GetOutput());
  castFilter->Update();

  using ImageToListSampleFilterType = itk::Statistics::ImageToListSampleFilter<ArrayPixelImageType, MaskPixelImageType>;

  auto filter = ImageToListSampleFilterType::New();
  filter->SetInput(castFilter->GetOutput());

  try
  {
    filter->Update();
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Exception caught: " << excp << std::endl;
    return EXIT_FAILURE;
  }

  using ListSampleType = ImageToListSampleFilterType::ListSampleType;

  using SubsampleType = itk::Statistics::Subsample<ListSampleType>;

  auto subsample = SubsampleType::New();

  std::cout << subsample->GetNameOfClass() << std::endl;


  const ImageToListSampleFilterType::ListSampleType * listSample = filter->GetOutput();

  subsample->Print(std::cout);

  subsample->SetSample(listSample);

  subsample->Print(std::cout);


  // Initialize the subsample with sample
  subsample->InitializeWithAllInstances();

  // Clear and  repopulate the subsample container
  subsample->Clear();

  // add only the first half of instances of the sample
  for (ListSampleType::InstanceIdentifier id = 0;
       id < static_cast<ListSampleType::InstanceIdentifier>(listSample->Size() / 2);
       id++)
  {
    subsample->AddInstance(id);
  }

  // test if an exception is thrown, if a sample with id outside the
  // range of the Sample is added to the SubSample
  const int idOutisdeRange = listSample->Size() + 2;

  try
  {
    subsample->AddInstance(idOutisdeRange);
    std::cerr
      << "Exception should have been thrown since an instance outside the range of the sample container is added"
      << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  using MeasurementVectorType = SubsampleType::MeasurementVectorType;
  try
  {
    const MeasurementVectorType vec = subsample->GetMeasurementVector(idOutisdeRange);
    std::cerr << "Exception should have been thrown since the id specified is outside the range of the sample container"
              << std::endl;
    std::cerr << "The invalid subsample->GetMeasurementVector() is: " << vec << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  try
  {
    // Purposely calling GetFrequency() method prematurely in order to trigger an exception.
    subsample->GetFrequency(idOutisdeRange);
    std::cerr << "Exception should have been thrown since the id specified is outside the range of the sample container"
              << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  // try swapping indices out of range
  try
  {
    subsample->Swap(2000000, 50);
    std::cerr << "Exception should have been thrown since the indices specified to be swapped are outside the range of "
                 "the sample container"
              << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  // try accessing a measurement vector by index that is out of range
  try
  {
    const unsigned int          index = listSample->Size() + 2;
    const MeasurementVectorType measurementVector = subsample->GetMeasurementVectorByIndex(index);
    std::cerr
      << "Exception should have been thrown since the index specified is outside the range of the sample container"
      << std::endl;
    std::cerr << "The size of the invalid subsample->GetMeasurementVectorByIndex( index ) is: " << subsample
              << std::endl;
    std::cerr << "The invalid subsample->GetMeasurementVectorByIndex() is: " << measurementVector << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  // try accessing a measurement vector frequency by index that is out of range
  try
  {
    const unsigned int                         index = listSample->Size() + 2;
    const SubsampleType::AbsoluteFrequencyType frequency = subsample->GetFrequencyByIndex(index);
    std::cout << "Frequency: " << frequency << std::endl;
    std::cerr
      << "Exception should have been thrown since the index specified is outside the range of the sample container"
      << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  // try accessing an instance identifier of a measurement vector
  // using an index that is out of range
  try
  {
    const unsigned int                       index = listSample->Size() + 2;
    const ListSampleType::InstanceIdentifier id = subsample->GetInstanceIdentifier(index);
    std::cerr
      << "Exception should have been thrown since the index specified is outside the range of the sample container"
      << std::endl;
    std::cout << "Instance identifier: " << id << std::endl;
    return EXIT_FAILURE;
  }
  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Expected Exception caught: " << excp << std::endl;
  }

  if ((totalSize / 2) != subsample->Size())
  {
    pass = false;
    whereFail = "Size()";
  }

  std::cout << subsample->GetTotalFrequency() << std::endl;

  auto index = ArrayPixelImageType::IndexType::Filled(2); // index {2, 2, 2} = instance identifier (offset from image)
  ArrayPixelImageType::PixelType           pixel = filter->GetInput()->GetPixel(index);
  const ListSampleType::InstanceIdentifier ind =
    static_cast<FloatImage::OffsetValueType>(filter->GetInput()->ComputeOffset(index));

  if (itk::Math::NotExactlyEquals(pixel[0], subsample->GetMeasurementVector(ind)[0]))
  {
    pass = false;
    whereFail = "GetMeasurementVector()";
  }

  // iterator test
  using ImageIterator = itk::ImageRegionConstIterator<ArrayPixelImageType>;
  ImageIterator i_iter(filter->GetInput(), filter->GetInput()->GetLargestPossibleRegion());

  SubsampleType::Iterator s_iter = subsample->Begin();
  unsigned int            count = 0;
  while (count < subsample->Size())
  {
    if (itk::Math::NotExactlyEquals(i_iter.Get()[0], s_iter.GetMeasurementVector()[0]))
    {
      pass = false;
      whereFail = "Iterator: GetMeasurementVector()";
    }
    ++count;
    ++i_iter;
    ++s_iter;
  }

  if (s_iter != subsample->End())
  {
    pass = false;
    whereFail = "Iterator: End()";
  }

  if (!pass)
  {
    std::cout << "Test failed in " << whereFail << '.' << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Test passed." << std::endl;
  return EXIT_SUCCESS;
}
