set(DOCUMENTATION "This module contains classes related to calculation of
eigenvectors and eigenvalues.")

itk_module(ITKEigen
  ENABLE_SHARED # ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKImageFilterBase
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
