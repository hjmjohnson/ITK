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

#include "itkImageLinearIteratorWithIndex.h"
#include "itkGTest.h"

TEST(ImageLinearIterator, ConvertedLegacyTest)
{
  SCOPED_TRACE("Creating an image of indices");

  constexpr unsigned int ImageDimension{ 3 };

  using PixelType = itk::Index<ImageDimension>;

  using ImageType = itk::Image<PixelType, ImageDimension>;

  auto                          myImage = ImageType::New();
  const ImageType::ConstPointer myConstImage = myImage;

  ImageType::SizeType size0;

  size0[0] = 100;
  size0[1] = 100;
  size0[2] = 100;

  const ImageType::RegionType region0{ size0 };

  myImage->SetRegions(region0);
  myImage->Allocate();

  using IteratorType = itk::ImageLinearIteratorWithIndex<ImageType>;

  using ConstIteratorType = itk::ImageLinearConstIteratorWithIndex<ImageType>;

  IteratorType it(myImage, region0);

  it.GoToBegin();
  it.SetDirection(0); // 0=x, 1=y, 2=z

  ImageType::IndexType index0;

  while (!it.IsAtEnd())
  {
    while (!it.IsAtEndOfLine())
    {
      index0 = it.GetIndex();
      it.Set(index0);
      ++it;
    }
    it.NextLine();
  }

  // Verification
  IteratorType ot(myImage, region0);

  ot.GoToBegin();
  ot.SetDirection(0); // 0=x, 1=y, 2=z

  SCOPED_TRACE("Verifying iterator...");

  while (!ot.IsAtEnd())
  {
    while (!ot.IsAtEndOfLine())
    {
      index0 = ot.GetIndex();
      EXPECT_EQ(ot.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
      ++ot;
    }
    ot.NextLine();
  }

  // Verification
  ConstIteratorType cot(myConstImage, region0);

  // Test exceptions
  constexpr int direction{ ImageType::GetImageDimension() + 1 };
  EXPECT_THROW(cot.SetDirection(direction), itk::ExceptionObject);

  cot.GoToBegin();
  cot.SetDirection(0); // 0=x, 1=y, 2=z

  SCOPED_TRACE("Verifying const iterator...");

  while (!cot.IsAtEnd())
  {
    while (!cot.IsAtEndOfLine())
    {
      index0 = cot.GetIndex();
      EXPECT_EQ(cot.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
      ++cot;
    }
    cot.NextLine();
  }

  // Test GoToReverseBeginOfLine()
  cot.GoToBegin();
  cot.GoToReverseBeginOfLine();
  index0 = cot.GetIndex();
  EXPECT_EQ(cot.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;


  // Verification
  {
    SCOPED_TRACE("Verifying iterator in reverse direction...");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 20;
    start[2] = 30;

    ImageType::SizeType size{ 2, 3, 4 };

    const ImageType::RegionType region{ start, size };

    SCOPED_TRACE("IteratorType ior( myImage, region );");
    IteratorType ior(myImage, region);

    std::cout << "    GetIndex(): " << ior.GetIndex() << std::endl;
    SCOPED_TRACE("ior.GoToReverseBegin();");
    ior.GoToReverseBegin();
    std::cout << "    GetIndex(): " << ior.GetIndex() << std::endl;
    SCOPED_TRACE("ior.SetDirection( 0 ); // 0=x, 1=y, 2=z");
    ior.SetDirection(0); // 0=x, 1=y, 2=z
    std::cout << " ior.GetDirection(): " << ior.GetDirection() << std::endl;
    SCOPED_TRACE("while( !ior.IsAtReverseEnd() )");
    while (!ior.IsAtReverseEnd())
    {
      SCOPED_TRACE("while( !ior.IsAtReverseEndOfLine() )");
      std::cout << "    GetIndex(): " << ior.GetIndex() << std::endl;
      while (!ior.IsAtReverseEndOfLine())
      {
        index0 = ior.GetIndex();
        EXPECT_EQ(ior.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
        SCOPED_TRACE("--ior;");
        --ior;
        std::cout << "    GetIndex(): " << ior.GetIndex() << std::endl;
      }
      SCOPED_TRACE("ior.PreviousLine();");
      ior.PreviousLine();
      std::cout << "    GetIndex(): " << ior.GetIndex() << std::endl;
    }
  }

  // Verification
  SCOPED_TRACE("Verifying const iterator in reverse direction...");

  ConstIteratorType cor(myImage, region0);

  cor.GoToReverseBegin();
  cor.SetDirection(0); // 0=x, 1=y, 2=z

  while (!cor.IsAtReverseEnd())
  {
    while (!cor.IsAtReverseEndOfLine())
    {
      index0 = cor.GetIndex();
      EXPECT_EQ(cor.Get(), index0) << "Values don't correspond to what was stored. Test failed at index " << index0;
      --cor;
    }
    cor.PreviousLine();
  }


  // Verification of GotoBeginOfLine() in the iterator
  {
    SCOPED_TRACE("Verifying  iterator GoToBeginOfLine()...");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    IteratorType bot(myImage, region);

    bot.SetDirection(0); // 0=x, 1=y, 2=z
    bot.GoToBegin();

    ImageType::IndexType testIndex = start;
    testIndex[1] += 2; // advance two lines in Y

    bot.NextLine(); // advance two lines in Y
    bot.NextLine();

    ++bot; // advance a bit along the line
    ++bot;
    ++bot;
    ++bot;

    bot.GoToBeginOfLine(); // go back to the begin of the line

    EXPECT_EQ(bot.GetIndex(), testIndex) << "GoToBeginOfLine() test failed";
  }


  // Verification of GotoBeginOfLine() in the const iterator
  {
    SCOPED_TRACE("Verifying const iterator GoToBeginOfLine()...");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    ConstIteratorType cbot(myImage, region);

    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    ImageType::IndexType testIndex = start;
    testIndex[1] += 2; // advance two lines in Y

    cbot.NextLine(); // advance two lines in Y
    cbot.NextLine();

    ++cbot; // advance a bit along the line
    ++cbot;
    ++cbot;
    ++cbot;

    cbot.GoToBeginOfLine(); // go back to the begin of the line

    EXPECT_EQ(cbot.GetIndex(), testIndex) << "GoToBeginOfLine() test failed";
  }


  // Verification of the Iterator in a subregion of the image
  {
    SCOPED_TRACE("Verifying Iterator in a Region smaller than the whole image...");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    IteratorType cbot(myImage, region);

    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    while (!cbot.IsAtEnd())
    {
      while (!cbot.IsAtEndOfLine())
      {
        const ImageType::IndexType index = cbot.GetIndex();
        const ImageType::PixelType pixel = cbot.Get();

        EXPECT_EQ(index, pixel) << "Iterator in region test failed";

        ++cbot;
      }
      cbot.NextLine();
    }
  }


  // Verification of the Const Iterator in a subregion of the image
  {
    SCOPED_TRACE("Verifying Const Iterator in a Region smaller than the whole image...");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    ConstIteratorType cbot(myImage, region);

    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    while (!cbot.IsAtEnd())
    {
      while (!cbot.IsAtEndOfLine())
      {
        const ImageType::IndexType index = cbot.GetIndex();
        const ImageType::PixelType pixel = cbot.Get();

        EXPECT_EQ(index, pixel) << "Iterator in region test failed";

        ++cbot;
      }
      cbot.NextLine();
    }
  }


  // Verification of the Iterator NextLine() in the middle of a line
  {
    SCOPED_TRACE("Verifying Iterator NextLine() in the middle of a line");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    SCOPED_TRACE("IteratorType cbot( myImage, region );");
    IteratorType cbot(myImage, region);

    SCOPED_TRACE("cbot.SetDirection( 0 ); // 0=x, 1=y, 2=z");
    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    SCOPED_TRACE("cbot.GoToBegin();");
    cbot.GoToBegin();
    std::cout << "    GetIndex(): " << cbot.GetIndex() << std::endl;
    // go to the middle of the first line
    SCOPED_TRACE("for(unsigned int i=0; ...");
    for (unsigned int i = 0; i < size[0] / 2; ++i)
    {
      SCOPED_TRACE("++cbot;");
      ++cbot;
      std::cout << "      GetIndex(): " << cbot.GetIndex() << std::endl;
    }

    // go to next line
    SCOPED_TRACE("cbot.NextLine();");
    cbot.NextLine();
    std::cout << "    GetIndex(): " << cbot.GetIndex() << std::endl;

    SCOPED_TRACE("const ImageType::IndexType testIndex = cbot.Get();");
    const ImageType::IndexType testIndex = cbot.Get();
    SCOPED_TRACE("if( cbot.GetIndex() != testIndex )");
    EXPECT_EQ(cbot.GetIndex(), testIndex) << "NextLine() test failed";
  }

  // Verification of the Iterator PreviousLine() in the middle of a line
  {
    SCOPED_TRACE("Verifying Iterator PreviousLine() in the middle of a line");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    SCOPED_TRACE("IteratorType cbot( myImage, region );");
    IteratorType cbot(myImage, region);

    SCOPED_TRACE("cbot.SetDirection( 0 ); // 0=x, 1=y, 2=z");
    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    SCOPED_TRACE("cbot.GoToBegin();");
    cbot.GoToBegin();
    std::cout << "    GetIndex(): " << cbot.GetIndex() << std::endl;
    // go to the middle of the second line
    SCOPED_TRACE("for(unsigned int i=0; ...");
    for (unsigned int i = 0; i < size[0] + size[0] / 2; ++i)
    {
      SCOPED_TRACE("++cbot;");
      ++cbot;
      SCOPED_TRACE("if(cbot.IsAtEndOfLine())");
      if (cbot.IsAtEndOfLine())
      {
        std::cout << "        cbot.NextLine();" << std::endl;
        cbot.NextLine();
      }
      std::cout << "    GetIndex(): " << cbot.GetIndex() << std::endl;
    }

    // go to previous line
    SCOPED_TRACE("cbot.PreviousLine();");
    cbot.PreviousLine();
    std::cout << "    GetIndex(): " << cbot.GetIndex() << std::endl;

    SCOPED_TRACE("const ImageType::IndexType testIndex = cbot.Get();");
    const ImageType::IndexType testIndex = cbot.Get();
    SCOPED_TRACE("if( cbot.GetIndex() != testIndex )");
    EXPECT_EQ(cbot.GetIndex(), testIndex) << "PreviousLine() test failed";
  }

  // Verification of the ConstIterator NextLine() in the middle of a line
  {
    SCOPED_TRACE("Verifying ConstIterator NextLine() in the middle of a line");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    ConstIteratorType cbot(myImage, region);

    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    // go to the middle of the first line
    for (unsigned int i = 0; i < size[0] / 2; ++i)
    {
      ++cbot;
    }

    // go to next line
    cbot.NextLine();

    const ImageType::IndexType testIndex = cbot.Get();
    EXPECT_EQ(cbot.GetIndex(), testIndex) << "NextLine() test failed";
  }

  // Verification of the ConstIterator PreviousLine() in the middle of a line
  {
    SCOPED_TRACE("Verifying ConstIterator PreviousLine() in the middle of a line");

    ImageType::IndexType start;
    start[0] = 10;
    start[1] = 12;
    start[2] = 14;

    ImageType::SizeType size{ 11, 12, 13 };

    const ImageType::RegionType region{ start, size };

    ConstIteratorType cbot(myImage, region);

    cbot.SetDirection(0); // 0=x, 1=y, 2=z
    cbot.GoToBegin();

    // go to the middle of the second line
    for (unsigned int i = 0; i < size[0] + size[0] / 2; ++i)
    {
      ++cbot;
      if (cbot.IsAtEndOfLine())
      {
        cbot.NextLine();
      }
    }

    // go to previous line
    cbot.PreviousLine();

    const ImageType::IndexType testIndex = cbot.Get();
    EXPECT_EQ(cbot.GetIndex(), testIndex) << "PreviousLine() test failed";
  }
}
