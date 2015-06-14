set(DOCUMENTATION "This module includes the most common image smoothing
filters. For example, Gaussian and Median filters. You may also find it
interesting to look at the ITKAnisotropicSmoothing group of filters.")

itk_module(ITKSmoothing
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  COMPILE_DEPENDS
    ITKImageFunction
    ITKImageFilterBase
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
