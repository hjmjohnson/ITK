set(DOCUMENTATION "This module contains filters that perform label voting, i.e.
they count the number of pixels with a given label within a neighborhood and
determine the output pixel based on the count. The operations on label images
are similar to filtering on scalar images. See also
ITKBinaryMathematicalMorphology, ITKConnectedComponents, and ITKLabelMap.")

itk_module(ITKLabelVoting
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKThresholding
  TEST_DEPENDS
    ITKTestKernel
    ITKMetaIO
    ITKDoubleConversion
  DESCRIPTION
    "${DOCUMENTATION}"
)
