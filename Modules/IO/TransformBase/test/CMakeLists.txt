itk_module_test()
set(ITKIOTransformBaseTests itkTransformFileWriterTest.cxx)

createtestdriver(ITKIOTransformBase "${ITKIOTransformBase-Test_LIBRARIES}" "${ITKIOTransformBaseTests}")

itk_add_test(
  NAME itkTransformFileWriterTest
  COMMAND
    ITKIOTransformBaseTestDriver
    itkTransformFileWriterTest
)

set(
  ITKIOTransformBaseGTests
  itkTransformFileReaderGTest.cxx
  itkTransformIOBaseGTest.cxx
)

creategoogletestdriver(ITKIOTransformBase "${ITKIOTransformBase-Test_LIBRARIES}" "${ITKIOTransformBaseGTests}")
