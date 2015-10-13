set(DOCUMENTATION "This module contains multiple variations of image
thresholding filters. In addition to the classical binary thresholding, you
will find here the thresholding filters based on the Otsu criterion, both for
single and multiple thresholds.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKThresholding_Shared "ENABLE_SHARED")
endif()

itk_module(ITKThresholding
  ${ITKThresholding_Shared}
  COMPILE_DEPENDS
    ITKImageIntensity
    ITKImageStatistics
  TEST_DEPENDS
    ITKTestKernel
    ITKSignedDistanceFunction
  DESCRIPTION
    "${DOCUMENTATION}"
)

# Extra test dependency on ITKSignedDistanceFunction  is introduced by itkBinaryThresholdSpatialFunctionTest.
# Extra test dependency on ITKSmoothing is introduced by itkBinaryThresholdProjectionImageFilterTest.
