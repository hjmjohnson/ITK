itk_module_test()
set(
  ITKAnisotropicSmoothingTests
  itkGradientAnisotropicDiffusionImageFilterTest2.cxx
)

createtestdriver(ITKAnisotropicSmoothing "${ITKAnisotropicSmoothing-Test_LIBRARIES}" "${ITKAnisotropicSmoothingTests}")

itk_add_test(
  NAME itkGradientAnisotropicDiffusionImageFilterTest2
  COMMAND
    ITKAnisotropicSmoothingTestDriver
    --compare
    DATA{${ITK_DATA_ROOT}/Baseline/BasicFilters/GradientAnisotropicDiffusionImageFilterTest2.png}
    ${ITK_TEST_OUTPUT_DIR}/GradientAnisotropicDiffusionImageFilterTest2.png
    itkGradientAnisotropicDiffusionImageFilterTest2
    DATA{${ITK_DATA_ROOT}/Input/cake_easy.png}
    ${ITK_TEST_OUTPUT_DIR}/GradientAnisotropicDiffusionImageFilterTest2.png
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/GradientAnisotropicDiffusionImageFilterTest2.png
)

set(
  ITKAnisotropicSmoothingGTests
  itkCurvatureAnisotropicDiffusionImageFilterGTest.cxx
  itkGradientAnisotropicDiffusionImageFilterGTest.cxx
  itkMinMaxCurvatureFlowImageFilterGTest.cxx
)
creategoogletestdriver(ITKAnisotropicSmoothing "${ITKAnisotropicSmoothing-Test_LIBRARIES}" "${ITKAnisotropicSmoothingGTests}")
