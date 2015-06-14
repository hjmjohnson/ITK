set(DOCUMENTATION "This module contains classes for calculating signed distance
images, i.e. images of the distance from a segmenting contour (the distance is
zero on the contour, negative inside the contour, and positive outside the
contour).")

itk_module(ITKSignedDistanceFunction
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKImageFunction
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
