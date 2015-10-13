set(DOCUMENTATION "This module contains classes made to visually
enhance the images, mostly by adding them artificial colors")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageFusion_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageFusion
  ${ITKImageFusion_Shared}
  COMPILE_DEPENDS
    ITKBinaryMathematicalMorphology
    ITKImageLabel
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
