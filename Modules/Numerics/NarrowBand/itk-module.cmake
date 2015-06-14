set(DOCUMENTATION "This module contains code for data types and calculation on a
narrow band of space.")

itk_module(ITKNarrowBand
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKImageIntensity
    ITKFiniteDifference
    ITKCurvatureFlow
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
