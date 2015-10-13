set(DOCUMENTATION "This module contains filters that compute differential
operations in images. In particular, image gradients, gradient magnitude and
difference of Gaussians.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageGradient_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageGradient
  ${ITKImageGradient_Shared}
  COMPILE_DEPENDS
    ITKImageAdaptors
    ITKImageIntensity
    ITKSmoothing
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
