set(DOCUMENTATION "This module contains classes for deformable image
registration based on intensity differences by solving the PDE, optical flow
problem.  This includes Thirion's popular \"demons\" algorithm.")

if(ITK_TEMPLATE_EXPLICIT_INSTANTIATION)
  set(ITKPDEDeformableRegistration_Shared "ENABLE_SHARED")
endif()

itk_module(ITKPDEDeformableRegistration
  ${ITKPDEDeformableRegistration_Shared}
  DEPENDS
    ITKRegistrationCommon
    ITKFiniteDifference
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
