set(DOCUMENTATION "This module contains filters that convolve an image
with a kernel. Convolution is a fundamental operation in many image
analysis algorithms.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKConvolution_Shared "ENABLE_SHARED")
endif()

itk_module(ITKConvolution
  ${ITKConvolution_Shared}
  COMPILE_DEPENDS
    ITKFFT
    ITKImageIntensity
    ITKThresholding
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
