set(DOCUMENTATION "This module contains classes for applying antialiasing
filters to images. This is typically done to smooth the outcome of
segmentations, previous to extracting contours or surfaces from them. Note that
you can also achieve effects similar to anti-aliasing by using a binary
segmentation as input to a level set filter.")

itk_module(ITKAntiAlias
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS ## COMPILE_DEPENDS
    ITKLevelSets
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
