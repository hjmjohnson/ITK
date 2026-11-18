set(
  DOCUMENTATION
  "This module contains filter/functions for converting
grayscale images to colormapped RGB images."
)

itk_module(
  ITKColormap
  DEPENDS
    ITKCommon
  ENABLE_SHARED
  TEST_DEPENDS
    ITKTestKernel
    ITKGoogleTest
  DESCRIPTION "${DOCUMENTATION}"
)
