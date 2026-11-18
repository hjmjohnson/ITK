set(
  DOCUMENTATION
  "This module contains implementations of generalized versions
of the Fast Marching filter. These implementations cover the use of Fast
Marching in both itk::Image and itk::QuadEdgeMesh objects."
)

itk_module(
  ITKFastMarching
  DEPENDS
    ITKQuadEdgeMesh
    ITKConnectedComponents
  PRIVATE_DEPENDS
    ITKMesh
  ENABLE_SHARED
  TEST_DEPENDS
    ITKTestKernel
    ITKImageLabel
    ITKIOMesh
    ITKGoogleTest
  DESCRIPTION "${DOCUMENTATION}"
)
