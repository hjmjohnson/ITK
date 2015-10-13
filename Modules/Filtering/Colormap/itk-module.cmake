set(DOCUMENTATION "This module contains filter/functions for converting
grayscale images to colormapped rgb images.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKColormap_Shared "ENABLE_SHARED")
endif()

itk_module(ITKColormap
  ${ITKColormap_Shared}
  COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
