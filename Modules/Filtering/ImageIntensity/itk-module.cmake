set(DOCUMENTATION "This module contains filters that perform pixel-wise
operations on the intensities of images. In particular you will find here
filters that compute trigonometric operations on pixel values, intensity
rescaling, exponentials, conversions between complex and reals, and filters
that combine multiple images into images of multiple components, as well as
filters that compute single scalar images from images of multiple components.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageIntensity_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageIntensity
  ${ITKImageIntensity_Shared}
  COMPILE_DEPENDS
    ITKImageAdaptors
    ITKImageStatistics
    ITKImageGrid
    ITKPath
  TEST_DEPENDS
    ITKTestKernel
    ITKDistanceMap
  DESCRIPTION
    "${DOCUMENTATION}"
)

# Extra dependency of ITKSpatialObjects is introduced by itkPolylineMaskImageFilterTest.
# Extra dependency of ITKSpatialObjects is introduced by itkModulusImageFilterTest.
