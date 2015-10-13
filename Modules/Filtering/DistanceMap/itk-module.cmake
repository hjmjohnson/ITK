set(DOCUMENTATION "This module contains multiple implementations of distance
map filters. They include the implementations of Danielsson and Maurer, as
well as other distance concepts such as Hausdorff and Chamfer distances.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKDistanceMap_Shared "ENABLE_SHARED")
endif()

itk_module(ITKDistanceMap
  ${ITKDistanceMap_Shared}
  COMPILE_DEPENDS
    ITKBinaryMathematicalMorphology
    ITKImageLabel
    ITKNarrowBand
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}")
