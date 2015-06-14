set(DOCUMENTATION "This module contains the GPU implementation for image
thresholding filters such as the classical binary thresholding.")

itk_module(ITKGPUThresholding
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKGPUCommon
  COMPILE_DEPENDS
    ITKThresholding
  TEST_DEPENDS
    ITKTestKernel
    ITKGPUSmoothing
  DESCRIPTION
    "${DOCUMENTATION}"
)
