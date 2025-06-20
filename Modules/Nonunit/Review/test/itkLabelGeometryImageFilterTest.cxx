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
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkMetaImageIO.h"
#include "itkLabelGeometryImageFilter.h"

#include "itkCSVArray2DFileReader.h"
#include "itkCSVNumericObjectFileWriter.h"
#include "itkTestingMacros.h"

// Helper function declaration.
template <const unsigned int VDimension>
int
LabelGeometryImageFilterTest(std::string labelImageName,
                             std::string intensityImageName,
                             std::string outputImageName,
                             std::string outputFileName,
                             std::string compareFileName);

// Helper function to compare matrices.
template <typename MatrixType>
bool
compareMatrices(const MatrixType & m1, const MatrixType & m2, double epsilon);

int
itkLabelGeometryImageFilterTest(int argc, char * argv[])
{
  if (argc < 5)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv);
    std::cerr << "labelImage intensityImage outputImage outputFileName [compareFileName]" << std::endl;
    return EXIT_FAILURE;
  }
  // Legacy compat with older MetaImages
  itk::MetaImageIO::SetDefaultDoublePrecision(6);

  std::string labelImageName = argv[1];
  std::string intensityImageName = argv[2];
  std::string outputImageName = argv[3];
  std::string outputFileName = argv[4];
  std::string compareFileName = "";
  if (argc == 6)
  {
    compareFileName = argv[5];
  }

  // Determine the dimension of the image and template the filter over
  // this dimension.
  itk::ImageIOBase::Pointer imageIO =
    itk::ImageIOFactory::CreateImageIO(intensityImageName.c_str(), itk::ImageIOFactory::IOFileModeEnum::ReadMode);
  imageIO->SetFileName(intensityImageName);
  imageIO->ReadImageInformation();
  const size_t ImageDimension = imageIO->GetNumberOfDimensions();

  if (ImageDimension == 2)
  {
    return LabelGeometryImageFilterTest<2>(
      labelImageName, intensityImageName, outputImageName, outputFileName, compareFileName);
  }
  else if (ImageDimension == 3)
  {
    return LabelGeometryImageFilterTest<3>(
      labelImageName, intensityImageName, outputImageName, outputFileName, compareFileName);
  }
  return EXIT_SUCCESS;
}

template <const unsigned int VDimension>
int
LabelGeometryImageFilterTest(std::string labelImageName,
                             std::string intensityImageName,
                             std::string outputImageName,
                             std::string outputFileName,
                             std::string compareFileName)
{
  // Tolerance for comparing the matrix of features for regression testing.
  double epsilon = 1e-3;

  using LabelPixelType = unsigned short;
  using IntensityPixelType = unsigned char;

  using LabelImageType = itk::Image<LabelPixelType, VDimension>;
  using IntensityImageType = itk::Image<IntensityPixelType, VDimension>;

  // Read the label image.
  using LabelReaderType = itk::ImageFileReader<LabelImageType>;
  auto labelReader = LabelReaderType::New();
  labelReader->SetFileName(labelImageName);

  // Read the intensity image.
  using IntensityReaderType = itk::ImageFileReader<IntensityImageType>;
  auto intensityReader = IntensityReaderType::New();
  intensityReader->SetFileName(intensityImageName);

  // First test the filter without any intensity image.
  using LabelGeometryType = itk::LabelGeometryImageFilter<LabelImageType, IntensityImageType>;
  auto labelGeometryFilter = LabelGeometryType::New();

  ITK_EXERCISE_BASIC_OBJECT_METHODS(labelGeometryFilter, LabelGeometryImageFilter, ImageToImageFilter);


  labelGeometryFilter->SetInput(labelReader->GetOutput());
  labelGeometryFilter->SetIntensityInput(intensityReader->GetOutput());

  // These generate optional outputs.
  auto calculatePixelIndices = true;
  ITK_TEST_SET_GET_BOOLEAN(labelGeometryFilter, CalculatePixelIndices, calculatePixelIndices);

  auto calculateOrientedBoundingBox = true;
  ITK_TEST_SET_GET_BOOLEAN(labelGeometryFilter, CalculateOrientedBoundingBox, calculateOrientedBoundingBox);

  auto calculateOrientedLabelRegions = true;
  ITK_TEST_SET_GET_BOOLEAN(labelGeometryFilter, CalculateOrientedLabelRegions, calculateOrientedLabelRegions);

  auto calculateOrientedIntensityRegions = true;
  ITK_TEST_SET_GET_BOOLEAN(labelGeometryFilter, CalculateOrientedIntensityRegions, calculateOrientedIntensityRegions);

  ITK_TRY_EXPECT_NO_EXCEPTION(labelGeometryFilter->Update());


  // Write out the oriented image of the first object.
  typename LabelGeometryType::LabelPixelType labelValue = 1;
  using IntensityWriterType = itk::ImageFileWriter<IntensityImageType>;
  auto intensityWriter = IntensityWriterType::New();
  intensityWriter->SetFileName(outputImageName);
  intensityWriter->SetInput(labelGeometryFilter->GetOrientedIntensityImage(labelValue));

  ITK_TRY_EXPECT_NO_EXCEPTION(intensityWriter->Update());


  // Write all of the object features out to a csv file.
  int numberOfLabels = labelGeometryFilter->GetNumberOfLabels();
  int numberOfColumns = 14;
  using WriterType = itk::CSVNumericObjectFileWriter<double, 1, 1>;
  using MatrixType = WriterType::vnlMatrixType;
  MatrixType matrix(numberOfLabels, numberOfColumns);

  int                                    rowIndex = 0;
  typename LabelGeometryType::LabelsType allLabels = labelGeometryFilter->GetLabels();
  for (auto allLabelsIt = allLabels.begin(); allLabelsIt != allLabels.end(); ++allLabelsIt)
  {
    int columnIndex = 0;
    labelValue = *allLabelsIt;
    matrix(rowIndex, columnIndex++) = labelValue;
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetVolume(labelValue);
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetIntegratedIntensity(labelValue);

    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetCentroid(labelValue)[0];
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetCentroid(labelValue)[1];
    if constexpr (VDimension == 3)
    {
      matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetCentroid(labelValue)[2];
    }
    else
    {
      matrix(rowIndex, columnIndex++) = 0;
    }
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetWeightedCentroid(labelValue)[0];
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetWeightedCentroid(labelValue)[1];
    if constexpr (VDimension == 3)
    {
      matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetWeightedCentroid(labelValue)[2];
    }
    else
    {
      matrix(rowIndex, columnIndex++) = 0;
    }
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetMajorAxisLength(labelValue);
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetMinorAxisLength(labelValue);
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetEccentricity(labelValue);
    matrix(rowIndex, columnIndex++) = labelGeometryFilter->GetElongation(labelValue);

    typename LabelGeometryType::RealType orientation = labelGeometryFilter->GetOrientation(labelValue);
    // If the orientation is very close pi, we set it to 0.
    orientation = itk::Math::abs(itk::Math::pi - orientation) < epsilon ? 0 : orientation;
    matrix(rowIndex, columnIndex++) = orientation;

    rowIndex++;
  }

  // Set up the headers.
  WriterType::StringVectorType columnName;
  columnName.emplace_back("Label number");
  columnName.emplace_back("Volume (voxels)");
  columnName.emplace_back("Integrated intensity");
  columnName.emplace_back("Centroid X (voxel)");
  columnName.emplace_back("Centroid Y (voxel)");
  columnName.emplace_back("Centroid Z (voxel)");
  columnName.emplace_back("Weighted centroid X (voxel)");
  columnName.emplace_back("Weighted centroid Y (voxel)");
  columnName.emplace_back("Weighted centroid Z (voxel)");
  columnName.emplace_back("Major axis length");
  columnName.emplace_back("Minor axis length");
  columnName.emplace_back("Eccentricity");
  columnName.emplace_back("Elongation");
  columnName.emplace_back("Orientation");

  // write out the array2D object
  auto writer = WriterType::New();
  writer->SetFileName(outputFileName);
  writer->SetInput(&matrix);
  writer->SetColumnHeaders(columnName);
  auto * matrixPointer = new MatrixType(matrix.data_block(), numberOfLabels, numberOfColumns);
  writer->SetInput(matrixPointer);

  ITK_TRY_EXPECT_NO_EXCEPTION(writer->Write());


  delete matrixPointer;

  // If an optional csv file was passed in, compare the results of this analysis with the values in the file.
  // This enables regression testing on the calculated values.
  if (strcmp(compareFileName.c_str(), ""))
  {
    // Read the values we just wrote.
    // This is better than comparing against the values in memory because some truncation occurs when writing to file.
    using ReaderType = itk::CSVArray2DFileReader<double>;
    auto newReader = ReaderType::New();
    newReader->SetFileName(outputFileName);
    newReader->SetFieldDelimiterCharacter(',');
    newReader->HasColumnHeadersOn();
    newReader->HasRowHeadersOff();

    // Read the values to compare against.
    auto compareReader = ReaderType::New();
    compareReader->SetFileName(compareFileName);
    compareReader->SetFieldDelimiterCharacter(',');
    compareReader->HasColumnHeadersOn();
    compareReader->HasRowHeadersOff();

    ITK_TRY_EXPECT_NO_EXCEPTION(newReader->Parse());
    ITK_TRY_EXPECT_NO_EXCEPTION(compareReader->Parse());


    using DataFrameObjectType = itk::CSVArray2DDataObject<double>;
    auto newDFO = DataFrameObjectType::New();
    newDFO = newReader->GetOutput();
    MatrixType newMatrix = newDFO->GetMatrix();

    auto compareDFO = DataFrameObjectType::New();
    compareDFO = compareReader->GetOutput();
    MatrixType compareMatrix = compareDFO->GetMatrix();

    std::cout << "Baseline matrix: " << std::endl;
    std::cout << compareMatrix << std::endl;
    std::cout << "Test matrix: " << std::endl;
    std::cout << newMatrix << std::endl;

    // Compare the matrices.
    if (!compareMatrices(newMatrix, compareMatrix, epsilon))
    {
      std::cerr << "Matrices are not the same! Test Failed!" << std::endl;
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}


// function for comparing matrices
template <typename MatrixType>
bool
compareMatrices(const MatrixType & m1, const MatrixType & m2, double epsilon)
{
  bool pass = true;

  if (m1.rows() != m2.rows() || m1.cols() != m2.cols())
  {
    pass = false;
    return pass;
  }

  for (unsigned int i = 0; i < m1.rows(); ++i)
  {
    for (unsigned int j = 0; j < m1.cols(); ++j)
    {
      // We need to test whether m1 is a NaN and/or m2 is a NaN.
      // If they are both NaN, then they are the same.
      // If only one is NaN, then the comparison should fail.
      // Without such a test, the comparison of the difference being greater than epsilon will pass.
      // The equality and inequality predicates are non-signaling so x = x returning false can be used to test if x is a
      // quiet NaN.
      bool m1_isNaN = (m1[i][j] == m1[i][j]);
      bool m2_isNaN = (m2[i][j] == m2[i][j]);
      if ((m1_isNaN && !m2_isNaN) || (!m1_isNaN && m2_isNaN))
      {
        pass = false;
        return pass;
      }
      if (itk::Math::abs(m1[i][j] - m2[i][j]) > epsilon)
      {
        std::cout << "Matrix difference:"
                  << "itk::Math::abs(m2[" << i << "][" << j << "] - m1[" << i << "][" << j
                  << "]): " << itk::Math::abs(m1[i][j] - m2[i][j]) << std::endl;
        pass = false;
        return pass;
      }
    }
  }
  return pass;
}
