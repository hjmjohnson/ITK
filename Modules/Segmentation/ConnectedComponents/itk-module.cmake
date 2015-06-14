set(DOCUMENTATION "This module contains modules to identify and modify connected
components. Theses algorithms are commonly applied to binary or label map
images. See also ITKClassifiers, ITKLabelMap, and
ITKBinaryMathematicalMorphology.")

itk_module(ITKConnectedComponents
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKImageIntensity
    ITKThresholding
    ITKImageGrid
    ITKImageLabel
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
