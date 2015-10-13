set(DOCUMENTATION "This module groups image filters whose operations are
related to manipulations of the underlying image grid. For example, flipping an
image, permuting axis, padding, cropping, pasting, tiling, resampling,
shrinking, and changing its origin or spacing or orientation.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageGrid_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageGrid
  ${ITKImageGrid_Shared}
  COMPILE_DEPENDS
    ITKImageFunction
  TEST_DEPENDS
    ITKTestKernel
    ITKImageSources
    ITKImageIntensity
  DESCRIPTION
    "${DOCUMENTATION}"
)

# ITKImageIntensity dependency introduced by itkBSplineScatteredDataPointSetToImageFilterTest4
# ITKSmoothing dependency introduced by itkSliceBySliceImageFilterTest.
# ITKIOImageBase dependency introduced by itkResampleImageFilter.
