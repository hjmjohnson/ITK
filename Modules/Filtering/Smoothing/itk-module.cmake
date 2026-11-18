set(
  DOCUMENTATION
  "This module includes the most common image smoothing
filters. For example, Gaussian and Median filters. You may also find it
interesting to look at the @ref ITKAnisotropicSmoothing group of filters."
)

itk_module(
  ITKSmoothing
  DEPENDS
    ITKConvolution
    ITKImageFunction
    ITKImageSources
  PRIVATE_DEPENDS
    ITKFFT
  ENABLE_SHARED
  TEST_DEPENDS
    ITKGoogleTest
    ITKConvolution
    ITKTestKernel
  DESCRIPTION "${DOCUMENTATION}"
)
