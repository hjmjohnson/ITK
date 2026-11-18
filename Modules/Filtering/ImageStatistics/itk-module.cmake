set(
  DOCUMENTATION
  "This module contains classes that compute statistics on
images, or use those statistics to perform image operations. In particular you
will find here: how to calculate image moments, minimum maximum values,
projections, principal components analysis (PCA) for shape modeling,
computation of label statistics and image accumulation."
)

itk_module(
  ITKImageStatistics
  DEPENDS
    ITKImageFilterBase
    ITKTransform
    ITKSpatialObjects
  PRIVATE_DEPENDS
    ITKImageCompose
  TEST_DEPENDS
    ITKGoogleTest
    ITKTestKernel
    ITKIOGDCM
    ITKIOMeta
    ITKImageIntensity
    ITKThresholding
    ITKImageLabel
    ITKImageCompose
  DESCRIPTION "${DOCUMENTATION}"
)

# Extra test dependency on ImageLabel is introduced by itkBinaryProjectionImageFilterTest.
