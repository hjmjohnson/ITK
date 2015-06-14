set(DOCUMENTATION "This module contains classes for deformable image
registration based on intensity differences by solving the PDE, optical flow
problem.  This includes Thirion's popular \"demons\" algorithm.")

itk_module(ITKPDEDeformableRegistration
  ENABLE_SHARED #ENABLE_SHARED_IF_EXPLICIT_INSTANTIATION
  DEPENDS
    ITKRegistrationCommon
    ITKFiniteDifference
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
