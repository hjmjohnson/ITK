set(DOCUMENTATION "This module contains a group of basic video filtering classes.")

itk_module(ITKVideoFiltering
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKVideoCore
  TEST_DEPENDS
    ITKTestKernel
    ITKVideoIO
    ITKSmoothing
  DESCRIPTION
    "${DOCUMENTATION}"
)
