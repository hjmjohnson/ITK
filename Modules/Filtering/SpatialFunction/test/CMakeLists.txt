itk_module_test()
set(ITKSpatialFunctionGTests itkSpatialFunctionImageEvaluatorFilterGTest.cxx)
creategoogletestdriver(ITKSpatialFunction "${ITKSpatialFunction-Test_LIBRARIES}" "${ITKSpatialFunctionGTests}")
