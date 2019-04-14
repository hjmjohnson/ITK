set(DOCUMENTATION "This module contains classes that implement variations of
mathematical morphology techniques for binary images. In addition to the classical erosion,
dilation, opening and closing filters, you will find here geodesic operations,
maxima and minima filters, and reconstruction filters.")

itk_module(ITKBinaryMathematicalMorphology
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS ## COMPILE_DEPENDS
    ITKLabelMap
    ITKMathematicalMorphology
  TEST_DEPENDS
    ITKTestKernel
    ITKImageGrid
    ITKImageIntensity
  DESCRIPTION
    "${DOCUMENTATION}"
)
