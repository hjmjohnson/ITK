set(DOCUMENTATION "This module contains classes that compute image features. In
particular you will find here: Canny edge detection, Sobel, ZeroCrossings,
Hough transform for lines and circles, Hessian filters, Vesselness, and
Fractional anisotropy for tensor images.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageFeature_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageFeature
  ${ITKImageFeature_Shared}
  COMPILE_DEPENDS
    ITKImageGradient
    ITKImageSources
  COMPILE_DEPENDS
    ITKMesh
    ITKImageStatistics
    ITKSmoothing
  TEST_DEPENDS
    ITKTestKernel
    ITKThresholding
  DESCRIPTION
    "${DOCUMENTATION}"
  )
# Extra test dependency on ITKThresholding is introduced by itkHoughTransform2DCirclesImageTest.
