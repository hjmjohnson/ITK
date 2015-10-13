set(DOCUMENTATION "This module groups image sources which generate an image")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageSources_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageSources
  ${ITKImageSources_Shared}
  COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
    ITKImageIntensity
  DESCRIPTION
    "${DOCUMENTATION}"
)

# the ITKIntensity is only needed for the
# VectorIndexSelectionCastImageFilter for the PhysicalPointImageSourceTest
