itk_module_test()
set(ITKTestKernelTests itkRandomImageSourceValuesTest.cxx)

createtestdriver(ITKTestKernel "${ITKTestKernel-Test_LIBRARIES}" "${ITKTestKernelTests}")

set(BASELINE "${ITK_DATA_ROOT}/Baseline/Common")
set(TEMP ${ITK_TEST_OUTPUT_DIR})

itk_add_test(
  NAME itkRandomImageSourceValuesTest
  COMMAND
    ITKTestKernelTestDriver
    --compare
    DATA{Baseline/itkRandomImageSourceValuesTest.mha}
    ${ITK_TEST_OUTPUT_DIR}/itkRandomImageSourceValuesTest.mha
    itkRandomImageSourceValuesTest
    ${ITK_TEST_OUTPUT_DIR}/itkRandomImageSourceValuesTest.mha
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkRandomImageSourceValuesTest.mha
)

set(
  ITKTestKernelGTests
  itkGoogleTest.cxx
  itkGoogleTestFixture.cxx
  itkRandomImageSourceAttributesGTest.cxx
  itkTestingComparisonImageFilterGTest.cxx
  itkTestingExtractSliceImageFilterGTest.cxx
  itkTestingStretchIntensityImageFilterGTest.cxx
  itkUtf8FilenameGTest.cxx
)

creategoogletestdriver(ITKTestKernel "${ITKTestKernel-Test_LIBRARIES}" "${ITKTestKernelGTests}")
