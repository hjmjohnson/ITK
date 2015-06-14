set(DOCUMENTATION "This module contains a factory to create transforms
from a string identifier.")

itk_module(ITKTransformFactory
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKTransform
  COMPILE_DEPENDS
    ITKDisplacementField
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
