set(DOCUMENTATION "This module contains the base classes that support image
filters. For the most part, these are classes that developers will use to
create new image filters (and that are the base classes of existing image
filters). You will find here: Unary, Binary and Ternary Functor filters, Noise
sources, recursive separable filters and the base classes for neighborhood
filters.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKImageFilterBase_Shared "ENABLE_SHARED")
endif()

itk_module(ITKImageFilterBase
  ${ITKImageFilterBase_Shared}
  COMPILE_DEPENDS
    ITKCommon
  TEST_DEPENDS
    ITKTestKernel
    ITKImageIntensity
  DESCRIPTION
    "${DOCUMENTATION}"
)

# Extra test dependency is introduced by itkMaskNeighborhoodOperatorImageFilterTest.
