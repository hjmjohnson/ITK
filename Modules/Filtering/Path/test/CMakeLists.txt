itk_module_test()
set(
  ITKPathTests
  itkContourExtractor2DImageFilterTest.cxx
  itkExtractOrthogonalSwath2DImageFilterTest.cxx
  itkHilbertPathTest.cxx
  itkOrthogonallyCorrected2DParametricPathTest.cxx
  itkOrthogonalSwath2DPathFilterTest.cxx
  itkPathFunctionsTest.cxx
  itkPathIteratorTest.cxx
  itkPathToChainCodePathFilterTest.cxx
  itkPathToImageFilterTest.cxx
  itkPolyLineParametricPathTest.cxx
)

createtestdriver(ITKPath "${ITKPath-Test_LIBRARIES}" "${ITKPathTests}")

itk_add_test(
  NAME itkPathIteratorTest
  COMMAND
    ITKPathTestDriver
    itkPathIteratorTest
)
itk_add_test(
  NAME itkHilbertPathTest
  COMMAND
    ITKPathTestDriver
    itkHilbertPathTest
)
itk_add_test(
  NAME itkOrthogonallyCorrected2DParametricPathTest
  COMMAND
    ITKPathTestDriver
    itkOrthogonallyCorrected2DParametricPathTest
)
itk_add_test(
  NAME itkPathToImageFilterTest
  COMMAND
    ITKPathTestDriver
    itkPathToImageFilterTest
)
itk_add_test(
  NAME itkPathToChainCodePathFilterTest
  COMMAND
    ITKPathTestDriver
    itkPathToChainCodePathFilterTest
)
itk_add_test(
  NAME itkPathFunctionsTest
  COMMAND
    ITKPathTestDriver
    itkPathFunctionsTest
)
itk_add_test(
  NAME itkPolyLineParametricPathTest
  COMMAND
    ITKPathTestDriver
    itkPolyLineParametricPathTest
)
itk_add_test(
  NAME itkExtractOrthogonalSwath2DImageFilterTest
  COMMAND
    ITKPathTestDriver
    --compare
    DATA{Baseline/ExtractOrthogonalSwath2DImageFilterTest.png}
    ${ITK_TEST_OUTPUT_DIR}/ExtractOrthogonalSwath2DImageFilterTest.png
    itkExtractOrthogonalSwath2DImageFilterTest
    ${ITK_TEST_OUTPUT_DIR}/ExtractOrthogonalSwath2DImageFilterTest.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/ExtractOrthogonalSwath2DImageFilterTest.png
)
itk_add_test(
  NAME itkOrthogonalSwath2DPathFilterTest
  COMMAND
    ITKPathTestDriver
    itkOrthogonalSwath2DPathFilterTest
)
itk_add_test(
  NAME itkContourExtractor2DImageFilterTest
  COMMAND
    ITKPathTestDriver
    itkContourExtractor2DImageFilterTest
    DATA{Input/ContourExtractor2DTest.tif}
)

set(
  ITKPathGTests
  itkChainCodePath2DGTest.cxx
  itkChainCodePathGTest.cxx
  itkChainCodeToFourierSeriesPathFilterGTest.cxx
  itkContourExtractor2DImageFilterGTest.cxx
  itkFourierSeriesPathGTest.cxx
)

creategoogletestdriver(ITKPath "${ITKPath-Test_LIBRARIES}" "${ITKPathGTests}")
