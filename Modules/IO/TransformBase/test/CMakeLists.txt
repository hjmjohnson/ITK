itk_module_test()

set(
  ITKIOTransformBaseGTests
  itkTransformFileReaderGTest.cxx
  itkTransformFileWriterGTest.cxx
  itkTransformIOBaseGTest.cxx
)

creategoogletestdriver(ITKIOTransformBase "${ITKIOTransformBase-Test_LIBRARIES}" "${ITKIOTransformBaseGTests}")
