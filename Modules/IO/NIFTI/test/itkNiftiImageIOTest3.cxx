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

#include "itkNiftiImageIOTest.h"
#include <type_traits> // for enable_if
#include <limits>

template <typename ScalarType>
void
Decrement(ScalarType & value, std::enable_if_t<!std::numeric_limits<ScalarType>::is_signed, ScalarType> * = nullptr)
{
  if (value > 1)
  {
    value--;
  }
}

template <typename ScalarType>
void
Decrement(ScalarType & value, std::enable_if_t<std::numeric_limits<ScalarType>::is_signed, ScalarType> * = nullptr)
{
  if (value > -std::numeric_limits<ScalarType>::max() + 1)
  {
    value--;
  }
}

template <typename ScalarType, unsigned int TVecLength, unsigned int TDimension>
int
TestImageOfVectors(const std::string & fname, const std::string & intentCode = "")
{
  constexpr int dimsize = 2;
  /** Deformation field pixel type. */
  using FieldPixelType = typename itk::Vector<ScalarType, TVecLength>;

  /** Deformation field type. */
  using VectorImageType = typename itk::Image<FieldPixelType, TDimension>;

  //
  // swizzle up a random vector image.
  // original test case was destined for failure.  NIfTI always writes out 3D
  // orientation.  The only sensible matrices you could pass in would be of the form
  // A B C 0
  // D E F 0
  // E F G 0
  // 0 0 0 1
  // anything in the 4th dimension that didn't follow that form would just come up scrambled.
  // NOTE: Nifti only reports up to 3D images correctly for direction cosigns.  It is implicitly assumed
  //      that the direction for dimensions 4 or greater come diagonal elements including a 1 in the
  //      direction matrix.
  const typename VectorImageType::DirectionType myDirection = PreFillDirection<TDimension>();

  std::cout << " === Testing VectorLength: " << TVecLength << " Image Dimension " << int{ TDimension } << std::endl;
  std::cout << "======================== Initialized Direction" << std::endl;
  std::cout << myDirection << std::endl;

  typename VectorImageType::IndexType        index{};
  auto                                       size = itk::MakeFilled<typename VectorImageType::SizeType>(dimsize);
  const typename VectorImageType::RegionType imageRegion{ index, size };
  auto                                       spacing = itk::MakeFilled<typename VectorImageType::SpacingType>(1.0);

  const typename VectorImageType::Pointer vi =
    itk::IOTestHelper::AllocateImageFromRegionAndSpacing<VectorImageType>(imageRegion, spacing);
  vi->SetDirection(myDirection);

  size_t dims[7];
  for (unsigned int i = 0; i < TDimension; ++i)
  {
    dims[i] = size[i];
  }
  for (unsigned int i = TDimension; i < 7; ++i)
  {
    dims[i] = 1;
  }

  ScalarType value = std::numeric_limits<ScalarType>::max();
  //  for(fillIt.GoToBegin(); !fillIt.IsAtEnd(); ++fillIt)
  size_t _index[7];
  for (size_t l = 0; l < dims[6]; ++l)
  {
    _index[6] = l;
    for (size_t m = 0; m < dims[5]; ++m)
    {
      _index[5] = m;
      for (size_t n = 0; n < dims[4]; ++n)
      {
        _index[4] = n;
        for (size_t p = 0; p < dims[3]; ++p)
        {
          _index[3] = p;
          for (size_t i = 0; i < dims[2]; ++i)
          {
            _index[2] = i;
            for (size_t j = 0; j < dims[1]; ++j)
            {
              _index[1] = j;
              for (size_t k = 0; k < dims[0]; ++k)
              {
                _index[0] = k;
                FieldPixelType pixel;
                for (size_t q = 0; q < TVecLength; ++q)
                {
                  // pixel[q] = randgen.drand32(lowrange,highrange);
                  Decrement(value);
                  pixel[q] = value;
                }
                for (size_t q = 0; q < TDimension; ++q)
                {
                  index[q] = _index[q];
                }
                vi->SetPixel(index, pixel);
              }
            }
          }
        }
      }
    }
  }
  if (!intentCode.empty())
  {
    itk::MetaDataDictionary & dictionary = vi->GetMetaDataDictionary();
    itk::EncapsulateMetaData<std::string>(dictionary, "intent_code", intentCode);
  }
  const std::string description("text description of file content");
  itk::EncapsulateMetaData<std::string>(vi->GetMetaDataDictionary(), "ITK_FileNotes", description);
  try
  {
    itk::IOTestHelper::WriteImage<VectorImageType, itk::NiftiImageIO>(vi, fname);
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::string message = "Problem found while writing image ";
    message += fname;
    message += "\n";
    message += ex.GetLocation();
    message += "\n";
    message += ex.GetDescription();
    std::cout << message << std::endl;
    itk::IOTestHelper::Remove(fname.c_str());
    return EXIT_FAILURE;
  }
  //
  // read it back in.
  typename VectorImageType::Pointer readback;
  try
  {
    readback = itk::IOTestHelper::ReadImage<VectorImageType>(fname);
  }
  catch (const itk::ExceptionObject & ex)
  {
    std::string message = "Problem found while reading image ";
    message += fname;
    message += "\n";
    message += ex.GetLocation();
    message += "\n";
    message += ex.GetDescription();
    std::cout << message << std::endl;
    itk::IOTestHelper::Remove(fname.c_str());
    return EXIT_FAILURE;
  }
  bool same = true;
  if (!intentCode.empty())
  {
    const itk::MetaDataDictionary & dictionary = readback->GetMetaDataDictionary();
    std::string                     readIntentCode;
    if (itk::ExposeMetaData<std::string>(dictionary, "intent_code", readIntentCode))
    {
      if (readIntentCode != intentCode)
      {
        std::cout << "intent_code is different: " << readIntentCode << " != " << intentCode << std::endl;
        same = false;
      }
    }
    else
    {
      std::cout << "The read image should have an intent_code in its dictionary" << std::endl;
      same = false;
    }
    std::string readDescription;
    if (itk::ExposeMetaData<std::string>(dictionary, "ITK_FileNotes", readDescription))
    {
      if (readDescription != description)
      {
        std::cout << "ITK_FileNotes is different: " << readDescription << " != " << description << std::endl;
        same = false;
      }
    }
    else
    {
      std::cout << "The read image should have a ITK_FileNotes (nifti descrip field) in its dictionary" << std::endl;
      same = false;
    }
  }
  if (readback->GetOrigin() != vi->GetOrigin())
  {
    std::cout << "Origin is different: " << readback->GetOrigin() << " != " << vi->GetOrigin() << std::endl;
    same = false;
  }
  if (readback->GetSpacing() != vi->GetSpacing())
  {
    std::cout << "Spacing is different: " << readback->GetSpacing() << " != " << vi->GetSpacing() << std::endl;
    same = false;
  }
  for (unsigned int r = 0; r < TDimension; ++r)
  {
    for (unsigned int c = 0; c < TDimension; ++c)
    {
      if (itk::Math::abs(readback->GetDirection()[r][c] - vi->GetDirection()[r][c]) > 1e-7)
      {
        std::cout << "Direction is different:\n " << readback->GetDirection() << "\n != \n"
                  << vi->GetDirection() << std::endl;
        same = false;
        break;
      }
    }
  }
  std::cout << "Original vector Image  ?=   vector Image read from disk " << std::endl;
  for (size_t l = 0; l < dims[6]; ++l)
  {
    _index[6] = l;
    for (size_t m = 0; m < dims[5]; ++m)
    {
      _index[5] = m;
      for (size_t n = 0; n < dims[4]; ++n)
      {
        _index[4] = n;
        for (size_t p = 0; p < dims[3]; ++p)
        {
          _index[3] = p;
          for (size_t i = 0; i < dims[2]; ++i)
          {
            _index[2] = i;
            for (size_t j = 0; j < dims[1]; ++j)
            {
              _index[1] = j;
              for (size_t k = 0; k < dims[0]; ++k)
              {
                _index[0] = k;
                for (size_t q = 0; q < TDimension; ++q)
                {
                  index[q] = _index[q];
                }
                const FieldPixelType p1 = vi->GetPixel(index);
                const FieldPixelType p2 = readback->GetPixel(index);
                if (p1 != p2)
                {
                  same = false;
                  std::cout << p1 << " != " << p2 << "    ERROR! " << std::endl;
                }
                else
                {
                  std::cout << p1 << " == " << p2 << std::endl;
                }
              }
            }
          }
        }
      }
    }
  }
  if (same)
  {
    itk::IOTestHelper::Remove(fname.c_str());
  }
  else
  {
    std::cout << "Failing image can be found at: " << fname << std::endl;
  }
  return same ? 0 : EXIT_FAILURE;
}

/** Test writing and reading a Vector Image
 */
int
itkNiftiImageIOTest3(int argc, char * argv[])
{
  //
  // first argument is passing in the writable directory to do all testing
  if (argc > 1)
  {
    char * testdir = *++argv;
    itksys::SystemTools::ChangeDirectory(testdir);
  }
  else
  {
    return EXIT_FAILURE;
  }
  int success(0);

  success |= TestImageOfVectors<unsigned char, 3, 1>(std::string("testVectorImage_unsigned_char_3_1.nii.gz"));
  success |= TestImageOfVectors<char, 3, 1>(std::string("testVectorImage_char_3_1.nii.gz"));
  success |= TestImageOfVectors<unsigned short, 3, 1>(std::string("testVectorImage_unsigned_short_3_1.nii.gz"));
  success |= TestImageOfVectors<short, 3, 1>(std::string("testVectorImage_short_3_1.nii.gz"));
  success |= TestImageOfVectors<unsigned int, 3, 1>(std::string("testVectorImage_unsigned_int_3_1.nii.gz"));
  success |= TestImageOfVectors<int, 3, 1>(std::string("testVectorImage_int_3_1.nii.gz"));
  success |= TestImageOfVectors<unsigned long, 3, 1>(std::string("testVectorImage_unsigned_long_3_1.nii.gz"));
  success |= TestImageOfVectors<long, 3, 1>(std::string("testVectorImage_long_3_1.nii.gz"));
  success |= TestImageOfVectors<unsigned long long, 3, 1>(std::string("testVectorImage_unsigned_long_long_3_1.nii.gz"));
  success |= TestImageOfVectors<long long, 3, 1>(std::string("testVectorImage_long_long_3_1.nii.gz"));
  success |= TestImageOfVectors<float, 3, 1>(std::string("testVectorImage_float_3_1.nii.gz"));
  success |= TestImageOfVectors<float, 3, 2>(std::string("testVectorImage_float_3_2.nii.gz"));
  success |= TestImageOfVectors<float, 3, 3>(std::string("testVectorImage_float_3_3.nii.gz"));
  success |= TestImageOfVectors<float, 4, 3>(std::string("testVectorImage_float_4_3.nii.gz"));
  success |= TestImageOfVectors<float, 4, 4>(std::string("testVectorImage_float_4_4.nii.gz"));
  success |= TestImageOfVectors<double, 3, 3>(std::string("testVectorImage_double_3_3.nii.gz"));

  // Test reading/writing as displacement field (NIFTI intent code = 1006)
  success |= TestImageOfVectors<double, 3, 1>(std::string("testDispacementImage_double.nii.gz"), std::string("1006"));
  success |= TestImageOfVectors<float, 3, 1>(std::string("testDisplacementImage_float.nii.gz"), std::string("1006"));

  return success;
}
