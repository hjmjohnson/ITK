itk_module_test()
set(ITKTransformFactoryGTests itkTransformFactoryBaseGTest.cxx)

creategoogletestdriver(ITKTransformFactory "${ITKTransformFactory-Test_LIBRARIES}" "${ITKTransformFactoryGTests}")
target_compile_definitions(
  ITKTransformFactoryGTestDriver
  PRIVATE
    "ITK_TRANSFORM_FACTORY_MAX_DIM=${ITK_TRANSFORM_FACTORY_MAX_DIM}"
)
