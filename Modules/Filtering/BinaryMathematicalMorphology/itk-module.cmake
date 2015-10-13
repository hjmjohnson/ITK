set(DOCUMENTATION "This module contains classes that implement variations of
mathematical morphology techniques for binary images. In addition to the classical erosion,
dilation, opening and closing filters, you will find here geodesic operations,
maxima and minima filters, and reconstruction filters.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKBinaryMathematicalMorphology_Shared "ENABLE_SHARED")
endif()

itk_module(ITKBinaryMathematicalMorphology
  ${ITKBinaryMathematicalMorphology}
  COMPILE_DEPENDS
    ITKLabelMap
    ITKMathematicalMorphology
  TEST_DEPENDS
    ITKTestKernel
    ITKImageGrid
    ITKImageIntensity
  DESCRIPTION
    "${DOCUMENTATION}"
)
