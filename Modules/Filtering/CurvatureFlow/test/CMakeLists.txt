itk_module_test()
set(ITKCurvatureFlowTests itkCurvatureFlowTest.cxx)

createtestdriver(ITKCurvatureFlow "${ITKCurvatureFlow-Test_LIBRARIES}" "${ITKCurvatureFlowTests}")

set(
  ITKCurvatureFlowGTests
  itkBinaryMinMaxCurvatureFlowImageFilterGTest.cxx
  itkCurvatureFlowFunctionGTest.cxx
  itkMinMaxCurvatureFlowFunctionGTest.cxx
)

creategoogletestdriver(ITKCurvatureFlow "${ITKCurvatureFlow-Test_LIBRARIES}" "${ITKCurvatureFlowGTests}")

itk_add_test(
  NAME itkCurvatureFlowTesti
  COMMAND
    ITKCurvatureFlowTestDriver
    itkCurvatureFlowTest
    ${ITK_TEST_OUTPUT_DIR}/itkCurvatureFlowTest.vtk
  ITK_REMOVE_TEMPORARY_TEST_FILES
    ${ITK_TEST_OUTPUT_DIR}/itkCurvatureFlowTest.vtk
)
