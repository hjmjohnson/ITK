set(DOCUMENTATION "This module contains filters that perform pixel-wise
operations on the intensities of images. In particular you will find here
filters that compute trigonometric operations on pixel values, intensity
rescaling, exponentials, conversions between complex and reals, and filters
that combine multiple images into images of multiple components, as well as
filters that compute single scalar images from images of multiple components.")

if(1)
# If building this module with explicit template instantiation, the module will
# need to be built as a shared library, and its dependencies will need to be
# escalated from DEPENDS ## COMPILE_DEPENDS to DEPENDS.  These changes are needed to
# ensure template instantiations are linked and shared correctly.

itk_module(ITKImageIntensity
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKImageAdaptors
    ITKImageStatistics
    ITKImageGrid
    ITKPath
  TEST_DEPENDS
    ITKTestKernel
    ITKDistanceMap
    ITKGoogleTest
  DESCRIPTION
    "${DOCUMENTATION}"
)

else()

itk_module(ITKImageIntensity
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
  DEPENDS ## COMPILE_DEPENDS
    ITKCommon
    ITKImageAdaptors
    ITKImageStatistics
    ITKImageGrid
    ITKPath
  TEST_DEPENDS
    ITKTestKernel
    ITKDistanceMap
    ITKGoogleTest
  DESCRIPTION
    "${DOCUMENTATION}"
)
endif()

# Extra dependency of ITKSpatialObjects is introduced by itkPolylineMaskImageFilterTest.
# Extra dependency of ITKSpatialObjects is introduced by itkModulusImageFilterTest.
