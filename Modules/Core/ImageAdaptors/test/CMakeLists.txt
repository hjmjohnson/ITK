itk_module_test()
set(
  ITKImageAdaptorsTests
  itkImageAdaptorTest.cxx
  itkVectorImageTest.cxx
)

createtestdriver(ITKImageAdaptors "${ITKImageAdaptors-Test_LIBRARIES}" "${ITKImageAdaptorsTests}")

itk_add_test(
  NAME itkImageAdaptorTest
  COMMAND
    ITKImageAdaptorsTestDriver
    itkImageAdaptorTest
)
itk_add_test(
  NAME itkVectorImageTest
  COMMAND
    ITKImageAdaptorsTestDriver
    itkVectorImageTest
    ${ITK_TEST_OUTPUT_DIR}/VectorImage.nrrd
    ${ITK_TEST_OUTPUT_DIR}/VectorImage.mhd
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/VectorImage.nrrd
    ${ITK_TEST_OUTPUT_DIR}/VectorImage.{mhd,raw}
)

set(
  ITKImageAdaptorsGTests
  itkImageAdaptorGTest.cxx
  itkComplexConjugateImageAdaptorGTest.cxx
  itkNthElementPixelAccessorGTest.cxx
  itkRGBToVectorImageAdaptorGTest.cxx
  itkVectorImageToImageAdaptorGTest.cxx
)

creategoogletestdriver(ITKImageAdaptors "${ITKImageAdaptors-Test_LIBRARIES}" "${ITKImageAdaptorsGTests}")
