itk_module_test()
set(ITKMarkovRandomFieldsClassifiersTests itkRGBGibbsPriorFilterTest.cxx)

createtestdriver(ITKMarkovRandomFieldsClassifiers "${ITKMarkovRandomFieldsClassifiers-Test_LIBRARIES}"
                 "${ITKMarkovRandomFieldsClassifiersTests}"
)

itk_add_test(
  NAME itkRGBGibbsPriorFilterTest
  COMMAND
    ITKMarkovRandomFieldsClassifiersTestDriver
    itkRGBGibbsPriorFilterTest
)

set(
  ITKMarkovRandomFieldsClassifiersGTests
  itkMRFImageFilterGTest.cxx
  itkRGBGibbsPriorFilterGTest.cxx
)

creategoogletestdriver(
  ITKMarkovRandomFieldsClassifiers
  "${ITKMarkovRandomFieldsClassifiers-Test_LIBRARIES}"
  "${ITKMarkovRandomFieldsClassifiersGTests}"
)
