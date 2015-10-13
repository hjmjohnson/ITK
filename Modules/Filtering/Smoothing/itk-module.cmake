set(DOCUMENTATION "This module includes the most common image smoothing
filters. For example, Gaussian and Median filters. You may also find it
interesting to look at the ITKAnisotropicSmoothing group of filters.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKSmoothing_Shared "ENABLE_SHARED")
endif()

itk_module(ITKSmoothing
  ${ITKSmoothing_Shared}
  COMPILE_DEPENDS
    ITKImageFunction
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
