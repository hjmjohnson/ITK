set(DOCUMENTATION "This module contains filters that deconvolve images
that have been blurred with a shift-invariant kernel.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKDeconvolution_Shared "ENABLE_SHARED")
endif()

itk_module(ITKDeconvolution
  ${ITKDeconvolution_Shared}
  COMPILE_DEPENDS
    ITKConvolution
    ITKImageSources
    ITKImageAdaptors
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
