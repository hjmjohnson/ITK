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

#include "itkImageToImageFilter.h"
#include "itkGTest.h"

namespace
{

template <typename TInputImage, typename TOutputImage>
class ImageToImageFilterTestHelper : public itk::ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  using Self = ImageToImageFilterTestHelper;
  using Superclass = itk::ImageToImageFilter<TInputImage, TOutputImage>;
  using Pointer = itk::SmartPointer<Self>;
  using ConstPointer = itk::SmartPointer<const Self>;

  itkNewMacro(Self);
};

} // namespace

TEST(ImageToImageFilter, ConvertedLegacyTest)
{

  constexpr unsigned int ImageDimension{ 3 };
  using InputPixelType = unsigned char;
  using OutputPixelType = short;

  using InputImageType = itk::Image<InputPixelType, ImageDimension>;
  using OutputImageType = itk::Image<OutputPixelType, ImageDimension>;

  using FilterType = ImageToImageFilterTestHelper<InputImageType, OutputImageType>;

  auto inputImage1 = InputImageType::New();
  auto inputImage2 = InputImageType::New();
  auto inputImage3 = InputImageType::New();
  auto inputImage4 = InputImageType::New();

  auto filter = FilterType::New();

  filter->Print(std::cout);
  std::cout << "Name of Class = " << filter->GetNameOfClass() << std::endl;
  std::cout << "Name of Superclass = " << filter->Superclass::GetNameOfClass() << std::endl;

  filter->SetInput(inputImage1);
  EXPECT_EQ(filter->GetInput(), inputImage1) << "Error in Set/GetInput()";

  filter->SetInput(inputImage2);
  EXPECT_EQ(filter->GetInput(), inputImage2) << "Error in Set/GetInput()";

  filter->SetInput(0, inputImage1);
  EXPECT_EQ(filter->GetInput(0), inputImage1) << "Error in Set/GetInput(n)";


  filter->PushBackInput(inputImage2);
  filter->PushBackInput(inputImage3);
  filter->PushFrontInput(inputImage4);

  EXPECT_EQ(filter->GetInput(0), inputImage4) << "Error in PushFrontInput";

  EXPECT_EQ(filter->GetInput(1), inputImage1) << "Error in PushFrontInput";

  EXPECT_EQ(filter->GetInput(2), inputImage2) << "Error in PushBackInput";

  EXPECT_EQ(filter->GetInput(3), inputImage3) << "Error in PushBackInput";
}
