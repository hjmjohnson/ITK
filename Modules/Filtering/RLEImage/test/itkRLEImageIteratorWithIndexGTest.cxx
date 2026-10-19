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

#include "itkNumericTraits.h"
#include "itkGTest.h"
#include "itkRLEImage.h"


namespace
{
template <typename TPixelType>
class itkRLEImageIteratorWithIndexTestIteratorTester
{
public:
  using PixelType = TPixelType;

  using ImageType = itk::RLEImage<PixelType>;

  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  using ConstIteratorType = itk::ImageRegionConstIteratorWithIndex<ImageType>;

  itkRLEImageIteratorWithIndexTestIteratorTester(const PixelType & value)
  {
    m_Image = ImageType::New();

    typename ImageType::SizeType size;
    size.Fill(100);

    typename ImageType::IndexType start;
    start.Fill(0);

    typename ImageType::RegionType region;
    region.SetSize(size);
    region.SetIndex(start);

    m_Image->SetRegions(region);
    m_Image->Allocate();

    m_Image->FillBuffer(value);
  }

  bool
  TestIterator()
  {
    IteratorType it(m_Image, m_Image->GetBufferedRegion());
    it.GoToBegin();
    while (!it.IsAtEnd())
    {
      PixelType value = it.Get();
      PixelType testValue = value * static_cast<typename itk::NumericTraits<PixelType>::ValueType>(2);
      it.Set(testValue);
      if (it.Get() != testValue)
      {
        std::cerr << "TestIterator failed!" << std::endl;
        return false;
      }
      ++it;
    }
    return true;
  }

  bool
  TestConstIterator()
  {
    ConstIteratorType it(m_Image, m_Image->GetBufferedRegion());
    it.GoToBegin();
    while (!it.IsAtEnd())
    {
      PixelType value = it.Get();
      if (value != it.Get()) // check repeatibility
      {
        std::cerr << "TestConstIterator failed!" << std::endl;
        return false;
      }
      ++it;
    }
    return true;
  }

  bool
  TestReverseIteration()
  {
    ConstIteratorType it(m_Image, m_Image->GetBufferedRegion());
    it.GoToReverseBegin();
    while (!it.IsAtReverseEnd())
    {
      PixelType value = it.Get();
      if (value != it.Get()) // check repeatibility
      {
        std::cerr << "TestReverseIteration failed!" << std::endl;
        return false;
      }
      --it;
    }
    return true;
  }

private:
  typename ImageType::Pointer m_Image;
};
} // namespace

TEST(RLEImageIteratorWithIndex, ConvertedLegacyTest)
{
  // Instantiate image of various types and
  // test the iterators on them

  std::cout << "Testing with Image< char, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<char> TesterC(10);
  EXPECT_TRUE(TesterC.TestIterator());
  EXPECT_TRUE(TesterC.TestConstIterator());
  EXPECT_TRUE(TesterC.TestReverseIteration());


  std::cout << "Testing with Image< unsigned char, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<unsigned char> TesterUC(10);
  EXPECT_TRUE(TesterUC.TestIterator());
  EXPECT_TRUE(TesterUC.TestConstIterator());
  EXPECT_TRUE(TesterUC.TestReverseIteration());

  std::cout << "Testing with Image< short, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<short> TesterS(10);
  EXPECT_TRUE(TesterS.TestIterator());
  EXPECT_TRUE(TesterS.TestConstIterator());
  EXPECT_TRUE(TesterS.TestReverseIteration());

  std::cout << "Testing with Image< unsigned short, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<unsigned short> TesterUS(10);
  EXPECT_TRUE(TesterUS.TestIterator());
  EXPECT_TRUE(TesterUS.TestConstIterator());
  EXPECT_TRUE(TesterUS.TestReverseIteration());

  std::cout << "Testing with Image< int, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<int> TesterI(10);
  EXPECT_TRUE(TesterI.TestIterator());
  EXPECT_TRUE(TesterI.TestConstIterator());
  EXPECT_TRUE(TesterI.TestReverseIteration());

  std::cout << "Testing with Image< unsigned int, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<unsigned int> TesterUI(10);
  EXPECT_TRUE(TesterUI.TestIterator());
  EXPECT_TRUE(TesterUI.TestConstIterator());
  EXPECT_TRUE(TesterUI.TestReverseIteration());

  std::cout << "Testing with Image< long long, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<long long> TesterLL(10);
  EXPECT_TRUE(TesterLL.TestIterator());
  EXPECT_TRUE(TesterLL.TestConstIterator());
  EXPECT_TRUE(TesterLL.TestReverseIteration());

  std::cout << "Testing with Image< unsigned long long, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<unsigned long long> TesterULL(10);
  EXPECT_TRUE(TesterULL.TestIterator());
  EXPECT_TRUE(TesterULL.TestConstIterator());
  EXPECT_TRUE(TesterULL.TestReverseIteration());

  std::cout << "Testing with Image< float, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<float> TesterF(10.0);
  EXPECT_TRUE(TesterF.TestIterator());
  EXPECT_TRUE(TesterF.TestConstIterator());
  EXPECT_TRUE(TesterF.TestReverseIteration());

  std::cout << "Testing with Image< double, 3 > " << std::endl;
  itkRLEImageIteratorWithIndexTestIteratorTester<double> TesterD(10.0);
  EXPECT_TRUE(TesterD.TestIterator());
  EXPECT_TRUE(TesterD.TestConstIterator());
  EXPECT_TRUE(TesterD.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<char,4>, 3 > " << std::endl;
  using VC = itk::Vector<char, 4>;
  VC vc;
  vc.Fill(127);
  itkRLEImageIteratorWithIndexTestIteratorTester<VC> TesterVC(vc);
  EXPECT_TRUE(TesterVC.TestIterator());
  EXPECT_TRUE(TesterVC.TestConstIterator());
  EXPECT_TRUE(TesterVC.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned char,4>, 3 > " << std::endl;
  using VUC = itk::Vector<unsigned char, 4>;
  VUC vuc;
  vuc.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VUC> TesterVUC(vuc);
  EXPECT_TRUE(TesterVUC.TestIterator());
  EXPECT_TRUE(TesterVUC.TestConstIterator());
  EXPECT_TRUE(TesterVUC.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<short,4>, 3 > " << std::endl;
  using VS = itk::Vector<short, 4>;
  VS vs;
  vs.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VS> TesterVS(vs);
  EXPECT_TRUE(TesterVS.TestIterator());
  EXPECT_TRUE(TesterVS.TestConstIterator());
  EXPECT_TRUE(TesterVS.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned short,4>, 3 > " << std::endl;
  using VUS = itk::Vector<unsigned short, 4>;
  VUS vus;
  vus.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VUS> TesterVUS(vus);
  EXPECT_TRUE(TesterVUS.TestIterator());
  EXPECT_TRUE(TesterVUS.TestConstIterator());
  EXPECT_TRUE(TesterVUS.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<int,4>, 3 > " << std::endl;
  using VI = itk::Vector<int, 4>;
  VI vi;
  vi.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VI> TesterVI(vi);
  EXPECT_TRUE(TesterVI.TestIterator());
  EXPECT_TRUE(TesterVI.TestConstIterator());
  EXPECT_TRUE(TesterVI.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned int,4>, 3 > " << std::endl;
  using VUI = itk::Vector<unsigned int, 4>;
  VUI vui;
  vui.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VUI> TesterVUI(vui);
  EXPECT_TRUE(TesterVUI.TestIterator());
  EXPECT_TRUE(TesterVUI.TestConstIterator());
  EXPECT_TRUE(TesterVUI.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<float,4>, 3 > " << std::endl;
  using VF = itk::Vector<float, 4>;
  VF vf;
  vf.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VF> TesterVF(vf);
  EXPECT_TRUE(TesterVF.TestIterator());
  EXPECT_TRUE(TesterVF.TestConstIterator());
  EXPECT_TRUE(TesterVF.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<double,4>, 3 > " << std::endl;
  using VD = itk::Vector<double, 4>;
  VD vd;
  vd.Fill(10);
  itkRLEImageIteratorWithIndexTestIteratorTester<VD> TesterVD(vd);
  EXPECT_TRUE(TesterVD.TestIterator());
  EXPECT_TRUE(TesterVD.TestConstIterator());
  EXPECT_TRUE(TesterVD.TestReverseIteration());
}
