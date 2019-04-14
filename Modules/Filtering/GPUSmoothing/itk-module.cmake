set(DOCUMENTATION "This module contains the GPU implementation of the
most common image smoothing filters.  For example, Gaussian and Median
filters.  You may also find it interesting to look at the
ITKAnisotropicSmoothing group of filters.")

itk_module(ITKGPUSmoothing
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKGPUCommon
    ITKGPUImageFilterBase
  DEPENDS ## COMPILE_DEPENDS
    ITKSmoothing
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
