set(DOCUMENTATION "This module contains filter/functions for converting
grayscale images to colormapped rgb images.")

itk_module(ITKColormap
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
