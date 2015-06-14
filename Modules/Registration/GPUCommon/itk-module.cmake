set(DOCUMENTATION "This module contains some common components to support GPU-based
registrations")

itk_module(ITKGPURegistrationCommon
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKCommon
    ITKGPUCommon
    ITKGPUFiniteDifference
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
