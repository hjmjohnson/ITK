itk_module_test()
set(
  ITKImageFrequencyTests
  #### Frequency Manipulation ###
  # BandPass Filter
  itkFrequencyBandImageFilterTest.cxx
)

createtestdriver(ITKImageFrequency "${ITKImageFrequency-Test_LIBRARIES}" "${ITKImageFrequencyTests}")

## BandPass
itk_add_test(
  NAME itkFrequencyBandImageFilterEvenTest
  COMMAND
    ITKImageFrequencyTestDriver
    itkFrequencyBandImageFilterTest
    "Even"
)
itk_add_test(
  NAME itkFrequencyBandImageFilterOddTest
  COMMAND
    ITKImageFrequencyTestDriver
    itkFrequencyBandImageFilterTest
    "Odd"
)

set(
  ${itk-module}GTests
  itkFrequencyFFTLayoutImageRegionIteratorWithIndexGTest.cxx
  itkFrequencyIteratorsGTest.cxx
)

creategoogletestdriver(${itk-module} "${${itk-module}-Test_LIBRARIES}" "${${itk-module}GTests}")
