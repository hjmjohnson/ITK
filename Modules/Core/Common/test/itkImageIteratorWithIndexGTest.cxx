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

#include "itkMath.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkNumericTraits.h"
#include "itkGTest.h"


namespace
{
template <typename TPixelType>
class itkImageIteratorWithIndexTestIteratorTester
{

public:
  using PixelType = TPixelType;

  using ImageType = itk::Image<PixelType, 3>;

  using IteratorType = itk::ImageRegionIteratorWithIndex<ImageType>;

  using ConstIteratorType = itk::ImageRegionConstIteratorWithIndex<ImageType>;

  itkImageIteratorWithIndexTestIteratorTester(const PixelType & value)
    : m_Image(ImageType::New())
  {
    auto size = ImageType::SizeType::Filled(100);

    const typename ImageType::RegionType region{ size };

    m_Image->SetRegions(region);
    m_Image->Allocate();

    m_Image->FillBuffer(value);
  }

  bool
  TestIterator()
  {
    IteratorType       it(m_Image, m_Image->GetBufferedRegion());
    itk::SizeValueType i = 0;
    it.GoToBegin();
    while (!it.IsAtEnd())
    {
      const PixelType value = it.Get();
      const PixelType testValue = value * static_cast<typename itk::NumericTraits<PixelType>::ValueType>(2);
      it.Set(testValue);
      if (itk::Math::NotExactlyEquals(it.Get(), testValue))
      {
        std::cerr << "TestIterator failed!" << std::endl;
        return false;
      }
      ++it;
      i++;
    }
    if (i != m_Image->GetBufferedRegion().GetNumberOfPixels())
    {
      std::cerr << "TestConstIterator failed (NumberOfPixels)!" << std::endl;
      return false;
    }
    return true;
  }

  bool
  TestConstIterator()
  {
    ConstIteratorType  it(m_Image, m_Image->GetBufferedRegion());
    itk::SizeValueType i = 0;
    it.GoToBegin();
    while (!it.IsAtEnd())
    {
      const PixelType value = it.Get();
      if (itk::Math::NotExactlyEquals(value, it.Get())) // check repeatability
      {
        std::cerr << "TestConstIterator failed!" << std::endl;
        return false;
      }
      ++it;
      i++;
    }
    if (i != m_Image->GetBufferedRegion().GetNumberOfPixels())
    {
      std::cerr << "TestConstIterator failed (NumberOfPixels)!" << std::endl;
      return false;
    }
    return true;
  }

  bool
  TestReverseIteration()
  {
    ConstIteratorType  it(m_Image, m_Image->GetBufferedRegion());
    itk::SizeValueType i = 0;
    it.GoToReverseBegin();
    while (!it.IsAtReverseEnd())
    {
      const PixelType value = it.Get();
      if (itk::Math::NotExactlyEquals(value, it.Get())) // check repeatability
      {
        std::cerr << "TestReverseIteration failed!" << std::endl;
        return false;
      }
      --it;
      i++;
    }
    if (i != m_Image->GetBufferedRegion().GetNumberOfPixels())
    {
      std::cerr << "TestConstIterator failed (NumberOfPixels)!" << std::endl;
      return false;
    }
    return true;
  }

private:
  typename ImageType::Pointer m_Image;
};
} // namespace

TEST(ImageIteratorWithIndex, ConvertedLegacyTest)
{
  // Instantiate image of various types and
  // test the iterators on them

  std::cout << "Testing with Image< char, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<int8_t> TesterC(10);
  EXPECT_TRUE(TesterC.TestIterator());
  EXPECT_TRUE(TesterC.TestConstIterator());
  EXPECT_TRUE(TesterC.TestReverseIteration());

  std::cout << "Testing with Image< unsigned char, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<unsigned char> TesterUC(10);
  EXPECT_TRUE(TesterUC.TestIterator());
  EXPECT_TRUE(TesterUC.TestConstIterator());
  EXPECT_TRUE(TesterUC.TestReverseIteration());

  std::cout << "Testing with Image< short, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<short> TesterS(10);
  EXPECT_TRUE(TesterS.TestIterator());
  EXPECT_TRUE(TesterS.TestConstIterator());
  EXPECT_TRUE(TesterS.TestReverseIteration());

  std::cout << "Testing with Image< unsigned short, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<unsigned short> TesterUS(10);
  EXPECT_TRUE(TesterUS.TestIterator());
  EXPECT_TRUE(TesterUS.TestConstIterator());
  EXPECT_TRUE(TesterUS.TestReverseIteration());

  std::cout << "Testing with Image< int, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<int> TesterI(10);
  EXPECT_TRUE(TesterI.TestIterator());
  EXPECT_TRUE(TesterI.TestConstIterator());
  EXPECT_TRUE(TesterI.TestReverseIteration());

  std::cout << "Testing with Image< unsigned int, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<unsigned int> TesterUI(10);
  EXPECT_TRUE(TesterUI.TestIterator());
  EXPECT_TRUE(TesterUI.TestConstIterator());
  EXPECT_TRUE(TesterUI.TestReverseIteration());

  std::cout << "Testing with Image< float, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<float> TesterF(10.0);
  EXPECT_TRUE(TesterF.TestIterator());
  EXPECT_TRUE(TesterF.TestConstIterator());
  EXPECT_TRUE(TesterF.TestReverseIteration());

  std::cout << "Testing with Image< double, 3 > " << std::endl;
  itkImageIteratorWithIndexTestIteratorTester<double> TesterD(10.0);
  EXPECT_TRUE(TesterD.TestIterator());
  EXPECT_TRUE(TesterD.TestConstIterator());
  EXPECT_TRUE(TesterD.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<int8_t,4>, 3 > " << std::endl;
  using VC = itk::Vector<int8_t, 4>;
  auto                                            vc = itk::MakeFilled<VC>(127);
  itkImageIteratorWithIndexTestIteratorTester<VC> TesterVC(vc);
  EXPECT_TRUE(TesterVC.TestIterator());
  EXPECT_TRUE(TesterVC.TestConstIterator());
  EXPECT_TRUE(TesterVC.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned char,4>, 3 > " << std::endl;
  using VUC = itk::Vector<unsigned char, 4>;
  auto                                             vuc = itk::MakeFilled<VUC>(10);
  itkImageIteratorWithIndexTestIteratorTester<VUC> TesterVUC(vuc);
  EXPECT_TRUE(TesterVUC.TestIterator());
  EXPECT_TRUE(TesterVUC.TestConstIterator());
  EXPECT_TRUE(TesterVUC.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<short,4>, 3 > " << std::endl;
  using VS = itk::Vector<short, 4>;
  auto                                            vs = itk::MakeFilled<VS>(10);
  itkImageIteratorWithIndexTestIteratorTester<VS> TesterVS(vs);
  EXPECT_TRUE(TesterVS.TestIterator());
  EXPECT_TRUE(TesterVS.TestConstIterator());
  EXPECT_TRUE(TesterVS.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned short,4>, 3 > " << std::endl;
  using VUS = itk::Vector<unsigned short, 4>;
  auto                                             vus = itk::MakeFilled<VUS>(10);
  itkImageIteratorWithIndexTestIteratorTester<VUS> TesterVUS(vus);
  EXPECT_TRUE(TesterVUS.TestIterator());
  EXPECT_TRUE(TesterVUS.TestConstIterator());
  EXPECT_TRUE(TesterVUS.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<int,4>, 3 > " << std::endl;
  using VI = itk::Vector<int, 4>;
  auto                                            vi = itk::MakeFilled<VI>(10);
  itkImageIteratorWithIndexTestIteratorTester<VI> TesterVI(vi);
  EXPECT_TRUE(TesterVI.TestIterator());
  EXPECT_TRUE(TesterVI.TestConstIterator());
  EXPECT_TRUE(TesterVI.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<unsigned int,4>, 3 > " << std::endl;
  using VUI = itk::Vector<unsigned int, 4>;
  auto                                             vui = itk::MakeFilled<VUI>(10);
  itkImageIteratorWithIndexTestIteratorTester<VUI> TesterVUI(vui);
  EXPECT_TRUE(TesterVUI.TestIterator());
  EXPECT_TRUE(TesterVUI.TestConstIterator());
  EXPECT_TRUE(TesterVUI.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<float,4>, 3 > " << std::endl;
  using VF = itk::Vector<float, 4>;
  auto                                            vf = itk::MakeFilled<VF>(10);
  itkImageIteratorWithIndexTestIteratorTester<VF> TesterVF(vf);
  EXPECT_TRUE(TesterVF.TestIterator());
  EXPECT_TRUE(TesterVF.TestConstIterator());
  EXPECT_TRUE(TesterVF.TestReverseIteration());

  std::cout << "Testing with Image< itk::Vector<double,4>, 3 > " << std::endl;
  using VD = itk::Vector<double, 4>;
  auto                                            vd = itk::MakeFilled<VD>(10);
  itkImageIteratorWithIndexTestIteratorTester<VD> TesterVD(vd);
  EXPECT_TRUE(TesterVD.TestIterator());
  EXPECT_TRUE(TesterVD.TestConstIterator());
  EXPECT_TRUE(TesterVD.TestReverseIteration());
}
