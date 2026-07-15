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

#include "itkGTest.h"

#include "itkImageSeriesReader.h"
#include "itkImageIOBase.h"
#include "itkMetaDataObject.h"
#include "itkArray.h"

namespace
{
using ImageType = itk::Image<unsigned char, 3>;

// ImageSeriesReader shares a single user-supplied ImageIOBase instance
// between its internal first-slice and last-slice readers, so this stub's
// ReadImageInformation() is invoked twice on the same object: once with
// GetFileName()=="first", once with GetFileName()=="last".
class StubSeriesImageIO : public itk::ImageIOBase
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(StubSeriesImageIO);
  using Self = StubSeriesImageIO;
  using Superclass = itk::ImageIOBase;
  using Pointer = itk::SmartPointer<Self>;
  itkNewMacro(Self);
  itkOverrideGetNameOfClassMacro(StubSeriesImageIO);

  bool
  CanReadFile(const char *) override
  {
    return true;
  }

  void
  ReadImageInformation() override
  {
    this->SetNumberOfDimensions(3);
    this->SetPixelType(itk::IOPixelEnum::SCALAR);
    this->SetComponentType(itk::IOComponentEnum::UCHAR);
    this->SetNumberOfComponents(1);
    for (unsigned int d = 0; d < 3; ++d)
    {
      this->SetDimensions(d, 4);
      this->SetSpacing(d, 1.0);
      this->SetOrigin(d, 0.0);
    }

    const std::string  fname = this->GetFileName();
    const double       sliceOrigin = (fname == "first") ? 0.0 : 10.0;
    const unsigned int overrideSize = (fname == "first") ? m_FirstOverrideSize : m_LastOverrideSize;
    this->SetOrigin(2, sliceOrigin);

    if (overrideSize > 0)
    {
      // ImageSeriesReader exposes this metadata as Array<SpacingScalarType>
      // (Array<ImageType::SpacingValueType>); a type mismatch would make
      // ExposeMetaData return false silently rather than exercise the guard.
      itk::Array<ImageType::SpacingValueType> origin(overrideSize, 0.0);
      if (overrideSize > 2)
      {
        // Distinct from sliceOrigin, and by a different amount per slice, so
        // the override changes the computed inter-slice spacing rather than
        // shifting both endpoints equally (which would look correct even if
        // the override were silently ignored).
        const double offset = (fname == "first") ? 100.0 : 300.0;
        origin[2] = static_cast<ImageType::SpacingValueType>(sliceOrigin + offset);
      }
      itk::EncapsulateMetaData<itk::Array<ImageType::SpacingValueType>>(
        this->GetMetaDataDictionary(), "ITK_ImageOrigin", origin);
    }
  }

  void
  Read(void *) override
  {}
  bool
  CanWriteFile(const char *) override
  {
    return false;
  }
  void
  WriteImageInformation() override
  {}
  void
  Write(const void *) override
  {}

  unsigned int m_FirstOverrideSize{ 0 };
  unsigned int m_LastOverrideSize{ 0 };

protected:
  StubSeriesImageIO() = default;
  ~StubSeriesImageIO() override = default;
};

itk::ImageSeriesReader<ImageType>::Pointer
MakeReader(unsigned int firstOverrideSize, unsigned int lastOverrideSize)
{
  auto io = StubSeriesImageIO::New();
  io->m_FirstOverrideSize = firstOverrideSize;
  io->m_LastOverrideSize = lastOverrideSize;

  auto reader = itk::ImageSeriesReader<ImageType>::New();
  reader->SetImageIO(io);
  reader->SetFileNames({ "first", "last" });
  return reader;
}
} // namespace

TEST(ImageSeriesReaderOriginOverride, RejectsShortOverrideOnFirstSlice)
{
  auto reader = MakeReader(2, 0);
  EXPECT_THROW(reader->UpdateOutputInformation(), itk::ExceptionObject);
}

TEST(ImageSeriesReaderOriginOverride, RejectsShortOverrideOnLastSlice)
{
  auto reader = MakeReader(0, 2);
  EXPECT_THROW(reader->UpdateOutputInformation(), itk::ExceptionObject);
}

TEST(ImageSeriesReaderOriginOverride, AcceptsCorrectlySizedOverride)
{
  auto reader = MakeReader(3, 3);
  ASSERT_NO_THROW(reader->UpdateOutputInformation());

  // Un-overridden slice origins are 0.0 and 10.0 (spacing 10.0); the override
  // shifts them to 100.0 and 310.0 (spacing 210.0). A silently-ignored
  // override would report 10.0, not 210.0.
  const ImageType::SpacingType spacing = reader->GetOutput()->GetSpacing();
  EXPECT_NEAR(spacing[2], 210.0, 1e-6);
}

TEST(ImageSeriesReaderOriginOverride, AcceptsOversizedOverride)
{
  // An override array longer than ImageDimension must not be rejected: only
  // the first ImageDimension elements were ever read, extras were always
  // silently ignored, and no out-of-bounds access ever occurred for this case.
  auto reader = MakeReader(4, 4);
  EXPECT_NO_THROW(reader->UpdateOutputInformation());
}

TEST(ImageSeriesReaderOriginOverride, IgnoresStaleOverrideFromSharedImageIOOnLastSlice)
{
  // Regression test: firstReader and lastReader share the same user-supplied
  // ImageIOBase instance. The last file's read here does not set
  // ITK_ImageOrigin (lastOverrideSize == 0); a leftover entry from reading
  // the first file must not be mistaken for a fresh override on the last.
  auto reader = MakeReader(3, 0);
  ASSERT_NO_THROW(reader->UpdateOutputInformation());

  // First-slice origin is overridden to 100.0; last-slice origin is the raw,
  // un-overridden 10.0. Expected spacing is |10.0 - 100.0| = 90.0. A stale
  // metadata leak would instead reuse the first slice's overridden origin
  // (100.0) for the last slice too, collapsing spacing to the degenerate
  // zero-displacement fallback of 1.0.
  const ImageType::SpacingType spacing = reader->GetOutput()->GetSpacing();
  EXPECT_NEAR(spacing[2], 90.0, 1e-6);
}
