itk_module_test()

set(ITKEigenGTests itkEigenAnalysis2DImageFilterGTest.cxx)
creategoogletestdriver(ITKEigen "${ITKEigen-Test_LIBRARIES}" "${ITKEigenGTests}")
